#include "structs.h"
#include "parser.h"
#include "re_standardize.h"
#include "re_to_suffix.h"
#include "suffix_to_nfa.h"
#include "nfa_to_dfa.h"
#include "code_generator.h"
#include <ctime>

// 全局数据定义
GlobalData g_data;

void printUsage(const char* program) {
    std::cout << "Usage: " << program << " <input.l> [output.cpp]" << std::endl;
    std::cout << "  input.l    - Lex specification file" << std::endl;
    std::cout << "  output.cpp - Output lexer code (default: lex.yy.cpp)" << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printUsage(argv[0]);
        return 1;
    }
    
    std::string inputFile = argv[1];
    std::string outputFile = (argc > 2) ? argv[2] : "lex.yy.cpp";
    
    std::cout << "========================================" << std::endl;
    std::cout << "SeuLex - Lexical Analyzer Generator" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "Input file: " << inputFile << std::endl;
    std::cout << "Output file: " << outputFile << std::endl;
    std::cout << std::endl;
    
    clock_t start, end;
    
    // Step 1: 解析.l文件
    std::cout << "[Step 1] Parsing .l file..." << std::endl;
    start = clock();
    if (!parseLexFile(inputFile)) {
        std::cerr << "Error: Failed to parse input file" << std::endl;
        return 1;
    }
    end = clock();
    std::cout << "  Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << std::endl;
    
    // Step 2: 正则表达式标准化
    std::cout << "[Step 2] Standardizing regular expressions..." << std::endl;
    start = clock();
    standardizeRegex();
    end = clock();
    std::cout << "  Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << std::endl;
    
    // Step 3: 转换为后缀表达式
    std::cout << "[Step 3] Converting to suffix notation..." << std::endl;
    start = clock();
    convertToSuffix();
    end = clock();
    std::cout << "  Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << std::endl;
    
    // Step 4: 构建NFA
    std::cout << "[Step 4] Building NFA (Thompson construction)..." << std::endl;
    start = clock();
    NFA nfa = convertToNFA();
    end = clock();
    std::cout << "  Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << std::endl;
    
    // Step 5: NFA转DFA
    std::cout << "[Step 5] Converting NFA to DFA (subset construction)..." << std::endl;
    start = clock();
    DFA dfa = convertNFAtoDFA(nfa);
    end = clock();
    std::cout << "  Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << std::endl;
    
    // Step 6: DFA最小化
    std::cout << "[Step 6] Minimizing DFA..." << std::endl;
    DFA miniDFA = minimizeDFA(dfa);
    std::cout << "  Minimized DFA has " << miniDFA.states.size() << " states" << std::endl;
    std::cout << std::endl;
    
    // Step 7: 生成驱动表
    std::cout << "[Step 7] Generating driver table..." << std::endl;
    start = clock();
    DriverTable table = generateDriverTable(miniDFA);
    end = clock();
    std::cout << "  Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << std::endl;
    
    // Step 8: 生成代码
    std::cout << "[Step 8] Generating C++ code..." << std::endl;
    start = clock();
    generateCode(table, outputFile);
    end = clock();
    std::cout << "  Time: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << std::endl;
    std::cout << std::endl;
    
    std::cout << "========================================" << std::endl;
    std::cout << "Done! Lexer generated successfully." << std::endl;
    std::cout << "========================================" << std::endl;
    
    return 0;
}
