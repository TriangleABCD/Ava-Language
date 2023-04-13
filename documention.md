# 软件课程设计(Ⅱ) Ava 语言

- 代码说明和使用样例见 ==README.md== 或 ==README.pdf== 文件

## 0. Ava 语言设计

### 0.0 概述

- ==Ava== 是一个函数式、面向过程的编程语言，语法特性类似于 `C++`、`Python` 和 `Rust`，你会发现一些以上语言中的特性。
- 代码文件后缀名为 `.ava`。
- 一个典型的 ==Ava== 程序如下所示：

```c++
fn add = [](number a, number b) number {
    return a + b;
};

fn max = [](number a, number b) {
    if(a > b) {
        return a;
    }
    return b;
};

fn doit = [](fn func, number a, number b) number {
    return func(a, b);
};

[]() number {
    number a = 3;
    number b = 4;
    str c = 'hello';
    str d = 'w';
    number e = 3.14;
    number f = max(a, b);
    number g = add(a, e);
    number i = 3+2i;
    doit(add, a, b);
    print(a);
    print(c);
    return 0;
}();
```

### 0.1 总体结构

- ==Ava==程序代码由若干个函数组成，其中最下方必须有一个主函数，主函数匿名，其余函数要显式指定函数名。

```c++
fn fun1 = [](参数列表) 返回值类型 {
    // 函数体
};

fn fun2 = [](参数列表) {
    // 函数体
};

[]() number {
    // 主函数体
}();
```

- 程序将从最下方的匿名主函数开始顺序执行，可以调用其他的具名函数。

### 0.2 基本类型和变量

- ==Ava== 语言共有 `3` 种类型，分别是 **数字类型**、**字符串类型**、**函数类型**。

#### 0.2.0 标识符命名规则

- ==Ava==语言的标识符命名规则与 `C++` 类似
    - 由 `数字`、`英文字母`、`下划线` 组成
    - 数字不能开头
    - 不与关键字重名
    - 区分大小写

#### 0.2.1 数字类型

- 类型关键字 `number`
- 表示所有的复数
    - 整数例如 `3`
    - 小数例如 `3.14`
    - 科学计数法表示的数 `314e-2`
    - 复数例如 `3+2i` (虚部必须在后)
- 定义变量 `number i = 3+2i;`，必须指定初始值

#### 0.2.2 字符串类型

- 类型关键字 `str`

- 和 `python` 类似，不区分单个字符和字符串，一律为字符串类型
- 用单引号包括字符串常量，支持转义字符
- 定义变量 `str s = 'a';` `str t = 'ava';`

#### 0.2.3 函数类型

- 类型关键字 `fn`
- 形式参考 `C++` 的 `lambda` 表达式
- 定义具名函数 `fn func = [](number a, number b) number {};`
- 若不显式指定返回值类型，则认为无返回值

### 0.3. 其他

- 函数 `print(<value>)` 打印变量或常量

## 1. 词法分析

### 1.0 词法分析程序流程

<img src="C:\Users\22117\Desktop\Course\软件课设2\pics\lexer_progress.png" alt="lexer_progress" style="zoom:80%;" />

### 1.1 正规文法

- >**正规文法**
    >
    >文法的所有产生式都满足如下形式：
    >
    >$A \rightarrow t$ 或 $A \rightarrow t B$
    >
    >其中 $A,B \in V_N, \ t \in V_T \cup {\epsilon}$.

- ==分隔符==的正规文法
    $$
    SEG \rightarrow \{ \ | \ \} \ | \ [ \ | \ ] \ | ( \ | \ ) \ | \ , \ | \ ; \\
    $$

- ==运算符==的正规文法
    $$
    OP \rightarrow + \ | \ - \ | \ * \ | \ / \ | \ < \ | \ > \ | \ = \\
    $$

- ==关键字==的正规文法
    $$
    KEYWORD \rightarrow fn |number|str|return|if \\
    $$

- ==标识符==的正规文法
    $$
    IDENTIFIER \rightarrow IDENTI\_START \ INDENT \\
    IDENTI\_START \rightarrow \_ \ | \ a \ | \ b \ | \ c \ | \ \cdots \ | \ z \ | \ A \ | \ B \ | \ \cdots \ | Z \\
    IDENTI \rightarrow (\_ \ | \ a \ | \ b \ | \ c \ | \ \cdots \ | \ z \ | \ A \ | \ B \ | \ \cdots \ | Z \ | \ 0 \ | \ 1 \ | \ 2 \ \cdots \ | \ 9) \ IDENTI \\
    $$

