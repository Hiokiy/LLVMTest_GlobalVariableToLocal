#include <string>
#include <iostream>
#include <utility>
#include <memory>

#include "llvm/IR/Module.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Support/WithColor.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Linker/Linker.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Support/TargetSelect.h"

#include "pass/easypass/src/easypass.hpp"
#include "pass/Power2ToLShift/src/Power2ToLShift.hpp"
#include "pass/GlobalVariableToLocal/src/GlobalVariableToLocal.hpp"

using namespace llvm; 
using namespace std;

void dump2(Module &M);

//いろいろ参考にしたURL
//https://8128.jp/notebooks/llvm-c-api
//https://itchyny.hatenablog.com/entry/2017/03/06/100000
//https://gist.github.com/ysaito8015/d37a154bdd60852ce58f44f4a0949a03
//http://d.hatena.ne.jp/imasahiro/20111217/1324086354
//https://qiita.com/sakasin/items/097fa676ccfd117acaa2#fn1
//https://qiita.com/k2ymg/items/653c5b22b74a091be604

//https://qiita.com/long_long_float/items/50ba0d9dc4075f3934a1

typedef struct Inst{
	string	name;
	unsigned long aug1;
} Inst;

int main(int argc, char* argv[])
{
	LLVMContext Context;
	SMDiagnostic Err;

	if (argc < 2) {
		fprintf(stderr, "usage: %s <bitcode.file>\n", argv[0]);
		return 1;
	}

	// ■Load Guest Instructions
	printf("---[Guest Instructions List]---\n");
	vector<Inst> GuestInstList = {
		{"STMLD", 1},
		{"STOUT", 2},
		{"STMLD", 3},
		{"STOUT", 4}
	};
	for (auto it : GuestInstList) {	printf("%s %u\n", it.name.c_str(), it.aug1);	}
	printf("---[End]---\n\n");

	// ■Load Module Base
	printf("---[Library Instruction list]---\n");
	string FuncLibPath = argv[1];
	std::unique_ptr<Module> M = parseIRFile(FuncLibPath, Err, Context);
	if (!M) {
		Err.print(argv[0], errs());
		return 1;
	}
//	printf("File Name: %s\n", FuncLibPath.c_str());
//	printf("Module Name: %s\n", M_FuncLib->getName());
//	printf("Module Dump:\n");
//	M_FuncLib->dump();
	for (auto &F : *M) {
		printf("%s\n", F.getName());
		// ついでに属性変更しとく。
		F.removeFnAttr(Attribute::NoInline);
		F.removeFnAttr(Attribute::OptimizeNone);
		F.addFnAttr(Attribute::AlwaysInline);
	}
	printf("---[End]---\n\n");

	// ■Make Output Module & main Function
//	llvm::Module *M_Out = new llvm::Module("M_Out", Context);
	llvm::IRBuilder<> builder(Context);

	auto *funcType = llvm::FunctionType::get(builder.getVoidTy(), false);
	auto *mainFunc = llvm::Function::Create(funcType, llvm::Function::ExternalLinkage, "main", M.get());
	auto *entrypoint = llvm::BasicBlock::Create(Context, "entrypoint", mainFunc);
	builder.SetInsertPoint(entrypoint);

	// ■Add Callees
//	printf("--------\n\n");
//	M->dump();

	for (auto GuestInst : GuestInstList) {

		Function *func;
		func = M->getFunction(("Inst" + GuestInst.name).c_str());
		if (!func) {
			printf("Can't find function!:%s\n", GuestInst.name.c_str());
			return 1;
#if 0
			func = M_FuncLib->getFunction(GuestInst.c_str());
			if (!func) {
				printf("Can't find function!:%s\n", GuestInst.c_str());
				return 1;
			}

			ValueToValueMapTy VMap;
//			Function* func_clone = CloneFunction(func, VMap);
//			func_clone->removeFromParent();
//			func_clone->removeFnAttr(Attribute::NoInline);
//			func_clone->removeFnAttr(Attribute::OptimizeNone);
//			func_clone->addFnAttr(Attribute::AlwaysInline);
//			M_Out->getFunctionList().push_back(func_clone);
// Cloneをつくると関数名がsub1.1とかに変わってしまうので、ライブラリから移動してみたが、
// ライブラリからモジュールが消えるのもなんか変。。
// とここで、逆にライブラリにmain関数を追加した方がよい気がしてきたので、作り直し！！
			func->removeFromParent();
			func->removeFnAttr(Attribute::NoInline);
			func->removeFnAttr(Attribute::OptimizeNone);
			func->addFnAttr(Attribute::AlwaysInline);
			M_FuncLib->getFunctionList().push_back(func);
#endif
		}

//		builder.CreateCall(func_clone);
		builder.CreateCall(func, { builder.getInt32(GuestInst.aug1) });
	}

	builder.CreateRetVoid();

	// ■Optimization
	llvm::legacy::PassManager PM;

	printf("\n----[Before Optimization]----\n", argv[1]);
	M->dump();
//	dump2(*M);

//	PM.add(new EasyPass());
//	PM.add(new Power2ToLShift());
	PM.add(createIPSCCPPass());
	PM.add(createFunctionInliningPass());
	PM.add(createLICMPass());
	PM.add(createGVNPass());
	PM.add(createGlobalDCEPass());
	PM.add(createPromoteMemoryToRegisterPass());

	PM.add(new GlobalVariableToLocal());
	PM.add(createPromoteMemoryToRegisterPass());
	PM.add(createGlobalDCEPass());

	PM.run(*M);

	printf("\n----[After Optimization]----\n", argv[1]);
	M->dump();
//	dump2(*M);

#if 1
	//コンパイルに時間がかかるので無効かしておく。
	{
		// アセンブリ出力
		// 参考：https://itchyny.hatenablog.com/entry/2017/03/06/100000
		// 初期化はllcからパクリ。
		// Intel形式で出力したいが、後回し。

		// Initialize targets first, so that --version shows registered targets.
		InitializeAllTargets();
		InitializeAllTargetMCs();
		InitializeAllAsmPrinters();
		InitializeAllAsmParsers();

		// Initialize codegen and IR passes used by llc so that the -print-after,
		// -print-before, and -stop-after options work.
		PassRegistry *Registry = PassRegistry::getPassRegistry();
		initializeCore(*Registry);
		initializeCodeGen(*Registry);
		initializeLoopStrengthReducePass(*Registry);
		initializeLowerIntrinsicsPass(*Registry);
		initializeEntryExitInstrumenterPass(*Registry);
		initializePostInlineEntryExitInstrumenterPass(*Registry);
		initializeUnreachableBlockElimLegacyPassPass(*Registry);
		initializeConstantHoistingLegacyPassPass(*Registry);
		initializeScalarOpts(*Registry);
		initializeVectorization(*Registry);
		initializeScalarizeMaskedMemIntrinPass(*Registry);
		initializeExpandReductionsPass(*Registry);

		// Initialize debugging passes.
		initializeScavengerTestPass(*Registry);


		std::string TargetTriple = llvm::sys::getDefaultTargetTriple();
		std::string err;
		const llvm::Target* Target = llvm::TargetRegistry::lookupTarget(TargetTriple, err);

		
		if (!Target) {
			std::cerr << "Failed to lookup target " + TargetTriple + ": " + err;
			return 1;
		}
		llvm::TargetOptions opt;
		llvm::TargetMachine* TheTargetMachine = Target->createTargetMachine(TargetTriple, "generic", "", opt, llvm::Optional<llvm::Reloc::Model>());
		M->setTargetTriple(TargetTriple);
		M->setDataLayout(TheTargetMachine->createDataLayout());
		std::string Filename = "output.s";
		std::error_code err_code;
		llvm::raw_fd_ostream dest(Filename, err_code, llvm::sys::fs::F_None);
		if (err_code) {
			std::cerr << "Could not open file: " << err_code.message();
			return 1;
		}
		llvm::legacy::PassManager pass;
		//if (TheTargetMachine->addPassesToEmitFile(pass, dest, llvm::TargetMachine::CGFT_ObjectFile)) {
		//if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, llvm::TargetMachine::CGFT_ObjectFile)) {
		if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, llvm::TargetMachine::CGFT_AssemblyFile)) {
				std::cerr << "TheTargetMachine can't emit a file of this type\n";
			return 1;
		}
		pass.run(*M);
		dest.flush();
	}
#endif


	return 0;
}

void dump2(Module &M)
{
	for (auto &F : M)
	{
		printf("[Function Name: %s]\n", F.getName());
		for (auto &B : F)
		{
			printf("[BasicBlock Name: %s]\n", B.getName());
			for (auto &I : B)
			{
				I.dump();
			}
		}
	}
	printf("[End of Dump2]\n\n");
}