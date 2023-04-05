#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "EscapeCode.h"
#include "Grammar.h"
#include "NFA.h"
#include "DFA.h"
#include "Token.h"

int main(int argc, char** argv) {

    // arg parsing
    if(argc < 3) {
        std::cerr << set_color("[*] too few arguments", COLOR_RED) << "\n";
        std::cerr << set_color("[*] usage: ./ava_lexer grammar_path source_path [-o] [-v]", COLOR_RED) << "\n";
        return 0;
    }

    if(argc > 5) {
        std::cerr << set_color("[*] too many arguments", COLOR_RED) << "\n";
        std::cerr << set_color("[*] usage: ./ava_lexer grammar_path source_path [-o] [-v]", COLOR_RED) << "\n";
        return 0;
    }

    bool vis = false;
    bool out = false;

    if(argc == 4 && strcmp(argv[3], "-o") == 0) {
        out = true;
    }

    if(argc == 5 && strcmp(argv[4], "-v") == 0) {
        vis = true;
    }

    std::string grammar_path = argv[1];
    std::string source_path = argv[2];
    
    // read grammars
    std::ifstream grammar_file(grammar_path);
    if(!grammar_file.is_open()) {
        std::cerr << set_color("[*] failed to open grammar file", COLOR_RED) << "\n";
        return 0;
    }
    std::string line;
    auto readGrammer = [&](std::string type) -> std::vector<std::string> {
        std::vector<std::string> res;
        bool st = false;
        while(getline(grammar_file, line)) {
            if(st && line == "//") {
                break;
            }
            if(!st && type == line) {
                st = true;
                continue;
            }
            if(st) {
                res.push_back(line);
            }
        }
        return res;
    };
    
    std::vector<Grammar*> grammars({
        new Grammar(), new Grammar(), new Grammar(),
        new Grammar(), new Grammar(), new Grammar()
    });

    grammars[0]->parse_from_str(readGrammer("SEGMENT"));
    grammars[1]->parse_from_str(readGrammer("OPERATOR"));
    grammars[2]->parse_from_str(readGrammer("KEYWORD"));
    grammars[3]->parse_from_str(readGrammer("IDENTIFIER"));
    grammars[4]->parse_from_str(readGrammer("VALUE"));
    grammars[5]->parse_from_str(readGrammer("OTHERS"));

    // init NFAs
    
    std::vector<NFA_t*> nfas({
        new NFA(), new NFA(), new NFA(),
        new NFA(), new NFA(), new NFA()
    });

    for(int i = 0; i < (int)nfas.size(); ++i) {
        assert(0 == nfas[i]->buildNFA(*grammars[i]));
    }

    // init DFAs
    std::vector<DFA_t*> dfas({
        new DFA(), new DFA(), new DFA(),
        new DFA(), new DFA(), new DFA()
    });

    for(int i = 0; i < (int)dfas.size(); ++i) {
        assert(0 == dfas[i]->buildDFA(*nfas[i]));
    }

    // read source
    std::ifstream source_file(source_path);
    if(!source_file.is_open()) {
        std::cerr << set_color("[*] failed to open source file", COLOR_RED) << "\n";
        return 0;
    }

    std::vector<std::string> src_lines;
    while(getline(source_file, line)) {
        src_lines.push_back(line);
    }
    std::string code = "";
    for(auto& str: src_lines) {
        code += str;
        code += "\n";
    }
    
    std::vector<Token> tokens;
    int line_cnt = 1;
    std::string ttmp = "";

    auto check = [&](std::string tmp) {
        bool acc = false;
        for(int i = 2; i < (int)dfas.size(); ++i) {
            if(dfas[i]->accept(tmp)) {
                TokenType type;
                switch(i) {
                    case 2:
                        type = KEYWORD;
                        break;
                    case 3:
                        type = IDENTIFIER;
                        break;
                    case 4:
                        type = VALUE;
                        break;
                    case 5:
                        type = OTHERS;
                        break;
                }
                Token t_token(type, line_cnt, tmp);
                tokens.push_back(t_token);
                acc = true;
                break;
            }
        }
        if(!acc) {
            Token t_token(ERROR, line_cnt, tmp);
            tokens.push_back(t_token);
        }
    }; 
    int code_length = (int)code.size();
    for(int i = 0; i < code_length; ++i) {
        auto c = code[i];
        std::string tt = ""; tt += c;
        if(dfas[0]->accept(tt)) {
            if(ttmp != "") {
                check(ttmp);
                ttmp = "";
            }
            Token t_token(SEGMENT, line_cnt, tt);
            tokens.push_back(t_token);
            continue;
        }
        if((i > 0 && i < code_length-1 && code[i-1] == ' ' && code[i+1] == ' ') && dfas[1]->accept(tt)) {
            if(ttmp != "") {
                check(ttmp);
                ttmp = "";
            }
            Token t_token(OPERATOR, line_cnt, tt);
            tokens.push_back(t_token);
            continue;
        }
        if('\n' == c || ' ' == c) {
            if(ttmp != "") {
                check(ttmp);
                ttmp = "";
            }
            if('\n' == c) {
                ++line_cnt;
            }
            continue;
        }
        ttmp += c;
    }

    // write result to file
    std::ofstream res_file("./tokens.json");
    assert(res_file.is_open());
    std::string res_token = "{\n\t\"tokens\": [\n";
    for(auto& token: tokens) {
        res_token += "\t\t";
        res_token += token.toJSON();
        res_token += ", \n";
    }
    res_token += "\t]\n}";
    res_file << res_token;
    res_file.close();

    // output result on terminal
    if(!out) {
        return 0;
    }
    for(auto& token: tokens) {
        if(token.type == ERROR) {
            std::cout << set_color(token.toString(), COLOR_RED) << std::endl;
        } else {
            std::cout << set_color(token.toString(), COLOR_BLACK) << std::endl;
        }
    }
    return 0;
}
