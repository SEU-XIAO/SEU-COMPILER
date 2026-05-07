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

// 词法规则结构
struct Rule {
    std::string pattern;                    // 正则表达式模式
    std::vector<std::string> actions;       // 对应的动作代码
    int ruleId;                             // 规则ID
};

// NFA状态结构
struct NFAState {
    int num;                                // 状态编号
    // 出边集合: <转换字符, 目标状态号>, '@' 代表epsilon
    std::multimap<char, int> edges;
    
    NFAState(int n = -1) : num(n) {}
};

// NFA结构
struct NFA {
    int startState;                         // 开始状态编号
    std::map<int, int> endStates;           // 结束状态集合 <状态号, 规则ID>
    std::map<int, NFAState> states;         // 所有状态
    int stateCount;                         // 状态计数器
    
    NFA() : startState(-1), stateCount(0) {}
    
    int newState() {
        int id = stateCount++;
        states[id] = NFAState(id);
        return id;
    }
};

// DFA状态结构
struct DFAState {
    int num;                                // 状态编号
    std::set<int> nfaStates;                // 对应的NFA状态子集
    std::map<char, int> edges;              // 出边集合 <转换字符, 目标状态号>
    int actionId;                           // 接受状态对应的规则ID (-1表示非接受状态)
    
    DFAState(int n = -1) : num(n), actionId(-1) {}
};

// DFA结构
struct DFA {
    int startState;                         // 开始状态编号
    std::map<int, int> endStates;           // 接受状态集合 <状态号, 规则ID>
    std::map<int, DFAState> states;         // 所有状态
    std::set<char> alphabet;                // 字母表
    int stateCount;                         // 状态计数器
    
    DFA() : startState(-1), stateCount(0) {}
};

// 驱动表结构
struct DriverTable {
    std::vector<int> yy_edge_col;           // 字符到列号的映射 (大小256)
    std::vector<int> yy_state_row;          // 状态行起始索引
    std::vector<int> yy_next;               // 状态转换表
    std::vector<int> yy_accept;             // 接受状态表
    std::vector<Rule> actionRules;          // 动作规则列表
    int startState;                         // 起始状态
};

// 全局数据
struct GlobalData {
    std::string part1;                      // %{ %} 之间的代码
    std::string part4;                      // 第二个 %% 之后的代码
    std::map<std::string, std::string> reMap;   // 正则表达式别名定义
    std::vector<Rule> rules;                // 词法规则列表
};

extern GlobalData g_data;

#endif // STRUCTS_H
