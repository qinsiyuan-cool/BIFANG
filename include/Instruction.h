#include "ValueRef.h"
#ifndef COMPILER_INSTRUCTION_H
#define COMPILER_INSTRUCTION_H

#include "Backend/AsmBuilder.hpp"
#include <map>
#include <string>
enum InstType_Enum{DUMMY,AddGlb,ALLOCA, LOAD, STORE, BINARY, CMP, BR, CONDBR, RET, CALL, ZEXT, XOR, GEP, PHI, ITFP, FPTI, FNEG, MEMSET, MOVE, SLL, SRA};

class Instruction {
public:
    virtual void outPut(std::ostream &os) = 0;
    virtual void replace(ValueRef *old, ValueRef *now) = 0;

    virtual void codegen(AsmBuilder *pBuilder,
                 std::map<std::string, int> &offset_table,
                 std::map<std::string, int> &size_table,
                 int frameSize) = 0;
    InstType_Enum instType;
    bool deleted = false;

    void addDef(ValueRef* ref) {
        this->def_list.insert(ref);
        ref->def.push_back(this);
    }

    void addUse(ValueRef* ref) {
        this->use_list.insert(ref);
        ref->use.push_back(this);
    }

    //用于维护this使用了哪些Value
    std::set<ValueRef*> use_list;
    //用于维护this定义了哪些Value
    std::set<ValueRef*> def_list;

    Instruction(InstType_Enum instType){ this->instType = instType; }
};

#endif
