#include <iostream>
#include <fstream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include "ast.h"

// 声明 Flex/Bison 函数
extern int yyparse();
extern FILE *yyin;

int main(int argc, char *argv[]) {
    // 初始化 LLVM
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();
    llvm::InitializeNativeTargetAsmParser();
    
    // 创建 LLVM 上下文
    llvm::LLVMContext context;
    
    // 创建模块
    std::unique_ptr<llvm::Module> module = std::make_unique<llvm::Module>("c99 compiler", context);
    
    // 创建 IR 构建器
    llvm::IRBuilder<> builder(context);
    
    // 打开输入文件
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            std::cerr << "Cannot open input file: " << argv[1] << std::endl;
            return 1;
        }
    }
    
    // 解析输入
    if (yyparse()) {
        std::cerr << "Parsing failed" << std::endl;
        return 1;
    }
    
    // 调试信息
    std::cout << "ast_root = " << ast_root << std::endl;
    if (ast_root) {
        std::cout << "ast_root type = " << ast_root->type << std::endl;
    }
    
    // 生成中间代码
    if (ast_root) {
        ast_root->codegen(builder, *module);
    }
    
    // 输出 LLVM IR
    module->print(llvm::errs(), nullptr);
    
    // 清理
    if (yyin) {
        fclose(yyin);
    }
    
    return 0;
}
