#ifndef AST_H
#define AST_H

#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <vector>
#include <string>

// 前向声明
class ASTNode;

// AST 节点类型枚举
enum ASTType {
    AST_VAR,
    AST_INT,
    AST_DOUBLE,
    AST_BINOP,
    AST_CALL,
    AST_UNOP,
    AST_POINTER,
    AST_ASSIGN,
    AST_COMPOUND,
    AST_DECL,
    AST_DECL_SPEC,
    AST_INIT_DECL,
    AST_TYPE_NAME,
    AST_ARRAY,
    AST_FUNC_TYPE,
    AST_PARAM_LIST,
    AST_PARAM,
    AST_INIT_LIST,
    AST_EXPR_STMT,
    AST_IF,
    AST_WHILE,
    AST_DO_WHILE,
    AST_FOR,
    AST_CONTINUE,
    AST_BREAK,
    AST_RETURN,
    AST_EXT_DECL,
    AST_TRANS_UNIT
};

// AST 基类
class ASTNode {
public:
    ASTType type;
    std::string varname; // 用于变量和函数名
    
    // 声明说明符相关
    struct {
        ASTNode **specs;
        int scount;
    } ds;
    
    // 函数类型相关
    struct {
        ASTNode *ret_type;
        ASTNode *params;
        ASTNode *body;
        ASTNode *next;
    } ft;
    
    // 序列相关
    struct {
        ASTNode **list;
        int count;
    } seq;
    
    // 二元操作相关
    struct {
        char op;
        ASTNode *left;
        ASTNode *right;
    } binop;
    
    // 一元操作相关
    struct {
        char op;
        ASTNode *expr;
    } unop;
    
    // 赋值相关
    struct {
        ASTNode *lhs;
        ASTNode *rhs;
    } assign;
    
    // if 语句相关
    struct {
        ASTNode *cond;
        ASTNode *then_branch;
        ASTNode *else_branch;
    } if_stmt;
    
    // while 语句相关
    struct {
        ASTNode *cond;
        ASTNode *body;
    } while_stmt;
    
    // do-while 语句相关
    struct {
        ASTNode *body;
        ASTNode *cond;
    } do_while_stmt;
    
    // for 语句相关
    struct {
        ASTNode *init;
        ASTNode *cond;
        ASTNode *inc;
        ASTNode *body;
    } for_stmt;
    
    // 数组相关
    struct {
        ASTNode *base;
        ASTNode *size;
    } array;
    
    // 函数调用相关
    struct {
        ASTNode **args;
        int argc;
    } call;
    
    // 参数相关
    struct {
        ASTNode **specs;
        int scount;
        ASTNode *decl;
    } param;
    
    // 初始化声明相关
    struct {
        ASTNode *decl;
        ASTNode *init;
    } init_decl;
    
    // 构造函数
    ASTNode(ASTType t) : type(t) {}
    
    // 虚析构函数
    virtual ~ASTNode() {}
    
    // 代码生成方法
    virtual llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) = 0;
};

