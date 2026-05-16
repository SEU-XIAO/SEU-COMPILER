#include "parser.h"
#include "utils.h"

bool parseLexFile(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open file " << filepath << std::endl;
        return false;
    }
    
    enum State {
        INITIAL,
        DECLARATION,
        DEFINITION,
        RULE,
        USER_CODE
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
                    state = DEFINITION;
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
                    state = DECLARATION;
                    inDeclaration = true;
                } else if (!trimmed.empty() && trimmed[0] != '#' && trimmed[0] != '/' && trimmed[0] != '*') {
                    size_t pos = trimmed.find_first_of(" \t");
                    if (pos != std::string::npos) {
                        std::string name = trim(trimmed.substr(0, pos));
                        std::string pattern = trim(trimmed.substr(pos));
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
                            if (i > 0 && (trimmed[i-1] == ' ' || trimmed[i-1] == '\t')) {
                                patternEnd = i;
                                break;
                            }
                        } else if (!inQuotes && !inBrackets && trimmed[i] == '}' && (i == 0 || trimmed[i-1] != '\\')) {
                            inBraces = false;
                        } else if (!inQuotes && !inBrackets && !inBraces && (trimmed[i] == ' ' || trimmed[i] == '\t')) {
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
                    
                    if (action.length() >= 2 && action[0] == '{' && action[action.length()-1] == '}') {
                        action = action.substr(1, action.length() - 2);
                    }
                    
                    if (!pattern.empty() && pattern[0] != '*') {
                        Rule rule;
                        rule.pattern = pattern;
                        rule.ruleId = ruleId++;
                        
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
                                currentAction = trim(currentAction);
                                if (!currentAction.empty()) {
                                    rule.actions.push_back(currentAction);
                                }
                                currentAction.clear();
                            } else {
                                currentAction += c;
                            }
                        }
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