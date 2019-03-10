#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Transforms/Utils/BasicBlockUtils.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/PatternMatch.h"

#include "GlobalVariableToLocal.hpp"

using namespace llvm;
using namespace std;
using namespace PatternMatch;

bool GlobalVariableToLocal::runOnModule(Module &M)
{
/*
なんかすごくダサいが、とりあえず強引に作ってみた。。。
グローバル変数のユーザーをなめた方がスマートだが、今回はmain関数内にインライン展開された
グローバル変数へのアクセスのみローカル変数に変えたかったので、ユーザーをなめると
ループ内で結局所属関数を判断しないといけないし、ライブラリの関数(main以外の関数)が
多いとmain内だけ探索した方がよい気がした。
しかし、getOperandだと左辺値の扱いがよくわからず、なんかまずいケースもありそうな・・・
一応サンプルコードではグローバル変数アクセスが消えていたけど。
特定ジュール内の特定グローバル変数のみをローカル変数化するのはどうするといいかなー？
ちょっと疲れたので一旦これでアップして休憩。。(*´Д｀)
*/

	bool bResult = false;
	vector<string> Gbl2LclValList = { "HSTK" };
	vector<string> Gbl2LclFuncList = { "main" };

	LLVMContext Context;
	llvm::IRBuilder<> Builder(Context);

	for (auto Gbl2LclFunc : Gbl2LclFuncList) {
		auto F = M.getFunction(Gbl2LclFunc);
		if (!F) continue;

		for (auto Gbl2LclVal : Gbl2LclValList) {
			auto GV = M.getGlobalVariable(Gbl2LclVal);
			if (!GV) continue;

			Builder.SetInsertPoint(&F->getBasicBlockList().front().getInstList().front());
			auto LclVal = Builder.CreateAlloca(GV->getValueType(), nullptr, Gbl2LclVal + "_L");

			for (auto &B : *F)
			{
				for (auto &I : B)
				{
					printf("--------\n");

					I.dump();
					for (auto l = 0; l < I.getNumOperands(); l++) {
						printf("----\n");
						I.getOperand(l)->dump();
						if (I.getOperand(l)->getValueID() == GV->getValueID()) {
							printf("Detect!\n");
							F->dump();
							I.getOperandUse(l).set(LclVal);
							F->dump();
						}
					}
				}
			}
		}
	}


// 以下テストコード
#if 0
	for (auto &G : M.getGlobalList()) {
		G.dump();
		bool can_localize = true;
		Function *F_refs_G = NULL;

		printf("[Global Vriable Name: %s]\n", G.getName());


		for (auto U : G.users()) {
			if (auto I = dyn_cast<Instruction>(U)) {

				if (Function *F = I->getFunction()) {

//					if (IsInlineFunction(F) == false) {
						if (F_refs_G == NULL) {
							F_refs_G = F;
						}
						else {
							if (F->getGUID() != F_refs_G->getGUID()) {
								can_localize = false;
								errs() << "break!\n";
								break;
							}
						}
					}
//				}
			}
		}




	}

/*
	for (auto &F : M)
	{
		for (auto &B : F)
		{
			for (auto &I : B)
			{
				I.dump();
				if (auto *si = dyn_cast<StoreInst>(&I))
				{
					si->dump();
					si->getOperand(1)->dump();
					auto *gv = dyn_cast<GlobalVariable>(si->getOperand(1));
					if (gv)
					{
						gv->dump();
	
					}
					//return true;
				}
			}
		}
	}
*/
#endif

	return false;
}


void GlobalVariableToLocal::getAnalysisUsage(llvm::AnalysisUsage &AU) const{
	AU.setPreservesCFG();
}

char GlobalVariableToLocal::ID=0;
static RegisterPass<GlobalVariableToLocal> X("GlobalVariableToLocal", "GlobalVariableToLocal Test Pass",
                                false /* Only looks at CFG */,
                                true /* Transform Pass */);

