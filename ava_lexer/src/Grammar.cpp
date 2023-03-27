
#include "Grammar.h"

int Grammar::parse_from_str(std::vector<std::string> strs) {
	for(auto& str: strs) {
		Grammar_Statement tmp;
		auto seg = str.find(" -> ");
		if(seg == std::string::npos) {
			return -1;
		}
		tmp.left = str.substr(0, seg);
		std::string ts = "";
		for(int i = seg+4; i < str.size(); ++i) {
			if(' ' == str[i]) {
				tmp.right.push_back(ts);
				ts = "";
				continue;
			}
			ts += str[i];
		}
		this->grammars.push_back(tmp);
	}
	this->start = this->grammars[0].left;
}

std::string Grammar::toString() {
	std::string res = "";
	res += "start symbol = \'" + this->start + "\'\n";
	for(auto& g: this->grammars) {
		std::string ts = "";
		ts += g.left + " -> ";
		for(auto& r: g.right) {
			ts += r + " ";
		}
		ts += "\n";
		res += ts;
	}
	return res;
}