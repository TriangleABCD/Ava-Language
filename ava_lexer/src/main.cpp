#include <iostream>
#include <string>
#include <fstream>

#include "Grammar.h"
#include "NFA.h"
#include "DFA.h"

using namespace std;

int main(int argc, char** argv) {
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
    // std::cout << grammar.toString() << std::endl;
    NFA_t nfa;
    nfa.buildNFA(grammar);
    for(auto& node: nfa.nodes) {
        std::cout << node->node_name << std::endl;
        for(auto& edge: node->goNext) {
            for(auto& ee: edge.second) {
                std::cout << "[*] f(" << node->node_name << ", " 
                << edge.first << ") = " << ee << std::endl;
            }
        }
    }
    std::cout << "--------------------------------------\n";
    DFA_t* dfa = new DFA();
    dfa->buildDFA(nfa);
    for(auto& node: dfa->nodes) {
        std::cout << node->node_name << std::endl;
        for(auto& edge: node->goNext) {
            std::cout << "[*] f(" << node->node_name << ", " 
                << edge.first << ") = " << edge.second << std::endl;
        }
    }
    return 0;
}
