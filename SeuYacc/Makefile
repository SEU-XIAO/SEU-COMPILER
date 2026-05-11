CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2

TARGET = seuYacc
SOURCES = main.cpp yaccDFA.cpp yyProducer.cpp yaccSource.cpp
OBJECTS = $(SOURCES:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET) *.exe