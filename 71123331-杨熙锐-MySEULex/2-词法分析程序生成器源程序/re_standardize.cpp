#include "re_standardize.h"
#include "utils.h"

// 展开花括号别名 {name}
// 递归展开直到没有更多的花括号
static std::string expandBraces(std::string pattern, const std::map<std::string, std::string>& reMap) {
    std::string result;
    bool changed = true;
    
    while (changed) {
        changed = false;
        result.clear();
        
        for (size_t i = 0; i < pattern.length(); i++) {
            if (pattern[i] == '{' && (i == 0 || pattern[i-1] != '\\')) {
                // 找到匹配的 }
                size_t j = i + 1;
                while (j < pattern.length() && pattern[j] != '}') {
                    j++;
                }
                if (j < pattern.length()) {
                    std::string name = pattern.substr(i + 1, j - i - 1);
                    auto it = reMap.find(name);
                    if (it != reMap.end()) {
                        result += "(" + it->second + ")";
                        i = j;
                        changed = true;
                        continue;
                    }
                }
            }
            result += pattern[i];
        }
        
        pattern = result;
    }
    
    return pattern;
}

// 展开方括号字符集 [a-z] [abc] [^a-z]
static std::string expandBrackets(const std::string& pattern) {
    std::string result;
    for (size_t i = 0; i < pattern.length(); i++) {
        if (pattern[i] == '[' && (i == 0 || pattern[i-1] != '\\')) {
            // 检查是否为否定[^...]
            bool negated = false;
            size_t start = i + 1;
            if (start < pattern.length() && pattern[start] == '^') {
                negated = true;
                start++;
            }
            
            // 找到匹配的 ]
            size_t j = start;
            while (j < pattern.length() && pattern[j] != ']') {
                j++;
            }
            
            if (j < pattern.length()) {
                std::string content = pattern.substr(start, j - start);
                std::string expanded;
                
                // 辅助函数：转义特殊字符
                auto escapeChar = [](char c) -> std::string {
                    if (c == '(' || c == ')' || c == '*' || c == '+' || c == '?' || 
                        c == '|' || c == '$' || c == '@' || c == '{' || c == '}' ||
                        c == '[' || c == ']' || c == '\\' || c == '.' || c == '^' ||
                        c == '"' || c == '\'' || c == ' ' || c == '\t' || c == '\n' ||
                        c == '\r' || c == '\v' || c == '\f') {
                        // 对于空白字符，使用转义表示
                        switch (c) {
                            case ' ': return "\\ ";
                            case '\t': return "\\t";
                            case '\n': return "\\n";
                            case '\r': return "\\r";
                            case '\v': return "\\v";
                            case '\f': return "\\f";
                            default: return std::string("\\") + c;
                        }
                    }
                    return std::string(1, c);
                };
                
                if (negated) {
                    // 否定字符集：包含所有ASCII字符除了指定的
                    // 简化处理：生成一个大的或表达式
                    std::set<char> excluded;
                    for (size_t k = 0; k < content.length(); k++) {
                        // 处理转义序列（如 \n, \t 等）
                        if (content[k] == '\\' && k + 1 < content.length()) {
                            char escapedChar;
                            switch (content[k+1]) {
                                case 'n': escapedChar = '\n'; break;
                                case 't': escapedChar = '\t'; break;
                                case 'r': escapedChar = '\r'; break;
                                case 'v': escapedChar = '\v'; break;
                                case 'f': escapedChar = '\f'; break;
                                case '\\': escapedChar = '\\'; break;
                                case ']': escapedChar = ']'; break;
                                default: escapedChar = content[k+1]; break;
                            }
                            excluded.insert(escapedChar);
                            k++;  // 跳过下一个字符
                            continue;
                        }
                        if (k + 2 < content.length() && content[k+1] == '-') {
                            for (char c = content[k]; c <= content[k+2]; c++) {
                                excluded.insert(c);
                            }
                            k += 2;
                        } else {
                            excluded.insert(content[k]);
                        }
                    }
                    
                    // 生成包含的字符（包含所有非NUL的ASCII字符1-127）
                    bool first = true;
                    for (int c = 1; c < 128; c++) {
                        if (excluded.find((char)c) == excluded.end()) {
                            if (!first) expanded += "|";
                            expanded += escapeChar((char)c);
                            first = false;
                        }
                    }
                } else {
                    // 普通字符集
                    bool first = true;
                    for (size_t k = 0; k < content.length(); k++) {
                        // 处理转义序列（如 \n, \t 等）
                        if (content[k] == '\\' && k + 1 < content.length()) {
                            char escapedChar;
                            switch (content[k+1]) {
                                case 'n': escapedChar = '\n'; break;
                                case 't': escapedChar = '\t'; break;
                                case 'r': escapedChar = '\r'; break;
                                case 'v': escapedChar = '\v'; break;
                                case 'f': escapedChar = '\f'; break;
                                case '\\': escapedChar = '\\'; break;
                                case ']': escapedChar = ']'; break;
                                case '-': escapedChar = '-'; break;
                                default: escapedChar = content[k+1]; break;
                            }
                            if (!first) expanded += "|";
                            expanded += escapeChar(escapedChar);
                            first = false;
                            k++;  // 跳过下一个字符
                            continue;
                        }
                        if (k + 2 < content.length() && content[k+1] == '-') {
                            for (char c = content[k]; c <= content[k+2]; c++) {
                                if (!first) expanded += "|";
                                expanded += escapeChar(c);
                                first = false;
                            }
                            k += 2;
                        } else {
                            if (!first) expanded += "|";
                            expanded += escapeChar(content[k]);
                            first = false;
                        }
                    }
                }
                                     
                result += "(" + expanded + ")";
                i = j;
                continue;
            }
        }
        result += pattern[i];
    }
    return result;
}

