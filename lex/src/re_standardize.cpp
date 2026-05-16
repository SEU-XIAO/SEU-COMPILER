#include "re_standardize.h"
#include "utils.h"

static std::string expandBraces(std::string pattern, const std::map<std::string, std::string>& reMap) {
    std::string result;
    bool changed = true;
    
    while (changed) {
        changed = false;
        result.clear();
        
        for (size_t i = 0; i < pattern.length(); i++) {
            if (pattern[i] == '{' && (i == 0 || pattern[i-1] != '\\')) {
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

static std::string expandBrackets(const std::string& pattern) {
    std::string result;
    for (size_t i = 0; i < pattern.length(); i++) {
        if (pattern[i] == '[' && (i == 0 || pattern[i-1] != '\\')) {
            bool negated = false;
            size_t start = i + 1;
            if (start < pattern.length() && pattern[start] == '^') {
                negated = true;
                start++;
            }
            
            size_t j = start;
            while (j < pattern.length() && pattern[j] != ']') {
                j++;
            }
            
            if (j < pattern.length()) {
                std::string content = pattern.substr(start, j - start);
                std::string expanded;
                
                auto escapeChar = [](char c) -> std::string {
                    if (c == '(' || c == ')' || c == '*' || c == '+' || c == '?' || 
                        c == '|' || c == '$' || c == '@' || c == '{' || c == '}' ||
                        c == '[' || c == ']' || c == '\\' || c == '.' || c == '^' ||
                        c == '"' || c == '\'' || c == ' ' || c == '\t' || c == '\n' ||
                        c == '\r' || c == '\v' || c == '\f') {
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
                    std::set<char> excluded;
                    for (size_t k = 0; k < content.length(); k++) {
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
                            k++;
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
                    
                    bool first = true;
                    for (int c = 1; c < 128; c++) {
                        if (excluded.find((char)c) == excluded.end()) {
                            if (!first) expanded += "|";
                            expanded += escapeChar((char)c);
                            first = false;
                        }
                    }
                } else {
                    bool first = true;
                    for (size_t k = 0; k < content.length(); k++) {
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
                            k++;
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

static std::string convertOperators(const std::string& pattern) {
    std::string result = pattern;
    
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
    
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] == '?' && !isEscaped(i)) {
            if (i == 0) {
                std::cerr << "Error: '?' operator at position 0 has no operand" << std::endl;
                continue;
            }
            
            size_t start;
            if (result[i-1] == ')' && !isEscaped(i-1)) {
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
    
    for (size_t i = 0; i < result.length(); i++) {
        if (result[i] == '+' && !isEscaped(i)) {
            if (i == 0) {
                std::cerr << "Error: '+' operator at position 0 has no operand" << std::endl;
                continue;
            }
            
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

static std::string addConcatOperator(const std::string& pattern) {
    std::string result;
    
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
            
            bool needConcat = false;
            bool wasEscaped = false;
            
            if (curr == '\\') {
                i++;
                result += pattern[i];
                wasEscaped = true;
                if (i + 1 < pattern.length()) {
                    curr = pattern[i];
                    next = pattern[i + 1];
                } else {
                    continue;
                }
            }
            
            bool currIsOperand;
            bool currIsClosing;
            if (wasEscaped) {
                currIsOperand = true;
                currIsClosing = false;
            } else {
                currIsOperand = (curr != '|' && curr != '(' && (curr != ')' || isEscaped(i)) && curr != '*' && curr != '$' && curr != '@');
                currIsClosing = ((curr == ')' && !isEscaped(i)) || curr == '*');
            }
            
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

static std::string escapeRegexChar(char c) {
    if (c == '(' || c == ')' || c == '*' || c == '+' || c == '?' || 
        c == '|' || c == '$' || c == '@' || c == '{' || c == '}' ||
        c == '[' || c == ']' || c == '\\' || c == '.' || c == '^' ||
        c == '"' || c == '\'') {
        return std::string("\\") + c;
    }
    return std::string(1, c);
}

static std::string handleQuotes(const std::string& pattern) {
    std::string result;
    for (size_t i = 0; i < pattern.length(); i++) {
        if (pattern[i] == '"' && (i == 0 || pattern[i-1] != '\\')) {
            size_t j = i + 1;
            int bracketDepth = 0;
            
            while (j < pattern.length()) {
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
                    break;
                }
                j++;
            }
            
            if (j >= pattern.length()) {
                result += pattern[i];
                continue;
            }
            
            std::string content = pattern.substr(i + 1, j - i - 1);
            content = expandBrackets(content);
            
            std::string expanded;
            for (size_t k = 0; k < content.length(); k++) {
                char c = content[k];
                
                if (!expanded.empty()) {
                    expanded += '$';
                }
                
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
                    expanded += escapeRegexChar(c);
                }
            }
            
            if (expanded.empty()) {
                expanded = "@";
            }
            
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

void standardizeRegex() {
    std::cout << "Original definitions:" << std::endl;
    for (const auto& pair : g_data.reMap) {
        std::cout << "  " << pair.first << " = " << pair.second << std::endl;
    }
    
    for (auto& pair : g_data.reMap) {
        std::string& pattern = pair.second;
        pattern = handleQuotes(pattern);
        pattern = expandBrackets(pattern);
        pattern = convertOperators(pattern);
    }
    
    for (auto& rule : g_data.rules) {
        std::string& pattern = rule.pattern;
        pattern = handleQuotes(pattern);
        pattern = expandBrackets(pattern);
        pattern = convertOperators(pattern);
    }
    
    std::cout << "Expanding definitions..." << std::endl;
    for (auto& pair : g_data.reMap) {
        std::cout << "  Before: " << pair.first << " = " << pair.second.substr(0, 100) << (pair.second.length() > 100 ? "..." : "") << std::endl;
        pair.second = expandBraces(pair.second, g_data.reMap);
        std::cout << "  After:  " << pair.first << " = " << pair.second.substr(0, 100) << (pair.second.length() > 100 ? "..." : "") << std::endl;
    }
    
    std::cout << "Expanding rules..." << std::endl;
    for (auto& rule : g_data.rules) {
        rule.pattern = expandBraces(rule.pattern, g_data.reMap);
    }
    
    for (auto& pair : g_data.reMap) {
        pair.second = addConcatOperator(pair.second);
    }
    
    for (auto& rule : g_data.rules) {
        rule.pattern = addConcatOperator(rule.pattern);
        std::cout << "Standardized rule " << rule.ruleId << ": " << rule.pattern << std::endl;
    }
}