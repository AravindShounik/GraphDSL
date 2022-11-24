#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"
#include "llvm/Transforms/Utils.h"
#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <set>
#include "types.h"

using namespace llvm;

static std::unique_ptr<LLVMContext> TheContext;
static std::unique_ptr<Module> TheModule;
static std::unique_ptr<IRBuilder<>> Builder;
static std::map<std::string, AllocaInst *> NamedValues;
static std::unique_ptr<legacy::FunctionPassManager> TheFPM;

static std::map<std::string, FunctionType *> funcList;
static std::map<std::string, FunctionType *> builtInFuncList;

static std::map<std::string, std::pair<GlobalVariable *, int>> graphList;

static void InitializeModuleAndPassManager(void);
static AllocaInst *CreateEntryBlockAlloca(Function *TheFunction, StringRef VarName);
Type *convertType(type_name Ty);

/* this is called from main.cc */
void doCodeGen(const std::vector<common_list> &ast);

static void HandleNode(const node &n);
static void HandleFunction(const function &f);
static Value *codegen(const node &n);
static Function *codegen(const function &f);
void emit(const node_vec &v);
Type *createGraph();

static void AddBuiltInFuncs();
