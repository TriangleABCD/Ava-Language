
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
	this->VT.insert("#");
	return 0;
}


int LR::initLR() {
	auto getTag = [](Production* p) -> std::string {
		std::string res = "";
		res += p->left + " -> ";
		for(auto& r: p->right) {
			res += r.value + " ";
		}
		res += ", ";
		for(auto& f: p->forward) {
			res += f + "/";
		}
		return res;
	};

	// init I_0
	this->getFIRST();
	auto p0 = this->productions[0];
	p0.right.push_back(p0.right[0]);
	p0.right[0].value = ".";
	p0.right[0].type = DOT;
	Production* produc = new Production(p0.left, p0.right, std::set<std::string>({"#"}));
	this->allItems.push_back(produc);
	this->item2tag[produc] = getTag(produc);
	this->tag2item[item2tag[produc]] = produc;

	std::set<Production*> I_0;
	I_0.insert(produc);
	this->getCLOSURE(I_0);
	

	auto initTable = [&](int id, std::set<Production*>& cur, std::string c, int nid, std::set<Production*>& newState) {
		auto getK = [&](Production* p) -> int {
			int k = 0;
			Production pro;
			pro.left = p->left;
			for(auto& v: p->right) {
				if(v.type == DOT) {
					continue;
				}
				pro.right.push_back(V(v.type, v.value));
			}
			if(pro.right.size() == 0) {
				for(int i = 0; i < (int)(this->productions.size()); ++i) {
					if(this->productions[i].left == pro.left && this->productions[i].right[0].value == "%") {
						return i;
					}
				}
			}
			for(int i = 0; i < (int)(this->productions.size()); ++i) {
				if(getTag(&pro) == getTag(&this->productions[i])) {
					k = i;
					break;
				}
			}
			return k;
		};
		
		if(this->VT.find(c) != this->VT.end()) {
			for(auto& p: newState) {
				if(c == this->productions[0].right[0].value && p->right.back().type == DOT) {
					this->ACTION[{nid, "#"}] = {3, 0};
				} else if(p->right.back().type == DOT) {
					int k = getK(p);
					for(auto& fc: p->forward) {
						this->ACTION[{nid, fc}] = {2, k};
					}
				}
			}
			this->ACTION[{id, c}] = {1, nid};
		} else if(this->VN.find(c) != this->VN.end()) {
			this->GOTO[{id, c}] = nid;
		}
	};


	// start init the DFA GOTO and ACTION
	std::set<std::string> C;
	C.insert(this->stateSet2str(I_0));
	std::queue<std::set<Production*>> que;
	std::map<std::string, int> ID;
	que.push(I_0);
	ID[this->stateSet2str(I_0)] = 1;
	int id = 1;
	int finish = 0;
	while(!que.empty()) {
		auto cur = que.front();
		que.pop();
		std::set<std::string> VTN;
		VTN.insert(
			this->VN.begin(),
			this->VN.end()
		);
		VTN.insert(
			this->VT.begin(),
			this->VT.end()
		);

		// std::cout << "******************\n";
		// for(auto& p: cur) {
		// 	std::cout << p->left << " -> ";
		// 	for(auto& rr: p->right) {
		// 		std::cout << rr.value << " ";
		// 	}
		// 	std::cout << ", {";
		// 	for(auto& fo: p->forward) {
		// 		std::cout << fo << ", ";
		// 	}
		// 	std::cout << "}";
		// 	std::cout << std::endl;
		// }
		// std::cout << "******************\n\n";

		for(auto& c: VTN) {
			if(c == "%") {
				continue;
			}
			auto newState = this->move_(cur, c);
			this->getCLOSURE(newState);
			if(newState.size() > 0 && C.find(this->stateSet2str(newState)) == C.end()) {
				++id;
				ID[this->stateSet2str(newState)] = id;
				for(auto& ff: newState) {
					if(ff->left == this->productions[0].left) {
						finish = id;
						break;
					}
				}
				C.insert(this->stateSet2str(newState));
				initTable(ID[this->stateSet2str(cur)], cur, c, ID[this->stateSet2str(newState)], newState);
				que.push(newState);
			} else if(newState.size() > 0 && C.find(this->stateSet2str(newState)) != C.end()) {
				initTable(ID[this->stateSet2str(cur)], cur, c, ID[this->stateSet2str(newState)], newState);
			}
		}
	}
	this->ACTION[{finish, "#"}] = {3, 0};
	for(int i = 1; i <= id; ++i) {
		this->states.insert(i);
	}
	return 0;
}

