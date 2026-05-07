#include "parser.h"
#include "utils.h"

// 解析.l文件
// .l文件格式:
// %{ ... %}          - 声明部分(直接复制到输出)
// 定义段              - 正则表达式别名定义
// %%                 - 分隔符
// 规则段              - 正则表达式 + 动作
// %%                 - 分隔符
// 用户代码段          - 直接复制到输出
bool parseLexFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return false;
    }
    
    enum State {
        INITIAL,        // 初始状态
        DECLARATION,    // %{ %} 声明部分
        DEFINITION,     // 定义段
        RULE,           // 规则段
        USER_CODE       // 用户代码段
    };
    
    State state = INITIAL;
    std::string line;
    std::string declarationBuffer;
    bool inDeclaration = false;
    int ruleId = 0;
    
    while (std::getline(file, line)) {
        std::string trimmed = trim(line);
        
        switch (state) {
            case INITIAL:
                if (trimmed == "%{") {
                    state = DECLARATION;
                    inDeclaration = true;
                } else if (trimmed == "%%") {
                    state = RULE;
                } else if (!trimmed.empty() && trimmed[0] != '/' && trimmed[0] != '#') {
                    // 定义段（跳过注释和预处理器指令）
                    state = DEFINITION;
                    // 处理当前行
                    size_t pos = trimmed.find_first_of(" \t");
                    if (pos != std::string::npos) {
                        std::string name = trim(trimmed.substr(0, pos));
                        std::string pattern = trim(trimmed.substr(pos));
                        g_data.reMap[name] = pattern;
                    }
                }
                break;
                
            case DECLARATION:
                if (trimmed == "%}") {
                    state = DEFINITION;
                    inDeclaration = false;
                    g_data.part1 = declarationBuffer;
                } else {
                    declarationBuffer += line + "\n";
                }
                break;
                
            case DEFINITION:
                if (trimmed == "%%") {
                    state = RULE;
                } else if (trimmed == "%{") {
                    // 在定义段中遇到 %{，进入声明状态
                    state = DECLARATION;
                    inDeclaration = true;
                } else if (!trimmed.empty() && trimmed[0] != '#' && trimmed[0] != '/' && trimmed[0] != '*') {
                    // 解析定义: name pattern
                    size_t pos = trimmed.find_first_of(" \t");
                    if (pos != std::string::npos) {
                        std::string name = trim(trimmed.substr(0, pos));
                        std::string pattern = trim(trimmed.substr(pos));
                        // 去除可能的注释
                        size_t commentPos = pattern.find("/*");
                        if (commentPos != std::string::npos) {
                            pattern = trim(pattern.substr(0, commentPos));
                        }
                        g_data.reMap[name] = pattern;
                    }
                }
                break;
                
            case RULE:
                if (trimmed == "%%") {
                    state = USER_CODE;
                } else if (!trimmed.empty() && trimmed[0] != '#' && 
                          !(trimmed.length() >= 2 && trimmed[0] == '/' && trimmed[1] == '/') &&
                          !(trimmed.length() >= 2 && trimmed[0] == '/' && trimmed[1] == '*') &&
                          !(trimmed.length() >= 2 && trimmed[0] == '*' && trimmed[1] == '/')) {
                    // 解析规则: pattern { action }
                    // 找到第一个非空白字符开始，到第一个空格或制表符
                    size_t patternEnd = 0;
                    bool inQuotes = false;
                    bool inBraces = false;
                    bool inBrackets = false;
                    
                    for (size_t i = 0; i < trimmed.length(); i++) {
                        if (trimmed[i] == '"' && (i == 0 || trimmed[i-1] != '\\')) {
                            inQuotes = !inQuotes;
                        } else if (!inQuotes && !inBrackets && trimmed[i] == '[' && (i == 0 || trimmed[i-1] != '\\')) {
                            inBrackets = true;
                        } else if (!inQuotes && inBrackets && trimmed[i] == ']' && (i == 0 || trimmed[i-1] != '\\')) {
                            inBrackets = false;
                        } else if (!inQuotes && !inBrackets && trimmed[i] == '{' && (i == 0 || trimmed[i-1] != '\\')) {
                            inBraces = true;
                            // 检查是否是动作的开始（前面有空格或制表符）
                            if (i > 0 && (trimmed[i-1] == ' ' || trimmed[i-1] == '\t')) {
                                patternEnd = i;
                                break;
                            }
                        } else if (!inQuotes && !inBrackets && trimmed[i] == '}' && (i == 0 || trimmed[i-1] != '\\')) {
                            inBraces = false;
                        } else if (!inQuotes && !inBrackets && !inBraces && (trimmed[i] == ' ' || trimmed[i] == '\t')) {
                            // 检查下一个非空白字符是否是'{'，如果是，则这是pattern和action的分界
                            size_t j = i;
                            while (j < trimmed.length() && (trimmed[j] == ' ' || trimmed[j] == '\t')) {
                                j++;
                            }
                            if (j < trimmed.length() && trimmed[j] == '{') {
                                patternEnd = i;
                                break;
                            }
                        }
                    }
                    
                    if (patternEnd == 0) patternEnd = trimmed.length();
                    
                    std::string pattern = trim(trimmed.substr(0, patternEnd));
                    std::string action = trim(trimmed.substr(patternEnd));
                    
                    // 去除动作中的大括号
                    if (action.length() >= 2 && action[0] == '{' && action[action.length()-1] == '}') {
                        action = action.substr(1, action.length() - 2);
                    }
                    
                    // 跳过纯注释的规则
                    if (!pattern.empty() && pattern[0] != '*') {
                        Rule rule;
                        rule.pattern = pattern;
                        rule.ruleId = ruleId++;
                        
                        // 分割多行动作（正确处理单引号中的分号）
                        std::string currentAction;
                        bool inSingleQuote = false;
                        bool inDoubleQuote = false;
                        for (size_t i = 0; i < action.length(); i++) {
                            char c = action[i];
                            if (c == '"' && (i == 0 || action[i-1] != '\\')) {
                                inDoubleQuote = !inDoubleQuote;
                                currentAction += c;
                            } else if (c == '\'' && (i == 0 || action[i-1] != '\\') && !inDoubleQuote) {
                                inSingleQuote = !inSingleQuote;
                                currentAction += c;
                            } else if (c == ';' && !inSingleQuote && !inDoubleQuote) {
                                // 分号作为语句分隔符
                                currentAction = trim(currentAction);
                                if (!currentAction.empty()) {
                                    rule.actions.push_back(currentAction);
                                }
                                currentAction.clear();
                            } else {
                                currentAction += c;
                            }
                        }
                        // 处理最后一个动作
                        currentAction = trim(currentAction);
                        if (!currentAction.empty()) {
                            rule.actions.push_back(currentAction);
                        }
                        
                        g_data.rules.push_back(rule);
                    }
                }
                break;
                
            case USER_CODE:
                g_data.part4 += line + "\n";
                break;
        }
    }
    
    file.close();
    
    std::cout << "Parsed " << g_data.rules.size() << " rules" << std::endl;
    std::cout << "Parsed " << g_data.reMap.size() << " definitions" << std::endl;
    
    return true;
}
