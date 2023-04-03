#ifndef DFA_H
#define DFA_H

#include <algorithm>

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

	DFA();
	int buildDFA(NFA_t& nfa);
	int simplifyDFA();
	std::string subSets2str(const std::set<Node_t*>& subSets);
	std::set<Node_t*> str2subSets(NFA_t& nfa, std::string str);
	std::set<Node_t*> move_(NFA_t& nfa, std::set<Node_t*> cur, std::string a);
	int closure_(NFA_t& nfa, std::set<Node_t*>& cur);
	virtual ~DFA();
} DFA_t;

#endif