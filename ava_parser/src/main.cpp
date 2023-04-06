#include <iostream>
#include <string>
#include <fstream>

#include "LR.h"

int main(int argc, char** argv) {
	std::string filename = "../../demo/2grammar.txt";
	std::fstream file(filename);
	assert(file.is_open());
	std::vector<std::string> strs;
	std::string line;
	while(getline(file, line)) {
		strs.push_back(line);
	}
	LR lr;
	lr.initProductions(strs);
	lr.initV();
	for(auto& p: lr.productions) {
		std::cout << p.left << " -> ";
		for(auto& r: p.right) {
			std::cout << r.value << "(" << (r.type == V_T ? "T" : "N") << ") ";
		}
		std::cout << std::endl;
	}
	for(auto& s: lr.VT) {
		std::cout << s << "\t";
	}
	std::cout << std::endl;
	for(auto& s: lr.VN) {
		std::cout << s << "\t";
	}
	std::cout << std::endl;
	return 0;
}