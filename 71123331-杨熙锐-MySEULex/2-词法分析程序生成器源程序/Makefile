# SeuLex Makefile

CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

TARGET = seuLex
SOURCES = main.cpp parser.cpp re_standardize.cpp re_to_suffix.cpp suffix_to_nfa.cpp nfa_to_dfa.cpp code_generator.cpp utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) lex.yy.cpp *.exe

test: $(TARGET)
	./$(TARGET) test.l lex.yy.cpp
	$(CXX) -std=c++17 -o test_lexer lex.yy.cpp
	./test_lexer test_input.txt
