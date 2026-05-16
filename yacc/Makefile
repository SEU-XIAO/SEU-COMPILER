CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

TARGET = seuYacc
SRCDIR = src
SOURCES = $(SRCDIR)/main.cpp $(SRCDIR)/yaccDFA.cpp $(SRCDIR)/yyProducer.cpp $(SRCDIR)/yaccSource.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean test

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(SRCDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET) SysY.y
	@echo "=== Generated y.tab.h ==="
	@head -20 y.tab.h
	@echo "=== Generated y.tab.c ==="
	@head -20 y.tab.c

clean:
	rm -f $(OBJECTS) $(TARGET) y.tab.c y.tab.h
