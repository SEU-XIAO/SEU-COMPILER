#include "re_to_suffix.h"
#include "utils.h"
#include <stack>

// 获取运算符优先级
// * (闭包) > $ (连接) > | (或)
static int getPriority(char op) {
    switch (op) {
        case '*': return 3;
        case '$': return 2;
        case '|': return 1;
        default: return 0;
    }
}

// 判断是否为运算符
static bool isOperator(char c) {
    return c == '*' || c == '$' || c == '|';
}

// 判断位置i的字符是否被转义
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

// 将单个正则表达式转换为后缀形式
static std::string toSuffix(const std::string& infix) {
    std::string output;
    std::stack<char> opStack;
    
    for (size_t i = 0; i < infix.length(); i++) {
        char c = infix[i];
        
        // 如果当前字符是转义符，和下一个字符一起作为普通字符处理
        if (c == '\\' && i + 1 < infix.length() && !isEscaped(infix, i)) {
            // 输出转义符和被转义的字符
            output += '\\';
            output += infix[i + 1];
            i++;  // 跳过下一个字符
            continue;
        }
        
        // 如果被转义，跳过（已经被前面的转义符处理了）
        if (isEscaped(infix, i)) {
            continue;
        } else if (c == '(') {
            // 左括号压栈
            opStack.push(c);
        } else if (c == ')') {
            // 右括号：弹出直到左括号
            while (!opStack.empty() && opStack.top() != '(') {
                output += opStack.top();
                opStack.pop();
            }
            // 弹出左括号
            if (!opStack.empty() && opStack.top() == '(') {
                opStack.pop();
            }
        } else if (isOperator(c)) {
            // 运算符
            // 弹出栈顶优先级 >= 当前运算符的元素
            while (!opStack.empty() && opStack.top() != '(' &&
                   getPriority(opStack.top()) >= getPriority(c)) {
                output += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        } else {
            // 普通字符直接输出
            output += c;
        }
    }
    
    // 弹出栈中剩余元素
    while (!opStack.empty()) {
        output += opStack.top();
        opStack.pop();
    }
    
    return output;
}

// 转换所有规则的正则表达式为后缀形式
void convertToSuffix() {
    for (auto& rule : g_data.rules) {
        std::string suffix = toSuffix(rule.pattern);
        rule.pattern = suffix;
        std::cout << "Suffix rule " << rule.ruleId << ": " << suffix << std::endl;
    }
}
