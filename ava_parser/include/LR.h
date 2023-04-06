#ifndef LR_H
#define LR_H

#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <assert.h>

#include "Grammar.h"
#include "Token.h"

struct LR {
	std::set<int> states;
	std::set<std::string> VT;
	std::set<std::string> VN;
	std::vector<Production> productions;

	std::stack<std::string> X;
	std::stack<int> S;

	std::map<std::pair<int, std::string>, int> GOTO;
	std::map<std::pair<int, std::string>, std::pair<int, int>> ACTION;

	int initProductions(std::vector<std::string> strs);

	int initV();

	int initLR();

	int getFIRST(std::map<std::string, std::set<std::string>>& FIRST);

	int getCLOSURE(std::vector<Production>& cur);

	bool accept(std::vector<Token> tokens);

}; 

#endif