// 变量节点
class VarNode : public ASTNode {
public:
    VarNode(const std::string &name) : ASTNode(AST_VAR) {
        varname = name;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 整数常量节点
class IntNode : public ASTNode {
public:
    int value;
    
    IntNode(int val) : ASTNode(AST_INT), value(val) {}
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 双精度浮点常量节点
class DoubleNode : public ASTNode {
public:
    double value;
    
    DoubleNode(double val) : ASTNode(AST_DOUBLE), value(val) {}
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 二元操作节点
class BinopNode : public ASTNode {
public:
    BinopNode(char op, ASTNode *left, ASTNode *right) : ASTNode(AST_BINOP) {
        binop.op = op;
        binop.left = left;
        binop.right = right;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 函数调用节点
class CallNode : public ASTNode {
public:
    CallNode(const std::string &name, ASTNode **args, int argc) : ASTNode(AST_CALL) {
        varname = name;
        call.args = args;
        call.argc = argc;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 一元操作节点
class UnopNode : public ASTNode {
public:
    UnopNode(char op, ASTNode *expr) : ASTNode(AST_UNOP) {
        unop.op = op;
        unop.expr = expr;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 指针节点
class PointerNode : public ASTNode {
public:
    PointerNode(ASTNode *expr) : ASTNode(AST_POINTER) {
        unop.expr = expr;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 赋值节点
class AssignNode : public ASTNode {
public:
    AssignNode(ASTNode *lhs, ASTNode *rhs) : ASTNode(AST_ASSIGN) {
        assign.lhs = lhs;
        assign.rhs = rhs;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 复合语句节点
class CompoundNode : public ASTNode {
public:
    CompoundNode(ASTNode **list, int count) : ASTNode(AST_COMPOUND) {
        seq.list = list;
        seq.count = count;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 声明节点
class DeclNode : public ASTNode {
public:
    DeclNode(ASTNode **specs, int scount, ASTNode **inits, int icount) : ASTNode(AST_DECL) {
        ds.specs = specs;
        ds.scount = scount;
        seq.list = inits;
        seq.count = icount;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 声明说明符节点
class DeclSpecNode : public ASTNode {
public:
    DeclSpecNode(ASTNode **specs, int scount) : ASTNode(AST_DECL_SPEC) {
        ds.specs = specs;
        ds.scount = scount;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 初始化声明节点
class InitDeclNode : public ASTNode {
public:
    InitDeclNode(ASTNode *decl, ASTNode *init) : ASTNode(AST_INIT_DECL) {
        init_decl.decl = decl;
        init_decl.init = init;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 类型名称节点
class TypeNameNode : public ASTNode {
public:
    TypeNameNode(const std::string &name) : ASTNode(AST_TYPE_NAME) {
        varname = name;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 数组节点
class ArrayNode : public ASTNode {
public:
    ArrayNode(ASTNode *base, ASTNode *size) : ASTNode(AST_ARRAY) {
        array.base = base;
        array.size = size;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 函数类型节点
class FuncTypeNode : public ASTNode {
public:
    FuncTypeNode(const std::string &name, ASTNode *params, ASTNode *ret_type, ASTNode *body) : ASTNode(AST_FUNC_TYPE) {
        varname = name;
        ft.params = params;
        ft.ret_type = ret_type;
        ft.body = body;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 参数列表节点
class ParamListNode : public ASTNode {
public:
    ParamListNode(ASTNode **params, int count) : ASTNode(AST_PARAM_LIST) {
        seq.list = params;
        seq.count = count;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 参数节点
class ParamNode : public ASTNode {
public:
    ParamNode(ASTNode **specs, int scount, ASTNode *decl) : ASTNode(AST_PARAM) {
        param.specs = specs;
        param.scount = scount;
        param.decl = decl;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 初始化列表节点
class InitListNode : public ASTNode {
public:
    InitListNode(ASTNode **inits, int count) : ASTNode(AST_INIT_LIST) {
        seq.list = inits;
        seq.count = count;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 表达式语句节点
class ExprStmtNode : public ASTNode {
public:
    ASTNode *expr;
    
    ExprStmtNode(ASTNode *e) : ASTNode(AST_EXPR_STMT), expr(e) {}
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// if 语句节点
class IfNode : public ASTNode {
public:
    IfNode(ASTNode *cond, ASTNode *then_branch, ASTNode *else_branch) : ASTNode(AST_IF) {
        if_stmt.cond = cond;
        if_stmt.then_branch = then_branch;
        if_stmt.else_branch = else_branch;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// while 语句节点
class WhileNode : public ASTNode {
public:
    WhileNode(ASTNode *cond, ASTNode *body) : ASTNode(AST_WHILE) {
        while_stmt.cond = cond;
        while_stmt.body = body;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// do-while 语句节点
class DoWhileNode : public ASTNode {
public:
    DoWhileNode(ASTNode *body, ASTNode *cond) : ASTNode(AST_DO_WHILE) {
        do_while_stmt.body = body;
        do_while_stmt.cond = cond;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// for 语句节点
class ForNode : public ASTNode {
public:
    ForNode(ASTNode *init, ASTNode *cond, ASTNode *inc, ASTNode *body) : ASTNode(AST_FOR) {
        for_stmt.init = init;
        for_stmt.cond = cond;
        for_stmt.inc = inc;
        for_stmt.body = body;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// continue 语句节点
class ContinueNode : public ASTNode {
public:
    ContinueNode() : ASTNode(AST_CONTINUE) {}
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// break 语句节点
class BreakNode : public ASTNode {
public:
    BreakNode() : ASTNode(AST_BREAK) {}
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// return 语句节点
class ReturnNode : public ASTNode {
public:
    ASTNode *expr;
    
    ReturnNode(ASTNode *e) : ASTNode(AST_RETURN), expr(e) {}
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 外部声明节点
class ExtDeclNode : public ASTNode {
public:
    ASTNode *decl;
    
    ExtDeclNode(ASTNode *d) : ASTNode(AST_EXT_DECL), decl(d) {}
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// 翻译单元节点
class TransUnitNode : public ASTNode {
public:
    TransUnitNode(ASTNode **decls, int count) : ASTNode(AST_TRANS_UNIT) {
        seq.list = decls;
        seq.count = count;
    }
    
    llvm::Value* codegen(llvm::IRBuilder<> &builder, llvm::Module &module) override;
};

// AST 构建函数声明
ASTNode *ast_var(const char *name);
ASTNode *ast_int(int val);
ASTNode *ast_double(double val);
ASTNode *ast_binop(char op, ASTNode *left, ASTNode *right);
ASTNode *ast_call(const char *name, ASTNode **args, int argc);
ASTNode *ast_unop(char op, ASTNode *expr);
ASTNode *ast_pointer(ASTNode *expr);
ASTNode *ast_assign(ASTNode *lhs, ASTNode *rhs);
ASTNode *ast_compound(ASTNode **list, int count);
ASTNode *ast_decl(ASTNode **specs, int scount, ASTNode **inits, int icount);
ASTNode *ast_decl_spec(ASTNode **specs, int scount);
ASTNode *ast_init_decl(ASTNode *decl, ASTNode *init);
ASTNode *ast_type_name(const char *name);
ASTNode *ast_array(ASTNode *base, ASTNode *size);
ASTNode *ast_func_type(const char *name, ASTNode *params, ASTNode *ret_type, ASTNode *body);
ASTNode *ast_param_list(ASTNode **params, int count);
ASTNode *ast_param(ASTNode **specs, int scount, ASTNode *decl);
ASTNode *ast_init_list(ASTNode **inits, int count);
ASTNode *ast_expr_stmt(ASTNode *expr);
ASTNode *ast_if(ASTNode *cond, ASTNode *then_branch, ASTNode *else_branch);
ASTNode *ast_while(ASTNode *cond, ASTNode *body);
ASTNode *ast_do_while(ASTNode *body, ASTNode *cond);
ASTNode *ast_for(ASTNode *init, ASTNode *cond, ASTNode *inc, ASTNode *body);
ASTNode *ast_continue();
ASTNode *ast_break();
ASTNode *ast_return(ASTNode *expr);
ASTNode *ast_ext_decl(ASTNode *decl);
ASTNode *ast_trans_unit(ASTNode **decls, int count);

// 全局根节点
extern ASTNode *ast_root;

#endif // AST_H
