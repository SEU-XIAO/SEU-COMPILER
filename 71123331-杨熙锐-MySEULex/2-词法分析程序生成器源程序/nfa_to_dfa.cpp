#include "nfa_to_dfa.h"
#include "utils.h"
#include <queue>

// 计算状态的epsilon闭包
static std::set<int> epsilonClosure(const NFA& nfa, const std::set<int>& states) {
    std::set<int> closure = states;
    std::stack<int> stack;

    for (int state : states) {
        stack.push(state);
    }

    while (!stack.empty()) {
        int state = stack.top();
        stack.pop();

        auto it = nfa.states.find(state);
        if (it != nfa.states.end()) {
            auto lb = it->second.edges.lower_bound('\0');
            auto ub = it->second.edges.upper_bound('\0');
            for (auto iter = lb; iter != ub; ++iter) {
                if (closure.find(iter->second) == closure.end()) {
                    closure.insert(iter->second);
                    stack.push(iter->second);
                }
            }
        }
    }

    return closure;
}

// 计算状态集合在某个输入字符下的转移
static std::set<int> move(const NFA& nfa, const std::set<int>& states, char c) {
    std::set<int> result;

    for (int state : states) {
        auto it = nfa.states.find(state);
        if (it != nfa.states.end()) {
            auto range = it->second.edges.equal_range(c);
            for (auto iter = range.first; iter != range.second; ++iter) {
                result.insert(iter->second);
            }
        }
    }

    return result;
}

// 使用子集构造法将NFA转换为DFA
DFA convertNFAtoDFA(const NFA& nfa) {
    DFA dfa;

    // 收集字母表（所有非epsilon的字符）
    for (const auto& pair : nfa.states) {
        for (const auto& edge : pair.second.edges) {
            if (edge.first != '\0') {
                dfa.alphabet.insert(edge.first);
            }
        }
    }

    // DFA的初始状态是NFA初始状态的epsilon闭包
    std::set<int> startSet = epsilonClosure(nfa, {nfa.startState});

    // 为DFA状态分配编号
    std::map<std::set<int>, int> dfaStateMap;
    int stateNum = 0;

    DFAState startState(stateNum);
    startState.nfaStates = startSet;

    // 检查是否为接受状态
    for (int nfaState : startSet) {
        auto it = nfa.endStates.find(nfaState);
        if (it != nfa.endStates.end()) {
            if (startState.actionId == -1 || it->second < startState.actionId) {
                startState.actionId = it->second;
            }
        }
    }

    dfa.states[stateNum] = startState;
    dfaStateMap[startSet] = stateNum;
    dfa.startState = stateNum;

    if (startState.actionId != -1) {
        dfa.endStates[stateNum] = startState.actionId;
    }

    stateNum++;

    // 使用队列处理未处理的DFA状态
    std::queue<int> unprocessed;
    unprocessed.push(0);

    while (!unprocessed.empty()) {
        int currentDfaState = unprocessed.front();
        unprocessed.pop();

        const std::set<int>& currentNfaStates = dfa.states[currentDfaState].nfaStates;

        // 对每个输入字符
        for (char c : dfa.alphabet) {
            std::set<int> moveResult = move(nfa, currentNfaStates, c);
            std::set<int> closure = epsilonClosure(nfa, moveResult);

            if (closure.empty()) continue;

            // 检查这个状态集合是否已经存在
            int nextStateNum;
            auto it = dfaStateMap.find(closure);
            if (it == dfaStateMap.end()) {
                // 新状态
                nextStateNum = stateNum++;
                dfaStateMap[closure] = nextStateNum;

                DFAState newState(nextStateNum);
                newState.nfaStates = closure;

                // 检查是否为接受状态
                for (int nfaState : closure) {
                    auto endIt = nfa.endStates.find(nfaState);
                    if (endIt != nfa.endStates.end()) {
                        if (newState.actionId == -1 || endIt->second < newState.actionId) {
                            newState.actionId = endIt->second;
                        }
                    }
                }

                dfa.states[nextStateNum] = newState;

                if (newState.actionId != -1) {
                    dfa.endStates[nextStateNum] = newState.actionId;
                }

                unprocessed.push(nextStateNum);
            } else {
                nextStateNum = it->second;
            }

            // 添加转移
            dfa.states[currentDfaState].edges[c] = nextStateNum;
        }
    }

    dfa.stateCount = stateNum;

    return dfa;
}

