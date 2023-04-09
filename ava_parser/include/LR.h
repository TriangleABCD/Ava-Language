#ifndef LR_H
#define LR_H

#include <iostream>
#include <string>
#include <stack>
#include <set>
#include <map>
#include <assert.h>
#include <functional>
#include <algorithm>
#include <queue>

#include "Grammar.h"
#include "Token.h"
#include "EscapeCode.h"

struct LR {
	std::set<int> states;
	std::set<std::string> VT;
	std::set<std::string> VN;
	std::vector<Production> productions;

	std::stack<std::string> X;
	std::stack<int> S;

	std::map<std::pair<int, std::string>, int> GOTO;
	std::map<std::pair<int, std::string>, std::pair<int, int>> ACTION;

	std::vector<Production*> allItems;
	std::map<Production*, std::string> item2tag;
	std::map<std::string, Production*> tag2item;
	std::map<std::string, std::set<std::string>> FIRST;
	std::map<std::string, std::vector<Production>> getProduction;

	int initProductions(std::vector<std::string> strs);

	int initV();

	int initLR();

	int getFIRST();

	int getCLOSURE(std::set<Production*>& cur);

	std::set<Production*> move_(std::set<Production*> cur, std::string c);

	std::string stateSet2str(std::set<Production*>& ss);

	bool accept(std::vector<Token> tokens, bool vis);

	virtual ~LR();

}; 

#endif