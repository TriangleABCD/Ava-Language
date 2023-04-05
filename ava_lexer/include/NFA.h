#ifndef NFA_H
#define NFA_H

#include <string>
#include <vector>
#include <map>
#include <set>
#include <assert.h>

#include "Grammar.h"

enum NodeType_t {START_NODE, NORMAL_NODE, END_NODE};

typedef struct Node {
	NodeType_t type;
	std::string node_name;
	std::map<std::string, std::set<std::string>> goNext;

	Node();
	Node(NodeType_t type, std::string node_name, const std::vector<std::pair<std::string, std::string>>& edges);
	Node(NodeType_t type, std::string node_name);
	int addEdge(std::pair<std::string, std::string> edge);
} Node_t;

typedef struct NFA {
	std::map<std::string, Node_t*> name2node;
	std::vector<Node_t*> nodes;
	std::set<std::string> alphabet;
	std::set<std::string> states;
	int buildNFA(const Grammar& G);
	std::string toString();
	virtual ~NFA();
	
} NFA_t;

#endif