// 转换 ? 和 + 操作符
// a? -> (@|a)  零次或一次
// a+ -> aa*     一次或多次
static std::string convertOperators(const std::string& pattern) {
    std::string result = pattern;
    
    // 辅助函数：检查位置i的字符是否被转义
    auto isEscaped = [&](size_t pos) -> bool {
        if (pos == 0) return false;
        int backslashCount = 0;
        size_t p = pos - 1;
        while (p < result.length() && result[p] == '\\') {
            backslashCount++;
            if (p == 0) break;
            p--;
        }
        return (backslashCount % 2) == 1;
    };
    
    // 处理 ? (需要找到前面的操作数范围)
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] == '?' && !isEscaped(i)) {
            // 检查是否有前面的操作数
            if (i == 0) {
                std::cerr << "Error: '?' operator at position 0 has no operand" << std::endl;
                continue;
            }
            
            // 找到前面的操作数
            size_t start;
            if (result[i-1] == ')' && !isEscaped(i-1)) {
                // 找到匹配的 (
                int depth = 1;
                if (i < 2) {
                    std::cerr << "Error: Unmatched ')' before '?'" << std::endl;
                    continue;
                }
                start = i - 2;
                while (depth > 0) {
                    if (result[start] == ')' && !isEscaped(start)) depth++;
                    if (result[start] == '(' && !isEscaped(start)) depth--;
                    if (depth > 0) {
                        if (start == 0) {
                            std::cerr << "Error: Unmatched ')' before '?'" << std::endl;
                            break;
                        }
                        start--;
                    }
                }
            } else if (result[i-1] == '}' && !isEscaped(i-1)) {
                // 找到匹配的 {
                int depth = 1;
                if (i < 2) {
                    std::cerr << "Error: Unmatched '}' before '?'" << std::endl;
                    continue;
                }
                start = i - 2;
                while (depth > 0) {
                    if (result[start] == '}' && !isEscaped(start)) depth++;
                    if (result[start] == '{' && !isEscaped(start)) depth--;
                    if (depth > 0) {
                        if (start == 0) {
                            std::cerr << "Error: Unmatched '}' before '?'" << std::endl;
                            break;
                        }
                        start--;
                    }
                }
            } else {
                start = i - 1;
                // 如果该字符是转义序列的一部分，需要包含前面的反斜杠
                if (isEscaped(start)) {
                    start--;
                }
            }
            
            std::string op = result.substr(start, i - start);
            std::string replacement = "(@|" + op + ")";
            result = result.substr(0, start) + replacement + result.substr(i + 1);
            i = start + replacement.length() - 1;
        }
    }
    
    // 处理 +
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] == '+' && !isEscaped(i)) {
            // 检查是否有前面的操作数
            if (i == 0) {
                std::cerr << "Error: '+' operator at position 0 has no operand" << std::endl;
                continue;
            }
            
            // 找到前面的操作数
            size_t start;
            if (result[i-1] == ')' && !isEscaped(i-1)) {
                int depth = 1;
                if (i < 2) {
                    std::cerr << "Error: Unmatched ')' before '+'" << std::endl;
                    continue;
                }
                start = i - 2;
                while (depth > 0) {
                    if (result[start] == ')' && !isEscaped(start)) depth++;
                    if (result[start] == '(' && !isEscaped(start)) depth--;
                    if (depth > 0) {
                        if (start == 0) {
                            std::cerr << "Error: Unmatched ')' before '+'" << std::endl;
                            break;
                        }
                        start--;
                    }
                }
            } else if (result[i-1] == '}' && !isEscaped(i-1)) {
                // 找到匹配的 {
                int depth = 1;
                if (i < 2) {
                    std::cerr << "Error: Unmatched '}' before '+'" << std::endl;
                    continue;
                }
                start = i - 2;
                while (depth > 0) {
                    if (result[start] == '}' && !isEscaped(start)) depth++;
                    if (result[start] == '{' && !isEscaped(start)) depth--;
                    if (depth > 0) {
                        if (start == 0) {
                            std::cerr << "Error: Unmatched '}' before '+'" << std::endl;
                            break;
                        }
                        start--;
                    }
                }
            } else {
                start = i - 1;
                // 如果该字符是转义序列的一部分，需要包含前面的反斜杠
                if (isEscaped(start)) {
                    start--;
                }
            }
            
            std::string op = result.substr(start, i - start);
            std::string replacement = "(" + op + ")(" + op + ")*";
            result = result.substr(0, start) + replacement + result.substr(i + 1);
            i = start + replacement.length() - 1;
        }
    }
    
    return result;
}

