#include "suffix_to_nfa.h"
#include "utils.h"
#include <stack>

// NFA片段结构（用于构造过程中的栈）
struct NFAFragment {
    int startState;
    std::set<int> endStates;

    NFAFragment(int start, const std::set<int>& ends)
        : startState(start), endStates(ends) {}
};

// 为单个规则构建NFA
static NFA buildNFAForRule(const std::string& suffix, int ruleId, int& stateCounter) {
    NFA nfa;
    nfa.stateCount = stateCounter;

    std::stack<NFAFragment> fragStack;

    for (size_t i = 0; i < suffix.length(); i++) {
        char c = suffix[i];

        // 处理转义序列（如 \n, \t, \.）
        if (c == '\\' && i + 1 < suffix.length()) {
            char next = suffix[i + 1];
            char actualChar;
            switch (next) {
                case 'n': actualChar = '\n'; break;
                case 't': actualChar = '\t'; break;
                case 'r': actualChar = '\r'; break;
                case 'v': actualChar = '\v'; break;
                case 'f': actualChar = '\f'; break;
                case 'a': actualChar = '\a'; break;
                case '\\': actualChar = '\\'; break;
                case '0': actualChar = '\0'; break;
                case ' ': actualChar = ' '; break;
                default: actualChar = next; break;
            }
            int start = nfa.newState();
            int end = nfa.newState();
            nfa.states[start].edges.insert({actualChar, end});
            fragStack.push(NFAFragment(start, {end}));
            i++;
            continue;
        }

        // epsilon
        if (c == '@') {
            int start = nfa.newState();
            fragStack.push(NFAFragment(start, {start}));

        } else if (c == '$') {
            // 连接操作
            if (fragStack.size() < 2) {
                std::cerr << "Error: Invalid regex pattern (not enough operands for concatenation)" << std::endl;
                continue;
            }
            NFAFragment frag2 = fragStack.top(); fragStack.pop();
            NFAFragment frag1 = fragStack.top(); fragStack.pop();

            for (int endState : frag1.endStates) {
                nfa.states[endState].edges.insert({'\0', frag2.startState});
            }

            fragStack.push(NFAFragment(frag1.startState, frag2.endStates));

        } else if (c == '|') {
            // 或操作
            if (fragStack.size() < 2) {
                std::cerr << "Error: Invalid regex pattern (not enough operands for alternation)" << std::endl;
                continue;
            }
            NFAFragment frag2 = fragStack.top(); fragStack.pop();
            NFAFragment frag1 = fragStack.top(); fragStack.pop();

            int newStart = nfa.newState();
            int newEnd = nfa.newState();

            nfa.states[newStart].edges.insert({'\0', frag1.startState});
            nfa.states[newStart].edges.insert({'\0', frag2.startState});

            for (int endState : frag1.endStates) {
                nfa.states[endState].edges.insert({'\0', newEnd});
            }
            for (int endState : frag2.endStates) {
                nfa.states[endState].edges.insert({'\0', newEnd});
            }

            fragStack.push(NFAFragment(newStart, {newEnd}));

        } else if (c == '*') {
            // 闭包操作
            if (fragStack.size() < 1) {
                std::cerr << "Error: Invalid regex pattern (not enough operands for closure)" << std::endl;
                continue;
            }
            NFAFragment frag = fragStack.top(); fragStack.pop();

            int newStart = nfa.newState();
            int newEnd = nfa.newState();

            nfa.states[newStart].edges.insert({'\0', frag.startState});
            nfa.states[newStart].edges.insert({'\0', newEnd});

            for (int endState : frag.endStates) {
                nfa.states[endState].edges.insert({'\0', frag.startState});
                nfa.states[endState].edges.insert({'\0', newEnd});
            }

            fragStack.push(NFAFragment(newStart, {newEnd}));

        } else if (c == '.') {
            // '.' wildcard: matches any ASCII character (1-127), excluding '\0' (epsilon)
            int start = nfa.newState();
            int end = nfa.newState();

            for (int ch = 1; ch < 128; ch++) {
                nfa.states[start].edges.insert({(char)ch, end});
            }

            fragStack.push(NFAFragment(start, {end}));
        } else {
            // 普通字符
            int start = nfa.newState();
            int end = nfa.newState();

            nfa.states[start].edges.insert({c, end});

            fragStack.push(NFAFragment(start, {end}));
        }
    }

    if (!fragStack.empty()) {
        NFAFragment finalFrag = fragStack.top();
        nfa.startState = finalFrag.startState;
        for (int endState : finalFrag.endStates) {
            nfa.endStates[endState] = ruleId;
        }
    }

    stateCounter = nfa.stateCount;
    return nfa;
}

// 合并多个NFA
NFA convertToNFA() {
    NFA finalNFA;
    int stateCounter = 0;

    std::vector<NFA> nfas;
    int ruleIdx = 0;
    for (const auto& rule : g_data.rules) {
        std::cout << "  Building NFA for rule " << ruleIdx << ": " << rule.pattern.substr(0, 50) << "..." << std::endl;
        NFA nfa = buildNFAForRule(rule.pattern, rule.ruleId, stateCounter);
        nfas.push_back(nfa);

        for (const auto& pair : nfa.states) {
            finalNFA.states[pair.first] = pair.second;
        }
        for (const auto& pair : nfa.endStates) {
            finalNFA.endStates[pair.first] = pair.second;
        }
        ruleIdx++;
    }

    int newStart = stateCounter;
    finalNFA.states[newStart] = NFAState(newStart);
    finalNFA.startState = newStart;

    for (const auto& nfa : nfas) {
        finalNFA.states[newStart].edges.insert({'\0', nfa.startState});
    }

    finalNFA.stateCount = stateCounter + 1;

    std::cout << "NFA constructed with " << finalNFA.states.size() << " states" << std::endl;

    return finalNFA;
}
