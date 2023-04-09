#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <vector>
#include <string>
#include <set>

enum VType {V_T, V_N, DOT};

struct V {
	VType type;
	std::string value;
	V();
	V(VType type, std::string value);
	V(const V& v);
	void operator=(const V& v);
};

typedef struct Grammar_Statement {
	std::string left;
	std::vector<V> right;
	std::set<std::string> forward;
	Grammar_Statement();
	Grammar_Statement(std::string left, std::vector<V> right, std::set<std::string> forward);
	Grammar_Statement(const Grammar_Statement& g);
} Production;

struct Grammar {
	std::string start;
	std::vector<Grammar_Statement> grammars;
	int parse_from_str(std::vector<std::string> strs);
	std::string toString();
};

#endif