// DFA最小化（Hopcroft算法思想）
DFA minimizeDFA(const DFA& dfa) {
    if (dfa.states.empty()) return dfa;

    // 初始划分：接受状态和非接受状态
    std::vector<std::set<int>> partitions;
    std::map<int, int> stateToPartition;

    // 按actionId将接受状态分组
    std::map<int, std::set<int>> acceptGroups;
    for (const auto& pair : dfa.endStates) {
        acceptGroups[pair.second].insert(pair.first);
    }

    // 添加接受状态组
    for (const auto& pair : acceptGroups) {
        for (int state : pair.second) {
            stateToPartition[state] = partitions.size();
        }
        partitions.push_back(pair.second);
    }

    // 添加非接受状态组
    std::set<int> nonAcceptStates;
    for (const auto& pair : dfa.states) {
        if (dfa.endStates.find(pair.first) == dfa.endStates.end()) {
            nonAcceptStates.insert(pair.first);
        }
    }

    if (!nonAcceptStates.empty()) {
        for (int state : nonAcceptStates) {
            stateToPartition[state] = partitions.size();
        }
        partitions.push_back(nonAcceptStates);
    }

    // 迭代细化
    bool changed = true;
    while (changed) {
        changed = false;
        std::vector<std::set<int>> newPartitions;
        std::map<int, int> newStateToPartition;

        for (const auto& group : partitions) {
            if (group.size() <= 1) {
                for (int state : group) {
                    newStateToPartition[state] = newPartitions.size();
                }
                newPartitions.push_back(group);
                continue;
            }

            // 尝试分裂这个组
            std::map<std::vector<int>, std::set<int>> splitGroups;

            for (int state : group) {
                std::vector<int> signature;
                auto it = dfa.states.find(state);
                if (it != dfa.states.end()) {
                    for (char c : dfa.alphabet) {
                        auto edgeIt = it->second.edges.find(c);
                        if (edgeIt != it->second.edges.end()) {
                            signature.push_back(stateToPartition[edgeIt->second]);
                        } else {
                            signature.push_back(-1);
                        }
                    }
                }
                splitGroups[signature].insert(state);
            }

            if (splitGroups.size() > 1) {
                changed = true;
            }

            for (const auto& pair : splitGroups) {
                for (int state : pair.second) {
                    newStateToPartition[state] = newPartitions.size();
                }
                newPartitions.push_back(pair.second);
            }
        }

        partitions = newPartitions;
        stateToPartition = newStateToPartition;
    }

    // 构建最小化DFA
    DFA miniDFA;
    miniDFA.alphabet = dfa.alphabet;

    // 构建状态映射（每个旧状态映射到新状态）
    for (size_t i = 0; i < partitions.size(); i++) {
        for (int oldState : partitions[i]) {
            stateToPartition[oldState] = i;
        }
    }

    // 创建新DFA状态
    for (size_t i = 0; i < partitions.size(); i++) {
        DFAState newState(i);
        int representative = *partitions[i].begin();

        // 复制边
        auto it = dfa.states.find(representative);
        if (it != dfa.states.end()) {
            for (const auto& edge : it->second.edges) {
                newState.edges[edge.first] = stateToPartition[edge.second];
            }
        }

        // 检查是否为接受状态
        auto endIt = dfa.endStates.find(representative);
        if (endIt != dfa.endStates.end()) {
            newState.actionId = endIt->second;
            miniDFA.endStates[i] = endIt->second;
        }

        miniDFA.states[i] = newState;
    }

    // 设置开始状态
    miniDFA.startState = stateToPartition[dfa.startState];
    miniDFA.stateCount = partitions.size();

    std::cout << "Minimized DFA has " << miniDFA.states.size() << " states" << std::endl;

    return miniDFA;
}

// 生成驱动表
DriverTable generateDriverTable(const DFA& dfa) {
    DriverTable table;
    table.startState = dfa.startState;

    // 构建字符到列号的映射
    std::map<char, int> charToCol;
    int colNum = 1;  // 从1开始，0表示无效
    for (char c : dfa.alphabet) {
        charToCol[c] = colNum++;
    }

    // yy_edge_col: 字符到列号的映射（大小256）
    table.yy_edge_col.resize(256, 0);
    for (const auto& pair : charToCol) {
        table.yy_edge_col[(unsigned char)pair.first] = pair.second;
    }

    // 计算每行的列数
    int cols = dfa.alphabet.size() + 1;  // +1因为列号从1开始

    // yy_state_row: 状态行起始索引
    table.yy_state_row.resize(dfa.stateCount);
    for (int i = 0; i < dfa.stateCount; i++) {
        table.yy_state_row[i] = i * cols;
    }

    // yy_next: 状态转换表
    table.yy_next.resize(dfa.stateCount * cols, -1);
    for (const auto& pair : dfa.states) {
        int state = pair.first;
        int rowStart = table.yy_state_row[state];
        for (const auto& edge : pair.second.edges) {
            int col = charToCol[edge.first];
            table.yy_next[rowStart + col] = edge.second;
        }
    }

    // yy_accept: 接受状态表
    table.yy_accept.resize(dfa.stateCount, 0);
    for (const auto& pair : dfa.endStates) {
        // +1因为0表示非接受状态
        table.yy_accept[pair.first] = pair.second + 1;
    }

    // 保存动作规则
    table.actionRules = g_data.rules;

    std::cout << "Driver table generated" << std::endl;
    std::cout << "  States: " << dfa.stateCount << std::endl;
    std::cout << "  Alphabet: " << dfa.alphabet.size() << std::endl;
    std::cout << "  Table size: " << table.yy_next.size() << std::endl;

    return table;
}