// 插入显式连接符 $
// ab -> a$b
// a*b -> a*$b
static std::string addConcatOperator(const std::string& pattern) {
    std::string result;
    
    // 辅助函数：检查位置i的字符是否被转义
    auto isEscaped = [&](size_t pos) -> bool {
        if (pos == 0) return false;
        int backslashCount = 0;
        size_t p = pos - 1;
        while (p < pattern.length() && pattern[p] == '\\') {
            backslashCount++;
            if (p == 0) break;
            p--;
        }
        return (backslashCount % 2) == 1;
    };
    
    for (size_t i = 0; i < pattern.length(); i++) {
        result += pattern[i];
        
        if (i + 1 < pattern.length()) {
            char curr = pattern[i];
            char next = pattern[i + 1];
            
            // 判断是否需要插入连接符
            bool needConcat = false;
            bool wasEscaped = false;
            
            // 如果当前字符是转义符，和下一个字符一起处理
            if (curr == '\\') {
                // 跳过下一个字符（被转义的字符）
                i++;
                result += pattern[i];  // 添加被转义的字符
                wasEscaped = true;
                // 转义序列作为一个整体，后面不需要连接符（除非后面还有字符）
                // 检查转义序列后面是否还有字符
                if (i + 1 < pattern.length()) {
                    curr = pattern[i];     // 更新 curr 为被转义的字符
                    next = pattern[i + 1]; // 更新 next 为转义序列后的字符
                    // 继续检查是否需要连接符（在转义序列之后）
                } else {
                    // 转义序列在字符串末尾，不需要连接符
                    continue;
                }
            }
            
            // 当前字符是操作数或 ) 或 *（考虑转义）
            bool currIsOperand;
            bool currIsClosing;
            if (wasEscaped) {
                // 转义字符始终是操作数（字面量），即使它看起来像运算符
                currIsOperand = true;
                currIsClosing = false;
            } else {
                currIsOperand = (curr != '|' && curr != '(' && (curr != ')' || isEscaped(i)) && curr != '*' && curr != '$' && curr != '@');
                currIsClosing = ((curr == ')' && !isEscaped(i)) || curr == '*');
            }
            
            // 下一个字符是操作数或 (（考虑转义）
            bool nextIsOperand = (next != '|' && (next != ')' || isEscaped(i+1)) && next != '*' && next != '$' && next != '@');
            bool nextIsOpening = (next == '(' && !isEscaped(i+1));
            
            if ((currIsOperand || currIsClosing) && (nextIsOperand || nextIsOpening)) {
                needConcat = true;
            }
            
            if (needConcat) {
                result += '$';
            }
        }
    }
    
    return result;
}

