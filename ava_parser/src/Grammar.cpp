
#include "Grammar.h"

V::V() {
}
	
	
V::V(VType type, std::string value) {
	this->type = type;
	this->value = value;
}

V::V(const V& v) {
	this->type = v.type;
	this->value = v.value;
}
	
	
void V::operator=(const V& v) {
	this->type = v.type;
	this->value = v.value;
}

Grammar_Statement::Grammar_Statement() {
}


Grammar_Statement::Grammar_Statement(std::string left, std::vector<V> right, std::set<std::string> forward) {
	this->left = left;
	this->right = right;
	this->forward = forward;
}

Grammar_Statement::Grammar_Statement(const Grammar_Statement& g) {
	this->left = g.left;
	this->right = g.right;
	this->forward = g.forward;
}


int Grammar::parse_from_str(std::vector<std::string> strs) {
	for(auto& str: strs) {
		Grammar_Statement tmp;
		auto seg = str.find(" -> ");
		if(seg == std::string::npos) {
			return -1;
		}
		tmp.left = str.substr(0, seg);
		std::string ts = "";
		for(int i = seg+4; ; ++i) {
			if('\0' == str[i]) {
				if(ts[0] == '@') {
					tmp.right.push_back(V(V_N, ts));
				} else {
					tmp.right.push_back(V(V_T, ts));
				}
				ts = "";
				break;
			}
			if(' ' == str[i]) {
				if(ts[0] == '@') {
					tmp.right.push_back(V(V_N, ts));
				} else {
					tmp.right.push_back(V(V_T, ts));
				}
				ts = "";
				continue;
			}
			ts += str[i];
		}
		this->grammars.push_back(tmp);
	}
	this->start = this->grammars[0].left;
	return 0;
}

std::string Grammar::toString() {
	std::string res = "";
	res += "start symbol = \'" + this->start + "\'\n";
	for(auto& g: this->grammars) {
		std::string ts = "";
		ts += g.left + " -> ";
		for(auto& r: g.right) {
			ts += r.value + " ";
		}
		ts += "\n";
		res += ts;
	}
	return res;
}