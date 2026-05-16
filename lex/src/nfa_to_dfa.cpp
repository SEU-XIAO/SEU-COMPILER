#include "nfa_to_dfa.h"
#include "utils.h"
#include <queue>

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

DFA convertNFAtoDFA(const NFA& nfa) {
    DFA dfa;

    for (const auto& pair : nfa.states) {
        for (const auto& edge : pair.second.edges) {
            if (edge.first != '\0') {
                dfa.alphabet.insert(edge.first);
            }
        }
    }

    std::set<int> startSet = epsilonClosure(nfa, {nfa.startState});

    std::map<std::set<int>, int> dfaStateMap;
    int stateNum = 0;

    DFAState startState(stateNum);
    startState.nfaStates = startSet;

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

    std::queue<int> unprocessed;
    unprocessed.push(0);

    while (!unprocessed.empty()) {
        int currentDfaState = unprocessed.front();
        unprocessed.pop();

        const std::set<int>& currentNfaStates = dfa.states[currentDfaState].nfaStates;

        for (char c : dfa.alphabet) {
            std::set<int> moveResult = move(nfa, currentNfaStates, c);
            std::set<int> closure = epsilonClosure(nfa, moveResult);

            if (closure.empty()) continue;

            int nextStateNum;
            auto it = dfaStateMap.find(closure);
            if (it == dfaStateMap.end()) {
                nextStateNum = stateNum++;
                dfaStateMap[closure] = nextStateNum;

                DFAState newState(nextStateNum);
                newState.nfaStates = closure;

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

            dfa.states[currentDfaState].edges[c] = nextStateNum;
        }
    }

    dfa.stateCount = stateNum;

    return dfa;
}

DFA minimizeDFA(const DFA& dfa) {
    if (dfa.states.empty()) return dfa;

    std::vector<std::set<int>> partitions;
    std::map<int, int> stateToPartition;

    std::map<int, std::set<int>> acceptGroups;
    for (const auto& pair : dfa.endStates) {
        acceptGroups[pair.second].insert(pair.first);
    }

    for (const auto& pair : acceptGroups) {
        for (int state : pair.second) {
            stateToPartition[state] = partitions.size();
        }
        partitions.push_back(pair.second);
    }

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

    DFA miniDFA;
    miniDFA.alphabet = dfa.alphabet;

    for (size_t i = 0; i < partitions.size(); i++) {
        for (int oldState : partitions[i]) {
            stateToPartition[oldState] = i;
        }
    }

    for (size_t i = 0; i < partitions.size(); i++) {
        DFAState newState(i);
        int representative = *partitions[i].begin();

        auto it = dfa.states.find(representative);
        if (it != dfa.states.end()) {
            for (const auto& edge : it->second.edges) {
                newState.edges[edge.first] = stateToPartition[edge.second];
            }
        }

        auto endIt = dfa.endStates.find(representative);
        if (endIt != dfa.endStates.end()) {
            newState.actionId = endIt->second;
            miniDFA.endStates[i] = endIt->second;
        }

        miniDFA.states[i] = newState;
    }

    miniDFA.startState = stateToPartition[dfa.startState];
    miniDFA.stateCount = partitions.size();

    std::cout << "Minimized DFA has " << miniDFA.states.size() << " states" << std::endl;

    return miniDFA;
}

DriverTable generateDriverTable(const DFA& dfa) {
    DriverTable table;
    table.startState = dfa.startState;

    std::map<char, int> charToCol;
    int colNum = 1;
    for (char c : dfa.alphabet) {
        charToCol[c] = colNum++;
    }

    table.yy_edge_col.resize(256, 0);
    for (const auto& pair : charToCol) {
        table.yy_edge_col[(unsigned char)pair.first] = pair.second;
    }

    int cols = dfa.alphabet.size() + 1;

    table.yy_state_row.resize(dfa.stateCount);
    for (int i = 0; i < dfa.stateCount; i++) {
        table.yy_state_row[i] = i * cols;
    }

    table.yy_next.resize(dfa.stateCount * cols, -1);
    for (const auto& pair : dfa.states) {
        int state = pair.first;
        int rowStart = table.yy_state_row[state];
        for (const auto& edge : pair.second.edges) {
            int col = charToCol[edge.first];
            table.yy_next[rowStart + col] = edge.second;
        }
    }

    table.yy_accept.resize(dfa.stateCount, 0);
    for (const auto& pair : dfa.endStates) {
        table.yy_accept[pair.first] = pair.second + 1;
    }

    table.actionRules = g_data.rules;

    std::cout << "Driver table generated" << std::endl;
    std::cout << "  States: " << dfa.stateCount << std::endl;
    std::cout << "  Alphabet: " << dfa.alphabet.size() << std::endl;
    std::cout << "  Table size: " << table.yy_next.size() << std::endl;

    return table;
}