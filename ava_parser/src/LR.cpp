
#include "LR.h"

int LR::initProductions(std::vector<std::string> strs) {
	Grammar grammar;
	assert(0 == grammar.parse_from_str(strs));
	Production tmp;
	tmp.left = grammar.start + "_" + grammar.start;
	tmp.right.push_back(V(V_N, grammar.start));
	this->productions.push_back(tmp);
	for(auto& prod: grammar.grammars) {
		this->productions.push_back(prod);
	}
	return 0;
}


int LR::initV() {
	for(auto& produc: this->productions) {
		this->VN.insert(produc.left);
		for(auto& vv: produc.right) {
			if(V_T == vv.type) {
				this->VT.insert(vv.value);
			} else if(V_N == vv.type) {
				this->VN.insert(vv.value);
			}
		}
	}
	return 0;
}


int LR::initLR() {
	std::set<std::string> C;
	std::map<std::string, std::set<std::string>> FIRST;

}

int LR::getFIRST(std::map<std::string, std::set<std::string>>& FIRST) {

}

int LR::getCLOSURE(std::vector<Production>& cur) {

}

bool LR::accept(std::vector<Token> tokens) {

}