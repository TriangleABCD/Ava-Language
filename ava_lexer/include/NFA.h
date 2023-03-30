#ifndef NFA_H
#define NFA_H

#include <string>
#include <vector>
#include <map>
#include <set>

#include "Grammar.h"

enum NodeType_t {START_NODE, NORMAL_NODE, END_NODE};

typedef struct Node {
	NodeType_t type;
	std::string node_name;
	std::multimap<std::string, std::string> goNext;

	Node();
	Node(NodeType_t type, std::string node_name, std::vector<std::pair<std::string, std::string>> edges);
	
} Node_t;

typedef struct NFA {
	std::map<std::string, Node_t*> name2node;
	std::vector<Node_t> nodes;

	int buildNFA(Grammar G);
	
} NFA_t;

#endif