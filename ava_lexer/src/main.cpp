#include <iostream>
#include <string>
#include <cstring>
#include <fstream>

#include "EscapeCode.h"
#include "Grammar.h"
#include "NFA.h"
#include "DFA.h"

using namespace std;

int main(int argc, char** argv) {

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

    std::cout << grammar_path << std::endl;
    std::cout << source_path << std::endl;
    std::cout << boolalpha << vis << std::endl;


    Grammar grammar;

    vector<string> lines;
    string line;
    ifstream file("/Code/cpp/Ava-Language/demo/G_sample.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }
    grammar.parse_from_str(lines);

    NFA_t* nfa = new NFA();
    nfa->buildNFA(grammar);
    
    DFA_t* dfa = new DFA();
    dfa->buildDFA(*nfa);
    
    // DFA_t* simlified_dfa = new DFA();
    // simlified_dfa->simplifyDFA(*dfa);

    return 0;
}
