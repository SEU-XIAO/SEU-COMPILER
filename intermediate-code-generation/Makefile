CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -fpermissive `llvm-config --cxxflags`
LDFLAGS = `llvm-config --ldflags --libs core`

FLEX = flex
BISON = bison

TARGET = compiler

# SysY 版本
SYSY_CXX_SRCS = main.cpp ast.cpp sysy.tab.cpp sysy_lex.yy.cpp
SYSY_HDRS = ast.h sysy.tab.h

# C99 版本（兼容）
C99_CXX_SRCS = main.cpp ast.cpp c99.tab.cpp lex.yy.cpp
C99_HDRS = ast.h c99.tab.h

all: sysy

sysy: $(SYSY_CXX_SRCS) $(SYSY_HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SYSY_CXX_SRCS) $(LDFLAGS)

c99: $(C99_CXX_SRCS) $(C99_HDRS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(C99_CXX_SRCS) $(LDFLAGS)

sysy.tab.cpp sysy.tab.h: sysy.y
	$(BISON) -d sysy.y
	mv sysy.tab.c sysy.tab.cpp

sysy_lex.yy.cpp: sysy.l sysy.tab.h
	$(FLEX) sysy.l
	mv lex.yy.c sysy_lex.yy.cpp

c99.tab.cpp c99.tab.h: c99.y
	$(BISON) -d c99.y
	mv c99.tab.c c99.tab.cpp

lex.yy.cpp: c99.l c99.tab.h
	$(FLEX) c99.l
	mv lex.yy.c lex.yy.cpp

test: sysy
	./$(TARGET) test.c

clean:
	rm -f $(TARGET) sysy.tab.cpp sysy.tab.h sysy_lex.yy.cpp \
	      c99.tab.cpp c99.tab.h lex.yy.cpp *.o

.PHONY: all sysy c99 test clean
