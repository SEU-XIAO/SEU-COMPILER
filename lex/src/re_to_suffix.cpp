#include "re_to_suffix.h"
#include "utils.h"
#include <stack>

static int getPriority(char op) {
    switch (op) {
        case '*': return 3;
        case '$': return 2;
        case '|': return 1;
        default: return 0;
    }
}

static bool isOperator(char c) {
    return c == '*' || c == '$' || c == '|';
}

static bool isEscaped(const std::string& str, size_t pos) {
    if (pos == 0) return false;
    int backslashCount = 0;
    size_t p = pos - 1;
    while (p < str.length() && str[p] == '\\') {
        backslashCount++;
        if (p == 0) break;
        p--;
    }
    return (backslashCount % 2) == 1;
}

static std::string toSuffix(const std::string& infix) {
    std::string output;
    std::stack<char> opStack;
    
    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];
        
        if (c == '\\' && i + 1 < infix.length() && !isEscaped(infix, i)) {
            output += '\\';
            output += infix[i + 1];
            i++;
            continue;
        }
        
        if (isEscaped(infix, i)) {
            continue;
        } else if (c == '(') {
            opStack.push(c);
        } else if (c == ')') {
            while (!opStack.empty() && opStack.top() != '(') {
                output += opStack.top();
                opStack.pop();
            }
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop();
            }
        } else if (isOperator(c)) {
            while (!opStack.empty() && opStack.top() != '(' &&
                   getPriority(opStack.top()) >= getPriority(c)) {
                output += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        } else {
            output += c;
        }
    }
    
    while (!opStack.empty()) {
        output += opStack.top();
        opStack.pop();
    }
    
    return output;
}

void convertToSuffix() {
    for (auto& rule : g_data.rules) {
        std::string suffix = toSuffix(rule.pattern);
        rule.pattern = suffix;
        std::cout << "Suffix rule " << rule.ruleId << ": " << suffix << std::endl;
    }
}