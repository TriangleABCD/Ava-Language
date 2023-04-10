# Ava-Language

- 开发环境

    ```shell
    ubuntu 20.04
    C++ 17
    CMake >= 3.10
    ```

## 代码架构

```shell
./
	README.md
	报告
	ava_lexer/
		CMakeLists.txt
		include/
		src/
	ava_parser/
		CMakeLists.txt
		include/
		src/
	demo/
		regular_grammar.txt
		demo.ava
		2grammar.txt
		visual.py
		ava_lexer
		ava_parser
```

## 词法分析器

### 生成可执行文件

```shell
cd ava_lexer
mkdir build && cd build
cmake ..
make
```

### demo 测试

```shell
cd demo
./ava_lexer regular_grammar.txt demo.ava
```

### 结果输出至控制台

```shell
cd demo
./ava_lexer regular_grammar.txt demo.ava -o
```

### 输出 DFA 

```shell
cd demo
./ava_lexer regular_grammar.txt demo.ava -v
```

### DFA 可视化

```shell
cd demo
./ava_lexer regular_grammar.txt demo.ava -v | python visual.py
```

- `python` 依赖

    ```shell
    pip install graphviz
    ```

## 语法分析器

### 生成可执行文件

```shell
cd ava_parser
mkdir build && cd build
cmake ..
make
```

### demo 测试

```shell
cd demo
./ava_lexer regular_grammar.txt demo.ava
./ava_parser 2grammar.txt tokens.txt
```

### 输出中间过程和表

```shell
cd demo
./ava_lexer regular_grammar.txt demo.ava
./ava_parser 2grammar.txt tokens.txt -v
```

