# 软件课程设计(Ⅱ) Ava 语言

- **王尧勇   9201040G0833**
- 代码说明和使用样例见 `README.md` 文件

## 0. Ava 语言设计

### 0.0 概述

- `Ava` 是一个函数式+面向过程的编程语言，语法特性类似于 `C++`、`Python` 和 `Rust`，你会发现一些以上语言中的特性。
- 代码文件后缀名为 `.ava`

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

- `Ava` 程序代码由若干个函数组成，其中最下方必须有一个主函数，主函数匿名，其余函数要显式指定函数名。

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

- `Ava` 语言共有 `3` 种类型，分别是 **数字类型**、**字符串类型**、**函数类型**。

#### 0.2.0 标识符命名规则

- `Ava` 语言的标识符命名规则与 `C++` 类似
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
- 定义变量 `str s = 'a';` `str t = 'ava\n';`

#### 0.2.3 函数类型

- 类型关键字 `fn`
- 形式参考 `C++` 的 `lambda` 表达式
- 定义具名函数 `fn func = [](number a, number b) number {};`
- 若不显式指定返回值类型，则认为无返回值

### 0.3. 其他

- 函数 `print(<value>)` 打印变量或常量

## 1. 词法分析



## 2. 语法分析



正规文法

- 科学计数法数字的正规式推导正规文法

    - 正规式

    $$
    ENUM  \rightarrow (+|-|\epsilon) \cdot (0|1|\cdots|9)^* \cdot (('\cdot' \cdot (0|1|\cdots|9)^*) | \epsilon) \\
    \cdot(('e'\cdot(+|-|\epsilon)\cdot(0|1|\cdots|9)^*) | \epsilon)
    $$

    - 正规文法
    
    $$
    ENUM \rightarrow (+|-|\epsilon) A \\
    A \rightarrow (0|1|\cdots|9)F \\
    A \rightarrow B \\
    F \rightarrow (1|2|\cdots|9) F \\
    F \rightarrow B \\
    B \rightarrow {'\cdot'} G \\
    G \rightarrow (0|1|\cdots|9) H \\
    G \rightarrow  C \\
    H \rightarrow (0|1|\cdots|9) H \\
    H \rightarrow  C \\
    B \rightarrow  C \\
    C \rightarrow {'e'}I\\
    I \rightarrow (+|-|\epsilon)E \\
    C \rightarrow \epsilon \\
    C \rightarrow {'e'} D \\
    D \rightarrow (+|-|\epsilon)E\\
    E \rightarrow (0|1|\cdots|9)J \\
    E \rightarrow \epsilon \\
    J \rightarrow (0|1|\cdots|9)J \\
    J \rightarrow \epsilon \\
    $$

- 复数数字的正规式推导正规文法

    - 正规式

    $$
    CNUM \rightarrow (+|-|\epsilon)\cdot (0|1|\cdots|9)^* \cdot (+|-)\cdot (0|1|\cdots|9)^*\cdot {'i'}
    $$

    - 正规文法

    $$
    CNUM \rightarrow (+|-|\epsilon) AA \\
    AA \rightarrow (0|1|\cdots|9)EE \\
    AA \rightarrow BB \\
    EE \rightarrow (0|1|\cdots|9)EE \\
    EE \rightarrow BB \\
    BB \rightarrow (+|-)CC \\
    CC \rightarrow (0|1|\cdots|9)FF \\
    CC \rightarrow DD \\
    FF \rightarrow (0|1|\cdots|9)FF \\
    FF \rightarrow DD \\
    DD \rightarrow {'i'}
    $$

- 