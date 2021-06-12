#include "sample.h"

#include <spdlog/spdlog.h>

#include <clang/Frontend/FrontendActions.h>
#include <clang/Lex/HeaderSearch.h>
#include <clang/Lex/PreprocessorOptions.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Basic/TargetInfo.h>
#include <clang/Basic/Builtins.h>

#include <llvm/Support/Host.h>

SampleAst::SampleAst() {
}

SampleAst::~SampleAst() {
}

void SampleAst::build() {

}