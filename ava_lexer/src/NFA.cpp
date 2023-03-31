
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
	this->goNext.insert(edge);
	return 0;
}

int NFA::buildNFA(const Grammar& G) {
	this->nodes.push_back(Node(START_NODE, G.start));
	this->name2node[G.start] = &this->nodes[0];

	this->nodes.push_back(Node(END_NODE, "END"));
	this->name2node["END"] = &this->nodes[1];

	for(auto& g: G.grammars) {
		if(this->states.find(g.left) == this->states.end()) {
			this->states.insert(g.left);
		}

		this->alphabet.insert(g.right[0]);

		if(1 == g.right.size()) {
			this->name2node[g.left]->addEdge({g.right[0], "END"});
		} else if(2 == g.right.size()) {
			if(this->states.find(g.right[1]) == this->states.end()) {
				this->states.insert(g.right[1]);
			}
			this->name2node[g.left]->addEdge({g.right[0], g.right[1]});
		} else {
			return -1;
		}
	}

	return 0;
}
	