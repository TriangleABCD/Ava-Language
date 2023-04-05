#ifndef LR_H
#define LR_H

#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <map>

#include "Grammar.h"

struct LR {
	std::set<int> states;
	std::set<std::string> VT;
	std::set<std::string> VN;
	std::vector<Grammar_Statement> productions;

	std::stack<std::string> X;
	std::stack<int> S;

	std::map<std::pair<int, std::string>, int> GOTO;
	std::map<std::pair<int, std::string>, int> ACTION;
}; 

#endif