- 常量的正规文法
    $$
    VALUE \rightarrow \epsilon (\ STR \ | \ ENUM \ | \ CNUM)\\
    $$

    - ==字符串常量==

    $$
    STR \rightarrow ' \ STRS \\
    STRS \rightarrow \{字符\} \ STRS \\
    STRS \rightarrow ' \\
    $$

    - ==科学计数法==形式的数字，较为复杂，难以直接得出，先得出正则表达式，从正则表达式转换间接得到正规文法

    $$
    ENUM  \rightarrow (+|-|\epsilon) \cdot (0|1|\cdots|9)^* \cdot (('\cdot' \cdot (0|1|\cdots|9)^*) | \epsilon) \\
    \cdot(('e'\cdot(+|-|\epsilon)\cdot(0|1|\cdots|9)^*) | \epsilon)
    $$

    
    $$
    ENUM \rightarrow (+|-|\epsilon) A \\
    A \rightarrow (0|1|\cdots|9)F \ | \ B\\
    F \rightarrow (0|1|\cdots|9)F \ | \ B\\
    B \rightarrow {'\cdot'} G \ | \ C\\
    G \rightarrow (0|1|\cdots|9) H \ | \ C\\
    H \rightarrow (0|1|\cdots|9) H \ | \ C\\
    C \rightarrow {'e'}I \ | \ {'e'} D  \ | \ \epsilon \\
    I \rightarrow (+|-|\epsilon)E \\
    D \rightarrow (+|-|\epsilon)E\\
    E \rightarrow (0|1|\cdots|9)J \ | \ \epsilon \\
    J \rightarrow (0|1|\cdots|9)J \ | \ \epsilon  \\
    $$

    - ==复数==形式的数字，较为复杂，难以直接得出，先得出正则表达式，从正则表达式转换间接得到正规文法

    $$
    CNUM \rightarrow (+|-|\epsilon)\cdot (0|1|\cdots|9)^* \cdot (+|-)\cdot (0|1|\cdots|9)^*\cdot {'i'}
    $$

    $$
    CNUM \rightarrow (+|-|\epsilon) AA \\
    AA \rightarrow (0|1|\cdots|9)EE \ | \ BB \\
    EE \rightarrow (0|1|\cdots|9)EE \ | \ BB \\
    BB \rightarrow (+|-)CC \\
    CC \rightarrow (0|1|\cdots|9)FF \ | \ DD \\
    FF \rightarrow (0|1|\cdots|9)FF \ | \ DD \\
    DD \rightarrow {'i'}
    $$

- ==注释==的正规文法
    $$
    OTHER \rightarrow // \ STR
    $$

### 1.2 从正规文法到 NFA

- >**正规文法到非确定的有穷自动机的转换算法**：
    >
    >- NFA $$M$$ 的字母表与文法 $$G$$ 的终结符相同。
    >- 为 $$G$$ 中的每一个非终结符生成 $$M$$ 中的一个状态，$$G$$ 中的开始符号作为 $$M$$ 的开始状态。
    >- 增加一个新状态 $$Z$$ 作为 $$M$$ 的终态。
    >- 对 $$G$$ 中的形如 $$A\rightarrow tB$$的规则（其中 $$t$$ 为终结符或者 $$ \epsilon $$，$$A,B$$为非终结符的一个产生式），构造 $$M$$ 的一个转换函数 $$f(A,t)=B$$。
    >- 对 $$G$$ 中的形如 $$A\rightarrow t$$的产生式，，构造 $$M$$ 的一个转换函数 $$f(A,t)=Z$$。

- ==NFA== 数据结构表示

    - 自动机的每个节点存储自身的节点类型、名字，同时用 `std::map<std::string, std::set<std::string>>` 来表示遇到非终结符时应该转移到的下一节点的名字。

        ```c++
        struct Node {
        	NodeType_t type;
        	std::string node_name;
        	std::map<std::string, std::set<std::string>> goNext;
            // functions ....
        };

    - 一个 ==NFA== 由若干个节点组成，自动机的结构体存储每个节点的指针，以及名字到指针的映射，同时存储所有的非终结符。

        ```c++
        struct NFA {
        	std::map<std::string, Node_t*> name2node;
        	std::vector<Node_t*> nodes;
        	std::set<std::string> alphabet;
        	std::set<std::string> states;
        	// functions ....
        };

### 1.3 从 NFA 到 DFA

