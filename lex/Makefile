CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

TARGET = seuLex
SRCDIR = src
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/parser.cpp $(SRCDIR)/re_standardize.cpp \
          $(SRCDIR)/re_to_suffix.cpp $(SRCDIR)/suffix_to_nfa.cpp \
          $(SRCDIR)/nfa_to_dfa.cpp $(SRCDIR)/code_generator.cpp $(SRCDIR)/utils.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET) SysY.l SysY_lex.yy.cpp
	@echo "=== Generated SysY lexer: SysY_lex.yy.cpp ==="

clean:
	rm -f $(OBJECTS) $(TARGET) SysY_lex.yy.cpp *.exe
