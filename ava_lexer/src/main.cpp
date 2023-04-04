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
        std::cerr << set_color("[*] usage: ./ava_lexer grammar_path source_path [-v]", COLOR_RED) << "\n";
        return 0;
    }

    if(argc > 4) {
        std::cerr << set_color("[*] too many arguments", COLOR_RED) << "\n";
        std::cerr << set_color("[*] usage: ./ava_lexer grammar_path source_path [-v]", COLOR_RED) << "\n";
        return 0;
    }

    bool vis = false;

    if(argc == 4 && strcmp(argv[3], "-v") == 0) {
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

    // for(auto& nfa: nfas) {
    //     for(auto& node: nfa->nodes) {
    //         std::cout << node->node_name << std::endl;
    //         for(auto& a: nfa->alphabet) {
    //             if(node->goNext.count(a) <= 0) {
    //                 continue;
    //             }
    //             for(auto& e: node->goNext[a]) {
    //                 std::cout << "f(" + node->node_name << ", " + a
    //                     << ") = " << e << std::endl;
    //             }
    //         }
    //     }
    //     std::cout << "-------------------------" << std::endl;
    // }

    // init DFAs
    std::vector<DFA_t*> dfas({
        new DFA(), new DFA(), new DFA(),
        new DFA(), new DFA(), new DFA()
    });

    for(int i = 0; i < (int)dfas.size(); ++i) {
        assert(0 == dfas[i]->buildDFA(*nfas[i]));
    }

    // for(auto& dfa: dfas) {
    //     for(auto& node: dfa->nodes) {
    //         std::cout << node->node_name << std::endl;
    //         for(auto& a: dfa->alphabet) {
    //             if(node->goNext.count(a) <= 0) {
    //                 continue;
    //             }
    //             std::cout << "f(" + node->node_name << ", " + a
    //                 << ") = " << node->goNext[a] << std::endl;
    //         }
    //     }
    //     std::cout << "-------------------------" << std::endl;
    // }

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

    // start lexical anylysis
    // std::vector<Token_t> tokens;
    // for(int i = 0; i < src_lines.size(); ++i) {
    //     std::string tmp = "";
    //     for(auto& c: src_lines[i]) {
    //         if(c == ' ') {

    //         }
            
    //     }
    // }

    int n = 4;
    for(auto& node: dfas[n]->nodes) {
        std::cout << node->node_name << std::endl;
        for(auto& a: dfas[n]->alphabet) {
            if(node->goNext.count(a) <= 0) {
                continue;
            }
            std::cout << "f(" + node->node_name << ", " + a
                << ") = " << node->goNext[a] << std::endl; 
        }
    }
    std::string ee;
    std::cin >> ee;
    std::cout << std::boolalpha << dfas[n]->accept(ee) << std::endl;
    return 0;
}
