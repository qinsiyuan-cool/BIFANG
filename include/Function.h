
#include "BasicBlock.h"
#include "Type.h"
#include "ValueRef.h"
//#include "Pass/DomNode.h"

#ifndef COMPILER_FUNCTION_H
#define COMPILER_FUNCTION_H

class AsmBuilder;

class Function {
public:
    FuncType * funcType;
    string name;
    //define i32 @func(i32 %1,%float %2){
    string debugInfo;
    BasicBlock * entry; // this block is the entry of func,and it only has alloc instr;(before mem2reg)
    DomNode * dom_root;

    map<std::string,Symbol*> symbol_table;
    std::vector<BasicBlock *> block_list; // 默认0号基本块为入口

    std::vector<Loop*> loops;

    std::set<Function*> caller;//这个函数的调用者
    std::set<Function*> callee;//这个函数调用的

    bool has_side_effect;


    Function(string name,FuncType *funcType);

    void appendBlock(BasicBlock * block);

    void addSymbol(string& symbolName,Symbol* symbol){
        symbol_table[symbolName] = symbol;
    }

    void Emit(std::ostream &os);

    void PrintSymbol();

    void codegen(AsmBuilder *builder);
    //逆后序遍历（深搜逆序）
    std::vector<BasicBlock*> getReversePostOrder();
};


#endif
