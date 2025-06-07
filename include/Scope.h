#ifndef COMPILER_SCOPE_H
#define COMPILER_SCOPE_H

#include <unordered_map>
#include "ValueRef.h"
#include "LLVM.h"

using namespace std;

class Scope{
public:
    int sid;
    Scope *super; // 上一级作用域
    unordered_map<string,Symbol*> vars; // 符号表,string(变量名) -> Symbol

    Symbol* getVar(const string& varName);

    Symbol* addVar(Builder* builder,Type* type,string& name,bool is_const,ValueRef *initVal); // if not inited, initVal == nullptr

    ValueRef* getFunc();

    void addFunc();

    Scope(Scope *super, int sid);
};

#endif


