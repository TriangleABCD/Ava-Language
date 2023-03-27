#include <iostream>
#include <string>
#include <fstream>

#include "Grammar.h"

using namespace std;

int main() {
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
    std::cout << grammar.toString() << std::endl;
    return 0;
}
