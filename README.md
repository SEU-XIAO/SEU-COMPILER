# SEU-COMPILER - 编译原理课程实践

## 项目概述

本项目是东南大学编译原理课程实践，实现一个 **SysY 语言编译器**，将 SysY 源代码编译为 LLVM IR 中间代码。

SysY 语言是 C 语言的一个子集，支持 `int`/`float` 类型、数组、函数、控制流语句等特性。

## 项目结构

```
SEU-COMPILER/
├── lex/                        # 第一部分：词法分析程序生成器 (SeuLex)
│   ├── src/                    # SeuLex 工具源码 (C++)
│   │   ├── main.cpp           # 主程序
│   │   ├── parser.cpp/h       # .l 文件解析器
│   │   ├── structs.h          # 数据结构定义
│   │   ├── re_standardize.*   # 正则表达式标准化
│   │   ├── re_to_suffix.*     # 正则转后缀表达式
│   │   ├── suffix_to_nfa.*    # 后缀表达式转 NFA (Thompson 构造)
│   │   ├── nfa_to_dfa.*       # NFA 转 DFA (子集构造)
│   │   ├── code_generator.*   # 驱动表代码生成
│   │   └── utils.*            # 工具函数
│   ├── SysY.l                 # SysY 词法定义文件
│   ├── Makefile               # 构建脚本
│   └── test/                  # 测试用例
│
├── yacc/                       # 第二部分：语法分析程序生成器 (SeuYacc)
│   ├── src/                    # SeuYacc 工具源码 (C++)
│   │   ├── main.cpp           # 主程序
│   │   ├── yaccParser.h       # .y 文件解析器
│   │   ├── yaccDFA.cpp        # LR(1) DFA 构造
│   │   ├── LRTable.h         # LALR 分析表
│   │   ├── yyProducer.*       # 产生式管理
│   │   ├── yaccSource.*       # 生成的解析器代码模板
│   │   └── yyWrite.h         # 输出工具
│   ├── SysY.y                 # SysY 语法定义文件
│   ├── Makefile               # 构建脚本
│   └── test/                  # 测试用例
│
├── intermediate-code-generation/  # 第三部分：中间代码生成
│   ├── sysy.l                 # Flex 词法分析器 (SysY)
│   ├── sysy.y                 # Bison 语法分析器 (SysY)
│   ├── ast.h/cpp              # 抽象语法树定义和实现
│   ├── main.cpp               # 主程序 (LLVM IR 生成)
│   ├── Makefile               # 构建脚本
│   ├── test.c                 # 测试文件
│   ├── test_sysy.c            # SysY 测试文件
│   ├── c99.l                  # C99 词法分析器 (兼容)
│   └── c99.y                  # C99 语法分析器 (兼容)
│
└── Makefile                    # 顶层构建脚本
```

## 构建和运行

### 环境要求

- Linux 操作系统
- g++ 编译器 (支持 C++17)
- flex 词法分析器生成器
- bison 语法分析器生成器
- LLVM 开发库 (llvm-config)

### 安装依赖 (Ubuntu/Debian)

```bash
sudo apt-get install g++ flex bison llvm-dev
```

### 构建所有组件

```bash
make
```

### 单独构建各部分

```bash
# 构建词法分析程序生成器
make lex

# 构建语法分析程序生成器
make yacc

# 构建中间代码生成器
make intermediate
```

### 运行测试

```bash
make test
```

### 清理构建产物

```bash
make clean
```

## 各部分说明

### 第一部分：词法分析程序生成器 (lex/)

自定义的词法分析程序生成器，基于以下算法：
- **正则表达式标准化**：将正则表达式转换为标准形式
- **后缀表达式转换**：将中缀正则表达式转换为后缀表示
- **Thompson 构造法**：从后缀表达式构建 NFA
- **子集构造法**：将 NFA 转换为 DFA
- **DFA 最小化**：最小化 DFA 状态数
- **驱动表生成**：生成词法分析器的驱动表和 C++ 代码

使用方法：
```bash
cd lex
make
./seuLex SysY.l SysY_lex.yy.cpp
```

### 第二部分：语法分析程序生成器 (yacc/)

自定义的语法分析程序生成器，基于 LALR(1) 分析方法：
- **FIRST 集计算**：计算各非终结符的 FIRST 集
- **LR(1) 项集族构造**：构造 LR(1) 自动机
- **LALR 合并**：合并同心状态得到 LALR(1) 自动机
- **分析表生成**：生成 LALR(1) 分析表
- **C 代码生成**：生成可编译运行的语法分析器

使用方法：
```bash
cd yacc
make
./seuYacc SysY.y
# 生成 y.tab.c 和 y.tab.h
```

### 第三部分：中间代码生成 (intermediate-code-generation/)

基于 Flex/Bison 和 LLVM 的中间代码生成器：
- **词法分析**：使用 Flex 生成词法分析器
- **语法分析**：使用 Bison 生成语法分析器
- **AST 构建**：在语法分析过程中构建抽象语法树
- **LLVM IR 生成**：遍历 AST 生成 LLVM IR 中间代码

使用方法：
```bash
cd intermediate-code-generation
make sysy
./compiler test_sysy.c
```

## SysY 语言特性

SysY 是 C 语言的一个子集，支持以下特性：

- **类型**：`int`、`float`、`void`
- **常量**：`const` 修饰的常量声明
- **变量**：全局和局部变量声明
- **数组**：一维和多维数组
- **函数**：函数定义和调用
- **控制流**：`if-else`、`while`、`do-while`、`for`、`break`、`continue`、`return`
- **运算符**：算术、关系、逻辑、赋值运算符
- **注释**：单行 `//` 和多行 `/* */` 注释
