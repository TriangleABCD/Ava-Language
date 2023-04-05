#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <iostream>
#include <vector>
#include <string>

struct Grammar_Statement {
	std::string left;
	std::vector<std::string> right;
};

struct Grammar {
	std::string start;
	std::vector<Grammar_Statement> grammars;
	int parse_from_str(std::vector<std::string> strs);
	std::string toString();
};

#endif