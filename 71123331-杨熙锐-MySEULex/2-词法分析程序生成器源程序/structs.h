#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cstring>

struct Rule {
    std::string pattern;
    std::vector<std::string> actions;
    int ruleId;
};

struct NFAState {
    int num;
    std::multimap<char, int> edges;
    
    NFAState(int n = -1) : num(n) {}
};

struct NFA {
    int startState;
    std::map<int, int> endStates;
    std::map<int, NFAState> states;
    int stateCount;
    
    NFA() : startState(-1), stateCount(0) {}
    
    int newState() {
        int id = stateCount++;
        states[id] = NFAState(id);
        return id;
    }
};

struct DFAState {
    int num;
    std::set<int> nfaStates;
    std::map<char, int> edges;
    int actionId;
    
    DFAState(int n = -1) : num(n), actionId(-1) {}
};

struct DFA {
    int startState;
    std::map<int, int> endStates;
    std::map<int, DFAState> states;
    std::set<char> alphabet;
    int stateCount;
    
    DFA() : startState(-1), stateCount(0) {}
};

struct DriverTable {
    std::vector<int> yy_edge_col;
    std::vector<int> yy_state_row;
    std::vector<int> yy_next;
    std::vector<int> yy_accept;
    std::vector<Rule> actionRules;
    int startState;
};

struct GlobalData {
    std::string part1;
    std::string part4;
    std::map<std::string, std::string> reMap;
    std::vector<Rule> rules;
};

extern GlobalData g_data;

#endif