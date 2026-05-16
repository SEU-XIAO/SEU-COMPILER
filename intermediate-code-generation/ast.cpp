#include "ast.h"
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Type.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <map>
#include <string>

// 全局符号表，用于存储变量和函数
std::map<std::string, llvm::Value*> symbolTable;

// 全局根节点
ASTNode *ast_root = nullptr;

// AST 构建函数实现
ASTNode *ast_var(const char *name) {
    return new VarNode(name);
}

ASTNode *ast_int(int val) {
    return new IntNode(val);
}

ASTNode *ast_double(double val) {
    return new DoubleNode(val);
}

ASTNode *ast_binop(char op, ASTNode *left, ASTNode *right) {
    return new BinopNode(op, left, right);
}

ASTNode *ast_call(const char *name, ASTNode **args, int argc) {
    return new CallNode(name, args, argc);
}

ASTNode *ast_unop(char op, ASTNode *expr) {
    return new UnopNode(op, expr);
}

ASTNode *ast_pointer(ASTNode *expr) {
    return new PointerNode(expr);
}

ASTNode *ast_assign(ASTNode *lhs, ASTNode *rhs) {
    return new AssignNode(lhs, rhs);
}

ASTNode *ast_compound(ASTNode **list, int count) {
    return new CompoundNode(list, count);
}

ASTNode *ast_decl(ASTNode **specs, int scount, ASTNode **inits, int icount) {
    return new DeclNode(specs, scount, inits, icount);
}

ASTNode *ast_decl_spec(ASTNode **specs, int scount) {
    return new DeclSpecNode(specs, scount);
}

ASTNode *ast_init_decl(ASTNode *decl, ASTNode *init) {
    return new InitDeclNode(decl, init);
}

ASTNode *ast_type_name(const char *name) {
    return new TypeNameNode(name);
}

ASTNode *ast_array(ASTNode *base, ASTNode *size) {
    return new ArrayNode(base, size);
}

ASTNode *ast_func_type(const char *name, ASTNode *params, ASTNode *ret_type, ASTNode *body) {
    return new FuncTypeNode(name, params, ret_type, body);
}

ASTNode *ast_param_list(ASTNode **params, int count) {
    return new ParamListNode(params, count);
}

ASTNode *ast_param(ASTNode **specs, int scount, ASTNode *decl) {
    return new ParamNode(specs, scount, decl);
}

ASTNode *ast_init_list(ASTNode **inits, int count) {
    return new InitListNode(inits, count);
}

ASTNode *ast_expr_stmt(ASTNode *expr) {
    return new ExprStmtNode(expr);
}

ASTNode *ast_if(ASTNode *cond, ASTNode *then_branch, ASTNode *else_branch) {
    return new IfNode(cond, then_branch, else_branch);
}

ASTNode *ast_while(ASTNode *cond, ASTNode *body) {
    return new WhileNode(cond, body);
}

ASTNode *ast_do_while(ASTNode *body, ASTNode *cond) {
    return new DoWhileNode(body, cond);
}

ASTNode *ast_for(ASTNode *init, ASTNode *cond, ASTNode *inc, ASTNode *body) {
    return new ForNode(init, cond, inc, body);
}

ASTNode *ast_continue() {
    return new ContinueNode();
}

ASTNode *ast_break() {
    return new BreakNode();
}

ASTNode *ast_return(ASTNode *expr) {
    return new ReturnNode(expr);
}

ASTNode *ast_ext_decl(ASTNode *decl) {
    return new ExtDeclNode(decl);
}

ASTNode *ast_trans_unit(ASTNode **decls, int count) {
    return new TransUnitNode(decls, count);
}

// codegen 方法实现
llvm::Value* VarNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 查找变量
    auto it = symbolTable.find(varname);
    if (it != symbolTable.end()) {
        // 加载变量的值
        // 在 LLVM 18 中，CreateLoad 需要类型参数
        llvm::Type *varType = llvm::Type::getInt32Ty(builder.getContext());
        return builder.CreateLoad(varType, it->second, varname + ".val");
    }
    // 变量未找到，报错
    fprintf(stderr, "Variable %s not found\n", varname.c_str());
    return nullptr;
}

llvm::Value* IntNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    return llvm::ConstantInt::get(builder.getContext(), llvm::APInt(32, value));
}