// 前向声明
static std::string expandBrackets(const std::string& pattern);

// 辅助函数：转义特殊字符
static std::string escapeRegexChar(char c) {
    if (c == '(' || c == ')' || c == '*' || c == '+' || c == '?' || 
        c == '|' || c == '$' || c == '@' || c == '{' || c == '}' ||
        c == '[' || c == ']' || c == '\\' || c == '.' || c == '^' ||
        c == '"' || c == '\'') {
        return std::string("\\") + c;
    }
    return std::string(1, c);
}

// 处理字符串字面量 "abc"
// 这个函数在expandBrackets之前调用
// 它会提取字符串内容，展开其中的方括号，然后转换为连接形式
static std::string handleQuotes(const std::string& pattern) {
    std::string result;
    for (size_t i = 0; i < pattern.length(); i++) {
        // 检查是否是字符串开始（未被转义的双引号）
        if (pattern[i] == '"' && (i == 0 || pattern[i-1] != '\\')) {
            // 找到匹配的结束引号
            size_t j = i + 1;
            int bracketDepth = 0;
            
            while (j < pattern.length()) {
                // 辅助函数：检查位置pos的字符是否被转义
                auto isEscapedAt = [&](size_t pos) -> bool {
                    if (pos == 0) return false;
                    int backslashCount = 0;
                    size_t p = pos - 1;
                    while (p < pattern.length() && pattern[p] == '\\') {
                        backslashCount++;
                        if (p == 0) break;
                        p--;
                    }
                    return (backslashCount % 2) == 1;
                };
                
                if (pattern[j] == '[' && !isEscapedAt(j)) {
                    bracketDepth++;
                } else if (pattern[j] == ']' && !isEscapedAt(j)) {
                    bracketDepth--;
                } else if (pattern[j] == '"' && !isEscapedAt(j) && bracketDepth == 0) {
                    // 找到结束引号
                    break;
                }
                j++;
            }
            
            if (j >= pattern.length()) {
                // 未找到结束引号，保持原样
                result += pattern[i];
                continue;
            }
            
            // 提取字符串内容（不包括引号）
            std::string content = pattern.substr(i + 1, j - i - 1);
            
            // 对字符串内容展开方括号
            content = expandBrackets(content);
            
            // 将内容转换为连接形式
            std::string expanded;
            for (size_t k = 0; k < content.length(); k++) {
                char c = content[k];
                
                // 在字符串字面量中，所有字符都是普通字符（除了转义序列）
                // 即使是操作符（| * ? +）也应该被转义
                
                // 添加$连接符（除了第一个字符）
                if (!expanded.empty()) {
                    expanded += '$';
                }
                
                // 处理转义序列
                if (c == '\\' && k + 1 < content.length()) {
                    char nextChar = content[k + 1];
                    char actualChar;
                    switch (nextChar) {
                        case 'n': actualChar = '\n'; break;
                        case 't': actualChar = '\t'; break;
                        case 'r': actualChar = '\r'; break;
                        case 'v': actualChar = '\v'; break;
                        case 'f': actualChar = '\f'; break;
                        case '\\': actualChar = '\\'; break;
                        case '"': actualChar = '"'; break;
                        case '\'': actualChar = '\''; break;
                        default: actualChar = nextChar; break;
                    }
                    expanded += escapeRegexChar(actualChar);
                    k++;
                } else {
                    // 所有字符都需要转义，包括操作符
                    expanded += escapeRegexChar(c);
                }
            }
            
            if (expanded.empty()) {
                expanded = "@";  // 空串用epsilon表示
            }
            
            // 包装在括号中（除了简单的情况）
            if (expanded.find('$') != std::string::npos || 
                expanded.find('|') != std::string::npos ||
                expanded.find('*') != std::string::npos) {
                result += "(" + expanded + ")";
            } else {
                result += expanded;
            }
            i = j;
            continue;
        }
        result += pattern[i];
    }
    return result;
}

