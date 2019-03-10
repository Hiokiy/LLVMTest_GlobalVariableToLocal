#ifndef __Power2ToLShift_H__
#define __Power2ToLShift_H__

#include<llvm/IR/Function.h>
#include<llvm/Pass.h>

using namespace llvm;

class Power2ToLShift : public FunctionPass{
    public:
        static char ID;
        Power2ToLShift() : FunctionPass(ID){}
        ~Power2ToLShift(){}

        virtual bool runOnFunction(Function &F);
        virtual void getAnalysisUsage(llvm::AnalysisUsage &AU) const;

	bool multOfPower2ToLShift(Function &F);
};

#endif