- ==DFA== 数据结构表示

    - 确定的有穷自动机的节点和非确定的节点表示基本一致，其中用 `std::map<std::string, std::string>` 来表示遇到非终结符时应该转移到的下一节点的名字，由于是确定的自动机，所以下一节点是唯一的。

        ```c++
        struct DFA_Node {
        	NodeType_t node_type;
        	std::string node_name;
        	std::map<std::string, std::string> goNext;
        	// functions .... 
        };
        ```

    - ==DFA== 的结构同样类似于 ==NFA==，由若干个节点组成，自动机的结构体存储每个节点的指针，以及名字到指针的映射，同时存储所有的非终结符。

        ```c++
        struct DFA {
        	std::map<std::string, DFA_Node_t*> name2node;
        	std::vector<DFA_Node_t*> nodes;
        	std::set<std::string> alphabet;
        	std::set<std::string> states;
            // functions .... 
        };
        ```

- >**子集法**：
    >
    >设 ==NFA== 为 $N = (K,\sum,f, K_0, K_t)$，按照如下步骤构造一个 ==DFA== $M=(S,\sum,D,S_0,S_t)$ 使得二者描述的语言等价。
    >
    >1. $$M$$ 的状态集 $$S$$ 由 $$K$$ 的一些子集组成，构造子集的算法如下：
    >
    >    1. $令 \epsilon-closure(K_0)为 C 中唯一成员，并且是未标注的.$
    >
    >    2. $$
    >        while(C 中存在尚未被标记过的子集 T) \ \{ \\
    >        标记 T ; \\
    >        for \  a \  in \sum \ \ \{ \\
    >        U := \epsilon-closure(move(T, a)); \\
    >        如果 U 不在 C中，将 U 作为未标记的子集加入 C中 \\
    >        \}
    >        \}
    >        $$
    >
    >2. $$M$$ 和 $$N$$ 的字母表一致。
    >
    >3. 转换函数 $$D([S_1,S_2,\cdots,S_j], a) = [R_1, R_2,\cdots, R_i]$$ 其中 $$\epsilon -closure(move([S_1,S_2,\cdots,S_j], a))=[R_1, R_2,\cdots, R_i]$$。
    >
    >4. $$S_0=\epsilon-closure(K_0)$$ 为 $$M$$ 的开始状态。
    >
    >5. $$S_t=\{ [S_j,S_k,\cdots,S_e] \}$$ 其中 $$[S_j,S_k,\cdots,S_e] \in S$$ 且 $$\{S_j,S_k,\cdots,S_e\} \cap K_t \neq \emptyset $$。

- 子集法的核心在于实现两个函数：`closure` 和 `move`

    - 闭包拓展

        ```c++
        int DFA::closure_(NFA& nfa, std::set<Node*>& cur) {
        	int size = 0;
        	while(true) {
        		if(size == (int)cur.size())
        			break;  // 如果闭包不再扩大, 就退出
        		size = cur.size();
                // 从空弧扩展
        		for(auto& node: cur) {
        			if(node->goNext.count("%") <= 0)
        				continue;
        			for(auto& nextNode: node->goNext["%"])
        				cur.insert(nfa.name2node[nextNode]);
        		}
        	}
        	return 0;
        }
        ```

    - `move`

        ```c++
        std::set<Node*> DFA::move_(NFA& nfa, std::set<Node*> cur, std::string a) {
        	std::set<Node*> res;
        	for(auto& node: cur) {
        		if(node->goNext.count(a) <= 0)
        			continue;
        		for(auto& nextNode: node->goNext[a])
        			res.insert(nfa.name2node[nextNode]);
        	}
        	return res;
        }
        ```

- 子集法主流程

    ```c++
    int DFA::buildDFA(NFA_t& nfa) {
    	std::set<std::string> C;
    	std::map<std::string, bool> ok;
    	// 构造初识状态
    	std::set<Node_t*> beg;
    	beg.insert(nfa.nodes[0]);
    	auto beg_str = this->subSets2str(beg);
    	C.insert(beg_str);
    	DFA_Node_t* p = new DFA_Node(START_NODE, beg_str);
    	this->nodes.push_back(p);
    	this->name2node[beg_str] = p;
    	this->states.insert(beg_str);
    	// NFA 转 DFA
    	std::vector<std::vector<std::string>> C_goNext;
    	while(true) {
    		// 检查是否所有状态都已经被标记
    		bool allOK = true;
    		for(auto& st: C)
    			if(!ok[st]) {
    				allOK = false;
    				break;
    			}
    		if(allOK) 
    			break;
    		// 选择一个未被标记的状态
    		std::string cur;
    		for(auto& st: C)
    			if(!ok[st]) {
    				cur = st;
    				break;
    			}
    		ok[cur] = true;
    		auto cur_set = this->str2subSets(nfa, cur);
    		for(auto& a: this->alphabet) {
    			auto newState = this->move_(nfa, cur_set, a);
    			if(newState.size() == 0)
    				continue;
    			assert(0 == this->closure_(nfa, newState));
    			auto new_str = this->subSets2str(newState);
    			if(new_str == "%")
    				continue;
    			if(C.find(new_str) == C.end())
    				C.insert(new_str);
    			C_goNext.push_back({cur, a, new_str});
    		}
    	}
    	// 存储 DFA 的节点和边信息 ....
    	return 0;
    }
    ```

