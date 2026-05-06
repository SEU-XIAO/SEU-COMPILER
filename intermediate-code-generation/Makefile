CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -fpermissive `llvm-config --cxxflags`
LDFLAGS = `llvm-config --ldflags --libs core`

FLEX = flex
BISON = bison

TARGET = compiler

CXX_SRCS = main.cpp ast.cpp c99.tab.cpp lex.yy.cpp
HDRS = ast.h c99.tab.h

all: $(TARGET)

$(TARGET): $(CXX_SRCS) $(HDRS)
	$(CXX) $(CXXFLAGS) -o $@ $(CXX_SRCS) $(LDFLAGS)

c99.tab.cpp c99.tab.h: c99.y
	$(BISON) -d c99.y
	mv c99.tab.c c99.tab.cpp

lex.yy.cpp: c99.l c99.tab.h
	$(FLEX) c99.l
	mv lex.yy.c lex.yy.cpp

clean:
	rm -f $(TARGET) c99.tab.cpp c99.tab.h lex.yy.cpp *.o

.PHONY: all clean