// 正则表达式标准化主函数
void standardizeRegex() {
    // Debug: 打印原始定义
    std::cout << "Original definitions:" << std::endl;
    for (const auto& pair : g_data.reMap) {
        std::cout << "  " << pair.first << " = " << pair.second << std::endl;
    }
    
    // Step 1: 先预处理定义中的正则表达式（不添加连接符）
    for (auto& pair : g_data.reMap) {
        std::string& pattern = pair.second;
        
        // 1. 处理字符串字面量（在方括号展开之前，保留字符串的原始结构）
        pattern = handleQuotes(pattern);
        
        // 2. 展开方括号字符集
        pattern = expandBrackets(pattern);
        
        // 3. 转换 ? 和 + 操作符
        pattern = convertOperators(pattern);
    }
    
    // Step 2: 预处理规则中的正则表达式（不添加连接符）
    for (auto& rule : g_data.rules) {
        std::string& pattern = rule.pattern;
        
        // 1. 处理字符串字面量（在方括号展开之前）
        pattern = handleQuotes(pattern);
        
        // 2. 展开方括号字符集
        pattern = expandBrackets(pattern);
        
        // 3. 转换 ? 和 + 操作符
        pattern = convertOperators(pattern);
    }
    
    // Step 3: 展开花括号别名（此时定义和规则都还没有连接符）
    // 先展开定义中的别名引用（定义可能引用其他定义）
    std::cout << "Expanding definitions..." << std::endl;
    for (auto& pair : g_data.reMap) {
        std::cout << "  Before: " << pair.first << " = " << pair.second.substr(0, 100) << (pair.second.length() > 100 ? "..." : "") << std::endl;
        pair.second = expandBraces(pair.second, g_data.reMap);
        std::cout << "  After:  " << pair.first << " = " << pair.second.substr(0, 100) << (pair.second.length() > 100 ? "..." : "") << std::endl;
    }
    
    // 再展开规则中的别名
    std::cout << "Expanding rules..." << std::endl;
    for (auto& rule : g_data.rules) {
        rule.pattern = expandBraces(rule.pattern, g_data.reMap);
    }
    
    // Step 4: 最后插入连接符
    for (auto& pair : g_data.reMap) {
        pair.second = addConcatOperator(pair.second);
    }
    
    for (auto& rule : g_data.rules) {
        rule.pattern = addConcatOperator(rule.pattern);
        std::cout << "Standardized rule " << rule.ruleId << ": " << rule.pattern << std::endl;
    }
}
