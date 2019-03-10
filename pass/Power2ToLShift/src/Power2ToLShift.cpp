#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/PatternMatch.h"

#include "Power2ToLShift.hpp"

using namespace llvm;
using namespace PatternMatch;

bool Power2ToLShift::runOnFunction(Function &F){
    bool result;
    result = multOfPower2ToLShift(F);
    return result;
}

bool Power2ToLShift::multOfPower2ToLShift(Function &F)
{
    for (auto &B : F)
    {
      for (auto &I : B)
      {
        if (auto *op = dyn_cast<BinaryOperator>(&I))
        {
          const APInt *power_of_2_value;
          Value *other_side;
          if (match(op, m_Mul(m_Power2(power_of_2_value), m_Value(other_side))) || match(op, m_Mul(m_Value(other_side), m_Power2(power_of_2_value))))
          {
            errs() << "At function " << F.getName() << ": mul operation by power of 2 was detected!\n";

            // Insert at the point where the instruction `op` appears.
            IRBuilder<> builder(op);
            // Calculate shift amount
            Constant *shiftAmount = ConstantInt::get(op->getType(), power_of_2_value->logBase2());
            // Create shift operation equivalents to original mult operation
            Value *sht = builder.CreateShl(other_side, shiftAmount);

            // Everywhere the old instruction was used as an operand, use our
            // new multiply instruction instead.
            for (auto &U : op->uses())
            {
              User *user = U.getUser(); // A User is anything with operands.
              user->setOperand(U.getOperandNo(), sht);
            }

            // We modified the code.
            return true;
          }
        }
      }
    }

    // Insist code was not modified.
    return false;
}


void Power2ToLShift::getAnalysisUsage(llvm::AnalysisUsage &AU) const{
	AU.setPreservesCFG();
}

char Power2ToLShift::ID=0;
static RegisterPass<Power2ToLShift> X("Power2ToLShift", "Power2ToLShift Test Pass featuring MURAAK",
                                false /* Only looks at CFG */,
                                true /* Transform Pass */);