llvm::Value* DoubleNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    return llvm::ConstantFP::get(builder.getContext(), llvm::APFloat(value));
}

llvm::Value* BinopNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    llvm::Value *left = binop.left->codegen(builder, module);
    llvm::Value *right = binop.right->codegen(builder, module);
    
    if (!left || !right) return nullptr;
    
    switch (binop.op) {
        case '+':
            return builder.CreateAdd(left, right, "addtmp");
        case '-':
            return builder.CreateSub(left, right, "subtmp");
        case '*':
            return builder.CreateMul(left, right, "multmp");
        case '/':
            return builder.CreateSDiv(left, right, "divtmp");
        case '%':
            return builder.CreateSRem(left, right, "remtmp");
        case '<':
            return builder.CreateICmpSLT(left, right, "cmptmp");
        case '>':
            return builder.CreateICmpSGT(left, right, "cmptmp");
        case 'l': // <=
            return builder.CreateICmpSLE(left, right, "cmptmp");
        case 'g': // >=
            return builder.CreateICmpSGE(left, right, "cmptmp");
        case 'e': // ==
            return builder.CreateICmpEQ(left, right, "cmptmp");
        case '!': // !=
            return builder.CreateICmpNE(left, right, "cmptmp");
        case '&':
            return builder.CreateAnd(left, right, "andtmp");
        case '|':
            return builder.CreateOr(left, right, "ortmp");
        case '^':
            return builder.CreateXor(left, right, "xortmp");
        case '[': // 数组访问
            // 简化处理，实际需要更复杂的数组访问处理
            return right;
        case '.': // 结构体访问
            // 简化处理，实际需要更复杂的类型处理
            return right;
        default:
            fprintf(stderr, "Unknown binary operator: %c\n", binop.op);
            return nullptr;
    }
}

llvm::Value* CallNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 查找函数
    llvm::Function *func = builder.GetInsertBlock()->getParent()->getParent()->getFunction(varname);
    if (!func) {
        fprintf(stderr, "Function %s not found\n", varname.c_str());
        return nullptr;
    }
    
    // 准备参数
    std::vector<llvm::Value*> args;
    for (int i = 0; i < call.argc; i++) {
        llvm::Value *arg = call.args[i]->codegen(builder, module);
        if (!arg) return nullptr;
        args.push_back(arg);
    }
    
    return builder.CreateCall(llvm::FunctionCallee(func), args, "calltmp");
}

llvm::Value* UnopNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    llvm::Value *expr = unop.expr->codegen(builder, module);
    if (!expr) return nullptr;
    
    switch (unop.op) {
        case '+': // 正号
            return expr;
        case '-': // 负号
            return builder.CreateNeg(expr, "negtmp");
        case '!': // 逻辑非
            return builder.CreateNot(expr, "nottmp");
        case '~': // 按位非
            return builder.CreateNot(expr, "bittmp");
        case '&': // 取地址
            // 简化处理，实际需要更复杂的内存管理
            return expr;
        default:
            fprintf(stderr, "Unknown unary operator: %c\n", unop.op);
            return nullptr;
    }
}

llvm::Value* PointerNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，实际需要更复杂的指针类型处理
    if (unop.expr) {
        return unop.expr->codegen(builder, module);
    }
    return nullptr;
}

llvm::Value* AssignNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    llvm::Value *lhs = assign.lhs->codegen(builder, module);
    llvm::Value *rhs = assign.rhs->codegen(builder, module);
    
    if (!lhs || !rhs) return nullptr;
    
    return builder.CreateStore(rhs, lhs, "assign tmp");
}

llvm::Value* CompoundNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    llvm::Value *last = nullptr;
    for (int i = 0; i < seq.count; i++) {
        last = seq.list[i]->codegen(builder, module);
    }
    return last;
}

