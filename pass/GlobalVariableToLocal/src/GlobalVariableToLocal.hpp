#ifndef __GlobalVariableToLocal_H__
#define __GlobalVariableToLocal_H__

#include<llvm/IR/Module.h>
#include<llvm/Pass.h>

using namespace llvm;

class GlobalVariableToLocal : public ModulePass{
    public:
        static char ID;
        GlobalVariableToLocal() : ModulePass(ID){}
        ~GlobalVariableToLocal(){}

        virtual bool runOnModule(Module &M);
		//virtual bool runOnFunction(Function &F);
		virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const;
};

#endif
