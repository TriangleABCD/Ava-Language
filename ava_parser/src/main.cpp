#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "LR.h"
#include "EscapeCode.h"
#include "Token.h"

int main(int argc, char** argv) {
	// arg parsing
    if(argc < 3) {
        std::cerr << set_color("[*] too few arguments", COLOR_RED) << "\n";
        std::cerr << set_color("[*] usage: ./ava_parser grammar_path token_path [-v]", COLOR_RED) << "\n";
        return 0;
    }

    if(argc > 4) {
        std::cerr << set_color("[*] too many arguments", COLOR_RED) << "\n";
        std::cerr << set_color("[*] usage: ./ava_parser grammar_path token_path [-v]", COLOR_RED) << "\n";
        return 0;
    }

    bool vis = false;

    if((argc == 4 && strcmp(argv[3], "-v") == 0)) {
        vis = true;
    }

    std::string filename = argv[1];
    std::string token_path = argv[2];

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
	lr.initLR();

	if(!vis) {
		goto Check;
	}

	std::cout << "ACTION\n%\t";
	for(auto c: lr.VT) {
		if(c == "%") {
			continue;
		}
		if(c == "IDENTIFIER") {
			c = "IDENT";
		}
		std::cout << c << "\t";
	}
	std::cout << "\n";
	for(auto& st: lr.states) {
		std::cout << st << "\t";
		for(auto& c: lr.VT) {
			if(c == "%") {
				continue;
			}
			std::string r = "";
			if(lr.ACTION.count({st, c}) <= 0) {
				r = "err";
			} else if(lr.ACTION[{st, c}].first == 1) {
				r = "S" + std::to_string(lr.ACTION[{st, c}].second);
			} else if(lr.ACTION[{st, c}].first == 2) {
				r = "r" + std::to_string(lr.ACTION[{st, c}].second);
			} else if(lr.ACTION[{st, c}].first == 3) {
				r = "acc";
			}
			std::cout << r << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << "\nGOTO\n";
	for(auto& st: lr.states) {
		for(auto& c: lr.VN) {
			if(lr.GOTO[{st, c}] == 0) {
				continue;
			}
			std::cout << "GOTO(" << st << ", " << c << ") = " << lr.GOTO[{st, c}] << std::endl;
		}
	}
	std::cout << "\n\n";
	Check:
	std::fstream token_file(token_path);
	assert(token_file.is_open());
	std::vector<Token> tokens;

	int token_n;
	token_file >> token_n;
	for(int i = 0; i < token_n; ++i) {
		int line_n;
		std::string ty, value;
		token_file >> line_n >> ty >> value;
		TokenType type;
		if("KEYWORD" == ty) {
			type = KEYWORD;
		} else if("IDENTIFIER" == ty) {
			type = IDENTIFIER;
		} else if("VALUE" == ty) {
			type = VALUE;
		} else if("ERROR" == ty) {
			type = ERROR;
		} else if("SEGMENT" == ty) {
			type = SEGMENT;
		} else if("OPERATOR" == ty) {
			type = OPERATOR;
		} else if("OTHERS" == ty) {
			type = OTHERS;
		}
		tokens.push_back(Token(type, line_n, value));
	}

	token_file.close();

	bool res = lr.accept(tokens, vis);
	if(res) {
		std::cout << "yes\n";
	} else {
		std::cout << "no\n";
	}
	return 0;
}