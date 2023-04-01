
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


int DFA::buildDFA(const NFA_t& nfa) {
	
}


int DFA::simplifyDFA() {

	return 0;
}


DFA::~DFA() {

}