llvm::Value* DeclNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，假设声明的是 int 类型的变量
    llvm::Type *varType = llvm::Type::getInt32Ty(builder.getContext());

    // 检查是否在函数内部（全局作用域不能用 alloca）
    bool isGlobalScope = !builder.GetInsertBlock();

    for (int i = 0; i < seq.count; i++) {
        // 获取初始化声明节点
        InitDeclNode *initDecl = static_cast<InitDeclNode*>(seq.list[i]);
        if (!initDecl) continue;

        // 获取变量名
        VarNode *varNode = static_cast<VarNode*>(initDecl->init_decl.decl);
        if (!varNode) continue;
        std::string varName = varNode->varname;

        if (isGlobalScope) {
            // 全局变量：创建全局变量定义
            llvm::GlobalVariable *gv = new llvm::GlobalVariable(
                module, varType, false,
                llvm::GlobalValue::ExternalLinkage,
                llvm::ConstantInt::get(varType, 0),
                varName);
            symbolTable[varName] = gv;
        } else {
            // 局部变量：使用 alloca
            llvm::Value *alloca = builder.CreateAlloca(varType, nullptr, varName);
            symbolTable[varName] = alloca;

            // 生成初始化代码
            if (initDecl->init_decl.init) {
                llvm::Value *initValue = initDecl->init_decl.init->codegen(builder, module);
                if (initValue) {
                    builder.CreateStore(initValue, alloca);
                }
            }
        }
    }
    return nullptr;
}

llvm::Value* DeclSpecNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，实际需要更复杂的类型处理
    return nullptr;
}

llvm::Value* InitDeclNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，实际需要更复杂的初始化处理
    if (init_decl.init) {
        init_decl.init->codegen(builder, module);
    }
    return init_decl.decl->codegen(builder, module);
}

llvm::Value* TypeNameNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 类型名称节点不需要生成代码
    return nullptr;
}

llvm::Value* ArrayNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，实际需要更复杂的数组类型处理
    if (array.base) {
        return array.base->codegen(builder, module);
    }
    return nullptr;
}

llvm::Value* FuncTypeNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，假设返回类型为 int
    llvm::Type *returnType = llvm::Type::getInt32Ty(builder.getContext());

    // 收集参数类型和名称
    std::vector<llvm::Type*> paramTypes;
    std::vector<std::string> paramNames;
    if (ft.params && ft.params->type == AST_PARAM_LIST) {
        ParamListNode *plist = static_cast<ParamListNode*>(ft.params);
        for (int i = 0; i < plist->seq.count; i++) {
            paramTypes.push_back(llvm::Type::getInt32Ty(builder.getContext()));
            ParamNode *p = static_cast<ParamNode*>(plist->seq.list[i]);
            if (p && p->param.decl && p->param.decl->type == AST_VAR) {
                paramNames.push_back(static_cast<VarNode*>(p->param.decl)->varname);
            } else {
                paramNames.push_back("");
            }
        }
    }

    llvm::FunctionType *funcType = llvm::FunctionType::get(returnType, paramTypes, false);

    // 创建函数
    llvm::Function *func = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, varname, module);

    // 为参数命名并创建 alloca
    llvm::BasicBlock *entryBB = llvm::BasicBlock::Create(builder.getContext(), "entry", func);
    builder.SetInsertPoint(entryBB);

    unsigned idx = 0;
    for (auto &arg : func->args()) {
        if (idx < paramNames.size()) {
            arg.setName(paramNames[idx]);
            // 为参数创建 alloca 并存储
            llvm::AllocaInst *alloca = builder.CreateAlloca(llvm::Type::getInt32Ty(builder.getContext()), nullptr, paramNames[idx]);
            builder.CreateStore(&arg, alloca);
            symbolTable[paramNames[idx]] = alloca;
        }
        idx++;
    }

    // 生成函数体代码
    if (ft.body) {
        ft.body->codegen(builder, module);
    }

    // 如果没有显式的 return 语句，添加一个默认的 return 0
    if (!builder.GetInsertBlock()->getTerminator()) {
        builder.CreateRet(llvm::ConstantInt::get(returnType, 0));
    }

    return func;
}

llvm::Value* ParamListNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 参数列表节点不需要生成代码
    return nullptr;
}

llvm::Value* ParamNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 参数节点不需要生成代码
    return nullptr;
}

llvm::Value* InitListNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，实际需要更复杂的初始化列表处理
    for (int i = 0; i < seq.count; i++) {
        seq.list[i]->codegen(builder, module);
    }
    return nullptr;
}

llvm::Value* ExprStmtNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    if (expr) {
        return expr->codegen(builder, module);
    }
    return nullptr;
}

