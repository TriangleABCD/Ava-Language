
#include "DFA.h"

DFA_Node::DFA_Node() {
}


DFA_Node::DFA_Node(NodeType_t node_type, std::string node_name, 
	const std::vector<std::pair<std::string, std::string>>& edges) {

	this->node_type = node_type;
	this->node_name = node_name;
	for(auto& edge : edges) {
		assert(this->addEdge(edge) == 0);
	}
}


DFA_Node::DFA_Node(NodeType_t node_type, std::string node_name) {
	this->node_type = node_type;
	this->node_name = node_name;
}


int DFA_Node::addEdge(const std::pair<std::string, std::string>& edge) {
	this->goNext[edge.first] = edge.second;
	return 0;
}


DFA::DFA() {
}


int DFA::buildDFA(NFA_t& nfa) {
	this->alphabet = nfa.alphabet;
	this->alphabet.erase("%");

	std::set<std::string> C;
	std::map<std::string, bool> ok;

	// build the start state
	std::set<Node_t*> beg;
	beg.insert(nfa.nodes[0]);
	assert(0 == this->closure_(nfa, beg));
	auto beg_str = this->subSets2str(beg);
	C.insert(beg_str);

	DFA_Node_t* p = new DFA_Node(START_NODE, beg_str);

	this->nodes.push_back(p);
	this->name2node[beg_str] = p;
	this->states.insert(beg_str);

	// NFA 2 DFA

	std::vector<std::vector<std::string>> C_goNext;

	while(true) {
		// check if all states are ok
		bool allOK = true;
		for(auto& st: C) {
			if(!ok[st]) {
				allOK = false;
				break;
			}
		}
		if(allOK) {
			break;
		}

		// choose a state that is not ok
		std::string cur;
		for(auto& st: C) {
			if(!ok[st]) {
				cur = st;
				break;
			}
		}
		ok[cur] = true;
		auto cur_set = this->str2subSets(nfa, cur);
		for(auto& a: this->alphabet) {
			auto newState = this->move_(nfa, cur_set, a);
			if(newState.size() == 0) {
				continue;
			}
			assert(0 == this->closure_(nfa, newState));
			auto new_str = this->subSets2str(newState);
			if(new_str == "%") {
				continue;
			}
			if(C.find(new_str) == C.end()) {
				C.insert(new_str);
			}
			C_goNext.push_back({cur, a, new_str});
		}
	}

	for(auto& st: C) {
		if(this->states.find(st) != this->states.end()) {
			continue;
		}
		this->states.insert(st);
		if(st.find("END") != std::string::npos) {
			p = new DFA_Node(END_NODE, st);
		} else {
			p = new DFA_Node(NORMAL_NODE, st);
		}
		this->nodes.push_back(p);
		this->name2node[st] = p;
	}

	for(auto& edge: C_goNext) {
		this->name2node[edge[0]]->addEdge({edge[1], edge[2]});
	}

	return 0;
}


int DFA::simplifyDFA(DFA& dfa) {
	
	return 0;
}


std::set<Node_t*> DFA::move_(NFA_t& nfa, std::set<Node_t*> cur, std::string a) {
	std::set<Node_t*> res;
	for(auto& node: cur) {
		if(node->goNext.count(a) <= 0) {
			continue;
		}
		for(auto& nextNode: node->goNext[a]) {
			res.insert(nfa.name2node[nextNode]);
		}
	}
	return res;
}


int DFA::closure_(NFA_t& nfa, std::set<Node_t*>& cur) {
	int size = 0;
	while(true) {
		if(size == (int)cur.size()) {
			break;
		}
		size = cur.size();
		for(auto& node: cur) {
			if(node->goNext.count("%") <= 0) {
				continue;
			}
			for(auto& nextNode: node->goNext["%"]) {
				cur.insert(nfa.name2node[nextNode]);
			}
		}
	}
	return 0;
}


std::string DFA::subSets2str(const std::set<Node_t*>& subSets) {
	if(subSets.size() == 0) {
		return "%";
	}
	std::string str = "";
	for(auto& p: subSets) {
		str += p->node_name;
		str += "_";
	}
	return str;
}
	

std::set<Node_t*> DFA::str2subSets(NFA_t& nfa, std::string str) {
	std::set<Node_t*> subSets;
	std::string tmp = "";
	for(auto& c: str) {
		if('_' == c) {
			subSets.insert(nfa.name2node[tmp]);
			tmp = "";
		} else {
			tmp += c;
		}
	}
	return subSets;
}


bool DFA::accept(std::string str) {
	std::string cur = this->nodes[0]->node_name;
	for(auto& c: str) {
		std::string cc = ""; cc += c;
		if(this->alphabet.find(cc) == this->alphabet.end()) {
			return false;
		}
		if(this->name2node[cur]->goNext.count(cc) <= 0) {
			return false;
		}
		cur = this->name2node[cur]->goNext[cc];
	}
	if(END_NODE == this->name2node[cur]->node_type) {
		return true;
	}
	return false;
}

std::string DFA::toString() {
	std::string res = "";
	res += std::to_string(this->nodes.size()) + "\n";
	for(auto& node: this->nodes) {
		res += node->node_name + "\n";
	}
	std::string tmp = "";
	int cnt = 0;
	for(auto& node: this->nodes) {
		for(auto& a: this->alphabet) {
			if(node->goNext.count(a) <= 0) {
				continue;
			}
			++cnt;
			tmp += node->node_name + " " + a + " " + node->goNext[a] + "\n";
		}
	}
	res += std::to_string(cnt) + "\n";
	res += tmp;
	return res;
}


DFA::~DFA() {
	for(auto& p: this->nodes) {
		delete p;
	}
}