- 算法优化

    - 在子集法中，以及后续的 ==LR(1)== 语法分析的过程中，会多次涉及到一个问题，就是快速判断某个无序的集合是否已经出现过。
    - 例如，使用子集法构造 ==DFA== 时，每个 ==DFA== 状态对应一个 ==NFA== 结点的无序集合，当算法转移到一个得到新的 ==DFA== 状态时，需要判断它的 ==NFA== 结点集合是否已经出现过。构造 ==LR(1)== 项目集自动机时，也需要对项目集合的存在性进行查询。
    - 利用 `c++ STL` 的 `std::set` 可以用少量代码实现一个高效的算法。
        - 每次有新的集合中的状态新产生，就将其绑定一个值，这个值的类型是基本数据类型，例如整型或者字符串。
        - 本项目采用节点的名字字符串作为节点的唯一标识，保证名字不重复，用 `std::map<std::string, Node*>` 和 `std::map<Node*, std::string>` 来绑定对应关系。
        - 一个集合中有若干个 `Node*`，按照其名字字符串字典序排列，然后按序拼接所有节点的字符串，每两个字符串之间用一个未出现在名字中的字符连接，例如下划线 `_`。得到的拼接后的字符串即为该集合的唯一标识。
        - 不难证明，不同的两个集合，其对应的字符串标识必定不一样。用 `std::set<std::string>` 记录所有出现过的集合字符串，即可判断某个集合是否已经出现过。
        - 假设待查询的集合为 $S$ ，则查询一次的时间复杂度为 $\mathcal{O}(|S|\log{|S|})$，因为 `std::set` 的底层实现是红黑树，一种平衡二叉搜索树，可达到 `log` 级别的复杂度。

### 1.4 词法分析结果输出和可视化

- `token` 输出

    - 以 `json` 格式输出到可执行文件同目录下的 ==tokens.json==，格式如下：

        ```json
        {
        	"tokens": [
        		{"line": 1, "type": "KEYWORD", "value": "fn"}, 
        		{"line": 1, "type": "IDENTIFIER", "value": "add"}, 
        		{"line": 1, "type": "OPERATOR", "value": "="}, 
        		{"line": 1, "type": "SEGMENT", "value": "["}, 
        		// ....
        	]
        }
        ```

    - 以 `txt` 格式输出到可执行文件同目录下的 ==tokens.txt==，方便语法分析程序读入，格式如下：

        ```shell
        第一行一个整数 n ，表示一共有 n 个 token。
        接下来 n 行，每行输入 line type value，
        分别表示行号、token类型、token值
        ```

    - `-o` 参数可以将输出同步输出在命令行终端（详见 ==README==）。 

- 中间过程的自动机输出（详见 ==README==）

    - `-v` 参数可将自动机输出至控制台。
    - 输出用管道绑定到 ==python visual.py== 可以绘制自动机。

## 2. 语法分析

### 2.0 语法分析程序流程

<img src="C:\Users\22117\Desktop\Course\软件课设2\pics\parser_progress.png" alt="parser_progress" style="zoom:80%;" />

### 2.1 构造项目集族

- >**项目**：
    >
    >在产生式中插入一个符号 $\cdot$，它之前的符号是待约的，它之后的符号是自动机转移的依据。
    >
    >例如 $S\rightarrow \cdot A$ 就是一个项目
    >
    >对于空产生式 $A\rightarrow \epsilon$，其对应的项目为 $A\rightarrow \cdot$

- >**$CLOSURE(I)$** 函数：
    >
    >对于 $\forall S \in I$，若 $S\rightarrow \alpha \cdot B\beta, \ a$ 在闭包内
    >
    >那么 $B \rightarrow \gamma, \ FIRST(\beta)$ 也在闭包内。
    >
    >反复取出 $I$ 中项目进行闭包的扩展，直到闭包不再扩大即可。

