#ifndef NFA_TO_DFA_H
#define NFA_TO_DFA_H

#include "structs.h"

// 使用子集构造法将NFA转换为DFA
DFA convertNFAtoDFA(const NFA& nfa);

// DFA最小化
DFA minimizeDFA(const DFA& dfa);

// 生成驱动表
DriverTable generateDriverTable(const DFA& dfa);

#endif // NFA_TO_DFA_H
