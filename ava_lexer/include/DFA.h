#ifndef DFA_H
#define DFA_H

#include "NFA.h"

typedef struct DFA_Node {
	NodeType_t node_type;
	std::string node_name;
	std::map<std::string, std::string> goNext;
	DFA_Node();
	DFA_Node(NodeType_t node_type, std::string node_name);
	DFA_Node(NodeType_t node_type, std::string node_name, const std::vector<std::pair<std::string, std::string>>& edges);
	int addEdge(const std::pair<std::string, std::string>& edge);
} DFA_Node_t;


typedef struct DFA {
	std::map<std::string, DFA_Node_t*> name2node;
	std::vector<DFA_Node_t*> nodes;
	std::set<std::string> alphabet;
	std::set<std::string> states;
	int buildDFA(const NFA_t& nfa);
	int simplifyDFA();
	virtual ~DFA();
} DFA_t;

#endif