int LR::getFIRST() {
	for(auto& produc: this->productions) {
		this->getProduction[produc.left].push_back(produc);
	}

	std::stack<std::string> path;
	std::set<std::string> path_set;
	std::set<std::string> finished;

	std::function<void(std::string)> dfs = [&](std::string symbol) {
		path.push(symbol);
		path_set.insert(symbol);
		if(finished.find(symbol) != finished.end()) {
			// FIRST[path.top()].insert(FIRST[symbol].begin(),FIRST[symbol].end());
			path_set.erase(path.top());
			path.pop();
			return;
		}
		if(symbol == "%" || this->VT.find(symbol) != this->VT.end()) {
			this->FIRST[symbol].insert(symbol);
			path_set.erase(path.top());
			path.pop();
			return;
		}
		if(this->VN.find(symbol) != this->VN.end()) {
			auto items = getProduction[symbol];
			for(auto& item: items) {
				for(int i = 0; i < (int)(item.right.size()); ++i) {
					auto& ti = item.right[i];
					if(ti.value == path.top() && path_set.find(ti.value) != path_set.end()) {
						break;
					}
					dfs(ti.value);
					bool hasE = this->FIRST[path.top()].find("%") == this->FIRST[path.top()].end();
					this->FIRST[path.top()].insert(
						this->FIRST[ti.value].begin(), 
						this->FIRST[ti.value].end()
					);
					if(hasE && this->VN.find(ti.value) != this->VN.end() && i != (int)(item.right.size()-1)) {
						for(auto& np: getProduction[ti.value]) {
							if(np.right.size() == 1 && np.right[0].value == "%") {
								this->FIRST[path.top()].erase("%");
							}
						}
					}
					if(this->VT.find(ti.value) != this->VT.end() 
						|| this->FIRST[ti.value].find("%") == this->FIRST[ti.value].end()) {
						break;
					}
				}
			}
		}
		finished.insert(path.top());
		path_set.erase(path.top());
		path.pop();
	};

	for(auto& a: this->VN) {
		dfs(a);
	}
	for(auto& a: this->VT) {
		dfs(a);
	}
	return 0;
}

int LR::getCLOSURE(std::set<Production*>& cur) {

	auto getTag = [](Production* p) -> std::string {
		std::string res = "";
		res += p->left + " -> ";
		for(auto& r: p->right) {
			res += r.value + " ";
		}
		res += ", ";
		for(auto& f: p->forward) {
			res += f + "/";
		}
		return res;
	};

	std::set<std::string> cc;
	for(auto& p: cur) {
		cc.insert(getTag(p));
	}

	int cur_size = 0;
	while(true) {
		if(cur_size == (int)cc.size()) {
			break;
		}
		cur_size = (int)cc.size();
		for(auto& p: cur) {
			for(int i = 0; i < (int)(p->right.size()); ++i) {
				if(p->right[i].type == DOT && i < (int)(p->right.size()-1) && p->right[i+1].type == V_N) {
					auto nps = this->getProduction[p->right[i+1].value];
					for(auto& np: nps) {
						Production* pp = new Production;
						pp->left = np.left;
						pp->right.push_back(V(DOT, "."));
						for(auto& rr: np.right) {
							if(rr.value == "%") {
								continue;
							}
							pp->right.push_back(rr);
						}
						if(i == (int)(p->right.size()-2) ){
							pp->forward.insert("#");
						} else {
							std::string first = p->right[i+2].value;
							pp->forward.insert(
								this->FIRST[first].begin(),
								this->FIRST[first].end()
							);
						}
						
						std::string tag = getTag(pp);
						if(this->tag2item.count(tag) > 0) {
							delete pp;
							if(cc.find(tag) == cc.end()) {
								cc.insert(tag);
								cur.insert(tag2item[tag]);
							}
						} else {
							this->allItems.push_back(pp);
							this->item2tag[pp] = tag;
							this->tag2item[tag] = pp;
							if(cc.find(tag) == cc.end()) {
								cc.insert(tag);
								cur.insert(pp);
							}
						}
					}
					break;
				}
			}
		}
	}
	return 0;
}

