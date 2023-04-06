#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <vector>
#include <string>

enum VType {V_T, V_N, DOT};

struct V {
	VType type;
	std::string value;
	V();
	V(VType type, std::string value);
};

typedef struct Grammar_Statement {
	std::string left;
	std::vector<V> right;
	std::string forward;
} Production;

struct Grammar {
	std::string start;
	std::vector<Grammar_Statement> grammars;
	int parse_from_str(std::vector<std::string> strs);
	std::string toString();
};

#endif