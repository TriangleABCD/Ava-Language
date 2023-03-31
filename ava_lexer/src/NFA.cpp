
#include "NFA.h"

Node::Node() {
}


Node::Node(NodeType_t type, std::string node_name) {
	this->type = type;
	this->node_name = node_name;
}


Node::Node(NodeType_t type, std::string node_name, 
	const std::vector<std::pair<std::string, std::string>>& edges) {
	
	this->type = type;
	this->node_name = node_name;
	for(auto& edge : edges) {
		assert(this->addEdge(edge) == 0);
	}
}

int Node::addEdge(std::pair<std::string, std::string> edge) {
	this->goNext[edge.first].insert(edge.second);	
	return 0;
}

int NFA::buildNFA(const Grammar& G) {
	Node_t* p = new Node(START_NODE, G.start);
	this->nodes.push_back(p);
	this->name2node[G.start] = this->nodes.back();
    this->states.insert(G.start);

	p = new Node(END_NODE, "END");
	this->nodes.push_back(p);
	this->name2node["END"] = this->nodes.back();
    this->states.insert("END");

	for(auto& g: G.grammars) {
		if(this->states.find(g.left) == this->states.end()) {
			p = new Node(NORMAL_NODE, g.left);
			this->nodes.push_back(p);
			this->name2node[g.left] = this->nodes.back();
			this->states.insert(g.left);
		}

		if(1 == g.right.size()) {
			this->alphabet.insert(g.right[0]);
			this->name2node[g.left]->addEdge({g.right[0], "END"});
		} else if(2 == g.right.size()) {
			this->alphabet.insert(g.right[0]);
			if(this->states.find(g.right[1]) == this->states.end()) {
				p = new Node(NORMAL_NODE, g.right[1]);
				this->nodes.push_back(p);
				this->name2node[g.right[1]] = this->nodes.back();
				this->states.insert(g.right[1]);
			}
			this->name2node[g.left]->addEdge({g.right[0], g.right[1]});
		} else {
			return -1;
		}
	}

	return 0;
}


NFA::~NFA() {
	for(auto& p: this->nodes) {
		delete p;
	}
}
