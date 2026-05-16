# SEU-COMPILER 顶层 Makefile
# 编译原理课程实践 - SysY 编译器

.PHONY: all lex yacc intermediate clean test

all: lex yacc intermediate

# 第一部分：词法分析程序生成器 (SeuLex)
lex:
	$(MAKE) -C lex

# 第二部分：语法分析程序生成器 (SeuYacc)
yacc:
	$(MAKE) -C yacc

# 第三部分：中间代码生成 (Flex/Bison + LLVM)
intermediate:
	$(MAKE) -C intermediate-code-generation

# 运行所有测试
test: test-lex test-yacc test-intermediate

test-lex: lex
	$(MAKE) -C lex test

test-yacc: yacc
	$(MAKE) -C yacc test

test-intermediate: intermediate
	$(MAKE) -C intermediate-code-generation test

# 清理所有构建产物
clean:
	$(MAKE) -C lex clean
	$(MAKE) -C yacc clean
	$(MAKE) -C intermediate-code-generation clean
