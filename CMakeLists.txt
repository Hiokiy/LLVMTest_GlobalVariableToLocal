cmake_minimum_required(VERSION 3.4.3)
project(PassTest CXX)
enable_language(C)

set(LLVM_DIR C:/Work/LLVM/build/lib/cmake/llvm)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

#llvm_map_components_to_libnames(llvm_a_libs support core irreader scalaropts ipo)
#以下、llcのプロジェクトから参照libをコピーしたが、もっと簡単に指定する方法はないものか・・・
llvm_map_components_to_libnames(
	llvm_a_libs
	support
	core
	irreader
	scalaropts
	ipo
	Analysis
	AsmPrinter
	CodeGen
	MC
	MIRParser
	SelectionDAG
	Target
	TransformUtils
	Vectorize
	AArch64Info
AArch64CodeGen
AArch64AsmParser
AArch64AsmPrinter
AArch64Desc
AArch64Disassembler
AArch64Info
AArch64Utils
AMDGPUCodeGen
AMDGPUAsmParser
AMDGPUAsmPrinter
AMDGPUDesc
AMDGPUDisassembler
AMDGPUInfo
AMDGPUUtils
ARMCodeGen
ARMAsmParser
ARMAsmPrinter
ARMDesc
ARMDisassembler
ARMInfo
ARMUtils
BPFCodeGen
BPFAsmParser
BPFAsmPrinter
BPFDesc
BPFDisassembler
BPFInfo
HexagonCodeGen
HexagonAsmParser
HexagonDesc
HexagonDisassembler
HexagonInfo
LanaiCodeGen
LanaiAsmParser
LanaiAsmPrinter
LanaiDesc
LanaiDisassembler
LanaiInfo
MipsCodeGen
MipsAsmParser
MipsAsmPrinter
MipsDesc
MipsDisassembler
MipsInfo
MSP430CodeGen
MSP430AsmPrinter
MSP430Desc
MSP430Info
NVPTXCodeGen
NVPTXAsmPrinter
NVPTXDesc
NVPTXInfo
PowerPCCodeGen
PowerPCAsmParser
PowerPCAsmPrinter
PowerPCDesc
PowerPCDisassembler
PowerPCInfo
SparcCodeGen
SparcAsmParser
SparcAsmPrinter
SparcDesc
SparcDisassembler
SparcInfo
SystemZCodeGen
SystemZAsmParser
SystemZAsmPrinter
SystemZDesc
SystemZDisassembler
SystemZInfo
X86CodeGen
X86AsmParser
X86AsmPrinter
X86Desc
X86Disassembler
X86Info
X86Utils
XCoreCodeGen
XCoreAsmPrinter
XCoreDesc
XCoreDisassembler
XCoreInfo
Analysis
AsmPrinter
CodeGen
Core
IRReader
MC
MIRParser
ScalarOpts
SelectionDAG
Support
Target
TransformUtils
Vectorize
ipo
Instrumentation
Linker
GlobalISel
MCDisassembler
AggressiveInstCombine
InstCombine
BitWriter
Object
MCParser
BitReader
ProfileData
DebugInfoCodeView
DebugInfoMSF
AsmParser
BinaryFormat
Demangle
)


add_executable(PassTest PassTest.cpp)
target_link_libraries(PassTest ${llvm_a_libs})

add_subdirectory(pass/easypass)
target_link_libraries(PassTest easypass)

add_subdirectory(pass/Power2ToLShift)
target_link_libraries(PassTest Power2ToLShift)

add_subdirectory(pass/GlobalVariableToLocal)
target_link_libraries(PassTest GlobalVariableToLocal)



