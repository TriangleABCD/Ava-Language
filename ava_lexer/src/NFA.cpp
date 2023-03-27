
#include "NFA.h"

Node::Node() {
}


Node::Node(int id, NodeType_t type, 
	std::vector<std::pair<std::string, int>> next) {
	this->id = id;
	this->type = type;
	
}