- >**$MOVE(I, \beta)$** 函数：
    >
    >对于 $\forall S \in I$，若 $S\rightarrow \alpha\cdot \beta \gamma, \ a$
    >
    >$S\rightarrow \alpha \beta \cdot \gamma, \ a \ \in MOVE(I,\beta)$ 

- LR(1) 项目集的构造

    1. 构造初始状态 $I_0$
        - $I_0 = CLOSURE(\{ S^{'} \rightarrow \cdot S \})$
    2. 反复构造新状态 $CLOSURE(MOVE(I,a))$ 直到不再产生新状态
    3. 记录下过程中所有的节点和边的转移关系。

- 求 `FIRST` 集合

    ```c++
    int LR::getFIRST() {
    	std::stack<std::string> path, path_set, finished;
    	std::function<void(std::string)> dfs = [&](std::string symbol) {
    		path.push(symbol);
    		path_set.insert(symbol);
    		if(finished.find(symbol) != finished.end()) {
    			path_set.erase(path.top()); path.pop();
    			return;
    		}
    		if(symbol == "%" || this->VT.find(symbol) != this->VT.end()) {
    			this->FIRST[symbol].insert(symbol);
    			path_set.erase(path.top()); path.pop();
    			return;
    		}
    		if(this->VN.find(symbol) != this->VN.end()) {
    			auto items = getProduction[symbol];
    			for(auto& item: items) {
    				for(int i = 0; i < (int)(item.right.size()); ++i) {
    					auto& ti = item.right[i];
    					if(ti.value == path.top() && path_set.find(ti.value) != path_set.end())
    						break;
    					dfs(ti.value);
    					bool hasE = this->FIRST[path.top()].find("%") == this->FIRST[path.top()].end();
    					this->FIRST[path.top()].insert(
    						this->FIRST[ti.value].begin(), this->FIRST[ti.value].end()
    					);
    					if(hasE&&this->VN.find(ti.value) != this->VN.end()&&i != (int)(item.right.size()-1)) {
    						for(auto& np: getProduction[ti.value])
    							if(np.right.size() == 1 && np.right[0].value == "%")
    								this->FIRST[path.top()].erase("%");
    					}
    					if(this->VT.find(ti.value) != this->VT.end() 
    						|| this->FIRST[ti.value].find("%") == this->FIRST[ti.value].end())
    						break;
    				}
    			}
    		}
    		finished.insert(path.top()); path_set.erase(path.top()); path.pop();
    	};
    	for(auto& a: this->VN) dfs(a);
    	for(auto& a: this->VT) dfs(a);
    	return 0;
    }
    ```

- 求闭包

    ```c++
    int LR::getCLOSURE(std::set<Production*>& cur) {
    	std::set<std::string> cc;
    	for(auto& p: cur) cc.insert(getTag(p));
    	int cur_size = 0;
    	while(true) {
    		if(cur_size == (int)cc.size()) break;
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
    							if(rr.value == "%") continue;
    							pp->right.push_back(rr);
    						}
    						if(i == (int)(p->right.size()-2) )
    							pp->forward.insert("#");
    						else {
    							std::string first = p->right[i+2].value;
    							pp->forward.insert(
    								this->FIRST[first].begin(), this->FIRST[first].end()
    							);
    						}
    						std::string tag = getTag(pp);
    						if(this->tag2item.count(tag) > 0) {
    							delete pp;
    							if(cc.find(tag) == cc.end()) {
    								cc.insert(tag); cur.insert(tag2item[tag]);
    							}
    						} else {
    							this->allItems.push_back(pp);
    							this->item2tag[pp] = tag;
    							this->tag2item[tag] = pp;
    							if(cc.find(tag) == cc.end()) {
    								cc.insert(tag); cur.insert(pp);
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
    ```

- 求 `MOVE` 

    ```c++
    std::set<Production*> LR::move_(std::set<Production*> cur, std::string c) {
    	std::set<Production*> res;
    	for(auto& cur_p: cur) {
    		for(int i = 0; i < (int)(cur_p->right.size()); ++i) {
    			if(cur_p->right[i].type==DOT&&i!=(int)(cur_p->right.size()-1) && cur_p->right[i+1].value == c) {
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
    ```

### 2.2 LR(1) 分析表的生成

- 对于构造好的 ==DFA== 上的每一条有向边 $A \xrightarrow{a} B$

    - 若 $a \in V_N$，则更新 $GOTO[A, a] = B$
    - 若 $a \in V_T$，则更新 $ACTION[A,a]=S_B$

- 对于构造好的 ==DFA== 上的每一个状态 $S$，它是一个项目的集合

    - 对于 $\forall production \in S$

    - 若 $production \rightarrow ... \ \cdot, \{x,y,\cdots\}$
    - 则更新 $ACTION[S,i] = r_k$，其中 $i\in \{x,y,\cdots\}$，$k$ 为这个产生式原本的编号
    - 特别的，若上面的 $i=\#$ 且 $production = 开始符号$，则 $ACTION[S,i]=acc$

- ```c++
    auto initTable = [&](int id, std::set<Production*>& cur, std::string c, 
    	int nid, std::set<Production*>& newState) {
    	if(this->VT.find(c) != this->VT.end()) {
    		for(auto& p: newState) {
    			if(c == this->productions[0].right[0].value && p->right.back().type == DOT) {
    				this->ACTION[{nid, "#"}] = {3, 0};
    			} else if(p->right.back().type == DOT) {
    				int k = getK(p);
    				for(auto& fc: p->forward)
    					this->ACTION[{nid, fc}] = {2, k};
    			}
    		}
    		this->ACTION[{id, c}] = {1, nid};
    	} else if(this->VN.find(c) != this->VN.end())
    		this->GOTO[{id, c}] = nid;
    };

### 2.3 LR(1) 分析过程

1. 初始状态入状态栈、`#` 入符号栈，输入串末尾添加 `#`
2. `op = ACTION[S.top(), a]`，对于当前的输入符号 `a` 和状态栈栈顶状态，查询 `ACTION` 表
    1. $op = acc$：接受，语法分析结束。
    2. $op = S_x$：移进，状态 `x` 入状态栈，符号 `a` 入符号栈。
    3. $op = r_x$：归约，用第 `x` 条产生式归约，假设为 $A \rightarrow ...$ 产生式右边有 `y` 个符号，则状态栈和符号栈都出栈 `y` 和元素，然后 `A` 入符号栈，`GOTO[S.top(), A]` 入状态栈。 `a` 为当前的输入符号，下一次的输入符号还是从 `a` 开始。
    4. $op = err$：错误，语法分析结束，反馈出错位置。

```c++
auto check_token = [&](Token token) -> int {
		auto op = this->ACTION[{this->S.top(), a}];
		if(op.first == 3)
			ok = true;
		else if(op.first == 2) {
			int r = this->productions[op.second].right.size();
			if(this->productions[op.second].right[0].value == "%")
				r = 0;
			while(r--) {
				this->X.pop(); this->S.pop();
			}
			this->X.push(this->productions[op.second].left);
			int nx = this->GOTO[{this->S.top(), this->X.top()}];
			this->S.push(nx);
			return 2;
		} else if(op.first == 1) {
			this->S.push(op.second); this->X.push(a);
		} else
			return 0;
		return 1;
	};
```

###  2.4 语法分析结果输出和可视化

- 语法分析结果的输出

    - ![image-20230411002153162](C:\Users\22117\AppData\Roaming\Typora\typora-user-images\image-20230411002153162.png)

- 中间过程的输出

    - `-v` 参数可以输出 `ACTION` 和 `GOTO` 表以及每一步分析的符号栈、状态栈的内容

        ![image-20230411002513509](C:\Users\22117\AppData\Roaming\Typora\typora-user-images\image-20230411002513509.png)

        ![image-20230411002542394](C:\Users\22117\AppData\Roaming\Typora\typora-user-images\image-20230411002542394.png)

        <img src="C:\Users\22117\AppData\Roaming\Typora\typora-user-images\image-20230411002624354.png" alt="image-20230411002624354" style="zoom:80%;" />

        

## 3. 总结

- 通过本次编译原理的软件课设，我对编译原理中的各种算法有了更加深刻、细致的了解。尤其对一些算法的工程实现有了深刻的理解。
- 同时此次的项目代码量较高，给 `debug` 的能力和耐心有较大的考验。
- 好在，利用熟悉的 `C++` 语言，尤其是其功能丰富又高效的 `STL` 库，我可以用尽可能少的代码实现功能。
- 由于时间安排问题，此次项目未能继续完成编译的后端部分，例如后续的语义分析、中间代码生成等。在课设结束后，后续功能将同步在 ==Github== 仓库。