llvm::Value* IfNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    llvm::Value *cond = if_stmt.cond->codegen(builder, module);
    if (!cond) return nullptr;
    
    llvm::Function *func = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *thenBB = llvm::BasicBlock::Create(builder.getContext(), "then", func);
    llvm::BasicBlock *elseBB = llvm::BasicBlock::Create(builder.getContext(), "else");
    llvm::BasicBlock *mergeBB = llvm::BasicBlock::Create(builder.getContext(), "ifcont");
    
    builder.CreateCondBr(cond, thenBB, elseBB);
    
    // 生成 then 分支
    builder.SetInsertPoint(thenBB);
    if_stmt.then_branch->codegen(builder, module);
    builder.CreateBr(mergeBB);
    
    // 生成 else 分支
    elseBB->insertInto(func);
    builder.SetInsertPoint(elseBB);
    if (if_stmt.else_branch) {
        if_stmt.else_branch->codegen(builder, module);
    }
    builder.CreateBr(mergeBB);
    
    // 合并块
    mergeBB->insertInto(func);
    builder.SetInsertPoint(mergeBB);
    
    return nullptr;
}

llvm::Value* WhileNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    llvm::Function *func = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(builder.getContext(), "loop", func);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(builder.getContext(), "afterloop");
    
    builder.CreateBr(loopBB);
    builder.SetInsertPoint(loopBB);
    
    llvm::Value *cond = while_stmt.cond->codegen(builder, module);
    if (!cond) return nullptr;
    
    builder.CreateCondBr(cond, loopBB, afterBB);
    
    // 生成循环体
    while_stmt.body->codegen(builder, module);
    builder.CreateBr(loopBB);
    
    // 循环结束后的块
    afterBB->insertInto(func);
    builder.SetInsertPoint(afterBB);
    
    return nullptr;
}

llvm::Value* DoWhileNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    llvm::Function *func = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(builder.getContext(), "loop", func);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(builder.getContext(), "afterloop");
    
    builder.CreateBr(loopBB);
    builder.SetInsertPoint(loopBB);
    
    // 生成循环体
    do_while_stmt.body->codegen(builder, module);
    
    // 生成条件判断
    llvm::Value *cond = do_while_stmt.cond->codegen(builder, module);
    if (!cond) return nullptr;
    
    builder.CreateCondBr(cond, loopBB, afterBB);
    
    // 循环结束后的块
    afterBB->insertInto(func);
    builder.SetInsertPoint(afterBB);
    
    return nullptr;
}

llvm::Value* ForNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，将 for 循环转换为 while 循环
    if (for_stmt.init) {
        for_stmt.init->codegen(builder, module);
    }
    
    llvm::Function *func = builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *loopBB = llvm::BasicBlock::Create(builder.getContext(), "loop", func);
    llvm::BasicBlock *afterBB = llvm::BasicBlock::Create(builder.getContext(), "afterloop");
    
    builder.CreateBr(loopBB);
    builder.SetInsertPoint(loopBB);
    
    if (for_stmt.cond) {
        llvm::Value *cond = for_stmt.cond->codegen(builder, module);
        if (!cond) return nullptr;
        builder.CreateCondBr(cond, loopBB, afterBB);
    }
    
    // 生成循环体
    for_stmt.body->codegen(builder, module);
    
    // 生成递增表达式
    if (for_stmt.inc) {
        for_stmt.inc->codegen(builder, module);
    }
    
    builder.CreateBr(loopBB);
    
    // 循环结束后的块
    afterBB->insertInto(func);
    builder.SetInsertPoint(afterBB);
    
    return nullptr;
}

llvm::Value* ContinueNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，实际需要找到循环的回边
    return nullptr;
}

llvm::Value* BreakNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    // 简化处理，实际需要找到循环的出口
    return nullptr;
}

llvm::Value* ReturnNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    if (expr) {
        llvm::Value *val = expr->codegen(builder, module);
        if (!val) return nullptr;
        return builder.CreateRet(val);
    } else {
        return builder.CreateRetVoid();
    }
}

llvm::Value* ExtDeclNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    return decl->codegen(builder, module);
}

llvm::Value* TransUnitNode::codegen(llvm::IRBuilder<> &builder, llvm::Module &module) {
    for (int i = 0; i < seq.count; i++) {
        seq.list[i]->codegen(builder, module);
    }
    return nullptr;
}