std::set<Production*> LR::move_(std::set<Production*> cur, std::string c) {
	auto getTag = [](Production* p) -> std::string {
		std::string res = "";
		res += p->left + " -> ";
		for(auto& r: p->right) {
			res += r.value + " ";
		}
		res += ", ";
		for(auto& f: p->forward) {
			res += f + "/";
		}
		return res;
	};

	std::set<Production*> res;
	for(auto& cur_p: cur) {
		for(int i = 0; i < (int)(cur_p->right.size()); ++i) {
			if(cur_p->right[i].type == DOT && i != (int)(cur_p->right.size()-1) && cur_p->right[i+1].value == c) {
				Production* newState = new Production(cur_p->left, cur_p->right, cur_p->forward);
				auto tmp = newState->right[i];
				newState->right[i] = newState->right[i+1];
				newState->right[i+1] = tmp;
				
				std::string tag = getTag(newState);
			
				if(this->tag2item.count(tag) > 0) {
					delete newState;
					res.insert(this->tag2item[tag]);
				} else {
					this->allItems.push_back(newState);
					this->item2tag[newState] = tag;
					this->tag2item[tag] = newState;
					res.insert(newState);
				}
				break;
			}
		}
	}
	return res;
}

std::string LR::stateSet2str(std::set<Production*>& ss) {
	std::string res = "";
	for(auto& p: ss) {
		res += this->item2tag[p] + " & ";
	}
	return res;
}

bool LR::accept(std::vector<Token> _tokens, bool vis) {
	std::vector<Token> tokens;
	for(auto& t: _tokens) {
		if(t.type == OTHERS) {
			continue;
		} else if(t.type == ERROR) {
			std::string err = "lex error: ";
			err += t.value;
			std::cout << set_color(err, COLOR_RED) << std::endl;
			return false;
		}
		tokens.push_back(t);
	}

	tokens.push_back(Token(KEYWORD, 0, "#"));

	this->X.push("#");
	this->S.push(1);

	bool ok = false;

	auto check_token = [&](Token token) -> int {
		std::string a = "";
		std::string ty = "";
		if(this->VT.find(token.value) != this->VT.end()) {
			a = token.value;
		} else {
			switch(token.type) {
				case KEYWORD:
					a += "KEYWORD";
					ty += "KEYWORD";
					break;
				case IDENTIFIER:
					a += "IDENTIFIER";
					ty += "IDENTIFIER";
					break;
				case VALUE:
					a += "VALUE";
					ty += "VALUE";
					break;
				case SEGMENT:
					a += "SEGMENT";
					ty += "SEGMENT";
					break;
				case OPERATOR:
					a += "OPERATOR";
					ty += "OPERATOR";
					break;
				case ERROR:
					a += "ERROR";
					ty += "ERROR";
					break;
				case OTHERS:
					a += "OTHERS";
					ty += "OTHERS";
					break;
			}
		}

		auto op = this->ACTION[{this->S.top(), a}];

		auto printStack = [](auto tt) {
			decltype(tt) st;
			while(!tt.empty()) {
				st.push(tt.top());
				tt.pop();
			}
			while(!st.empty()) {
				std::cout << st.top() << " ";
				st.pop();
			}
			std::cout << std::endl;
		};

		if(!vis) {
			goto Acc;
		}

		std::cout << "token: " << a << std::endl;
		std::cout << "[state stack] ";
		printStack(this->S);
		std::cout << std::endl;
		std::cout << "[symbol stack] ";
		printStack(this->X);
		std::cout << "\n\n";
		Acc:
		if(op.first == 3) {
			ok = true;
		} else if(op.first == 2) {
			int r = this->productions[op.second].right.size();
			if(this->productions[op.second].right[0].value == "%") {
				r = 0;
			}
			while(r--) {
				this->X.pop();
				this->S.pop();
			}
			this->X.push(this->productions[op.second].left);
			int nx = this->GOTO[{this->S.top(), this->X.top()}];
			this->S.push(nx);
			return 2;
		} else if(op.first == 1) {
			this->S.push(op.second);
			this->X.push(a);
		} else {
			return 0;
		}
		return 1;
	};
	for(int i = 0; i < (int)tokens.size(); ++i) {
		std::cout << i << "'s ";
		int res = check_token(tokens[i]);
		if(0 == res) {
			std::string err = set_color("error on line: ", COLOR_CYAN);
			err += set_color(std::to_string(tokens[i].line), COLOR_CYAN) + "\n";
			int ll = std::max(0, i - 10), rr = std::min((int)tokens.size(), i + 10);
			for(int ii = ll; ii < rr; ++ii) {
				if(i == ii) {
					err += set_color(tokens[ii].value+"^", COLOR_RED);
				} else {
					err += set_color(tokens[ii].value, COLOR_CYAN);
				}
				err += " ";
			}
			std::cout << err << std::endl;
			return false;
		} else if(2 == res) {
			--i;
		}
	}
	return ok;
}

LR::~LR() {
	for(auto& p: this->allItems) {
		delete p;
	}
}