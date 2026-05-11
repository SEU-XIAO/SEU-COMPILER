#ifndef NFA_TO_DFA_H
#define NFA_TO_DFA_H

#include "structs.h"

DFA convertNFAtoDFA(const NFA& nfa);
DFA minimizeDFA(const DFA& dfa);
DriverTable generateDriverTable(const DFA& dfa);

#endif