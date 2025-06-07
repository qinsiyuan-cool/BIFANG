#include <queue>
#include "Pass/IROptimizer.h"
#include "Pass/DomTreePass.h"
#include "Pass/LiveVariableAnalysis.h"
#include "Pass/Mem2RegPass.h"
#include "Pass/OptUtils.h"

IROptimizer::IROptimizer(GlobalUnit *gu) {
    this->globalUnit = gu;
}

void IROptimizer::Optimize() {
    // Dom Tree & DF

    BuildCFG();
    Constlize();

    //globalUnit->Emit(std::cerr);
    DomTreePass* domTreePass = new DomTreePass(this->globalUnit);
    domTreePass->run();

    //LVA
    LiveVariableAnalysis* lva = new LiveVariableAnalysis(this->globalUnit);
    lva->analysis();

    //Mem2reg
    Mem2RegPass* mem2reg = new Mem2RegPass(this->globalUnit);
    mem2reg->run();

}

void IROptimizer::BuildCFG() {
    // 1.bfs && remove unvisited blocks
    for(auto&[name,func]: globalUnit->func_table){
        if(func->entry == nullptr) continue;

        set<BasicBlock*> vis;
        queue<BasicBlock*> q;
        q.push(func->entry);
        while(!q.empty()){
            BasicBlock * block = q.front(); q.pop();
            if(vis.count(block)) continue;
            vis.insert(block);
            for(auto bb:block->succ){
                q.push(bb);
            }
        }

        auto& v = func->block_list;
        vector<BasicBlock *> not_visited;
        for(auto & it : v){
            if(!vis.count(it)){ // not visited
                not_visited.push_back(it);
            }
        }

        for(auto bb:not_visited){
            DelBlock(bb);
        }
    }
}

void IROptimizer::debug() {
    for(auto&[name,func]:globalUnit->func_table){
        for(auto block: func->block_list){
            for(auto instr: block->local_instr){
                if(!instr->def_list.empty()){
                    ValueRef * def = *(instr->def_list.begin());
                    cerr << def->name << " :" << endl;
                    for(auto use : def->use){
                        use->outPut(std::cerr);
                    }
                }
            }
        }
    }
}

void IROptimizer::Constlize() {
    for(auto &[name,symbol]: globalUnit->global_symbol_table){
        if(symbol->symbolType->type != ARRAYTYPE && symbol->def.empty()){
            for(auto load: symbol->use){
                ValueRef* val = *(load->def_list.begin());
                replaceAllUsesOf(val,symbol->constVal);
            }
        }
    }
}
