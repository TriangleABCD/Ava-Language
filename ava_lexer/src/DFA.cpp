
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


int DFA::buildDFA(NFA_t& nfa) {
	this->alphabet = nfa.alphabet;

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
			assert(0 == this->closure_(nfa, newState));
			auto new_str = this->subSets2str(newState);
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
		p = new DFA_Node(NORMAL_NODE, st);
		this->nodes.push_back(p);
		this->name2node[st] = p;
	}

	for(auto& edge: C_goNext) {
		this->name2node[edge[0]]->addEdge({edge[1], edge[2]});
	}

	return 0;
}


int DFA::simplifyDFA() {

	return 0;
}


std::set<Node_t*> DFA::move_(NFA_t& nfa, std::set<Node_t*> cur, std::string a) {
	std::set<Node_t*> res;
	for(auto& node: cur) {
		for(auto& nextNode: node->goNext[a]) {
			res.insert(nfa.name2node[nextNode]);
		}
	}
	return res;
}


int DFA::closure_(NFA_t& nfa, std::set<Node_t*>& cur) {
	for(auto& node: cur) {
		for(auto& nextNode: node->goNext["%"]) {
			cur.insert(nfa.name2node[nextNode]);
		}
	}
	return 0;
}


std::string DFA::subSets2str(const std::set<Node_t*>& subSets) {
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


DFA::~DFA() {

}
