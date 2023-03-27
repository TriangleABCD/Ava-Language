#ifndef NFA_H
#define NFA_H

#include <string>
#include <vector>
#include <map>

enum NodeType_t {START_NODE, NORMAL_NODE, END_NODE};

typedef struct Node {
	int id;
	NodeType_t type;
	std::map<std::string, std::vector<Node*>> next;

	Node();
	Node(int id, NodeType_t type, std::vector<std::pair<std::string, int>> next);
} Node_t;

typedef struct NFA {
	
} NFA_t;

#endif