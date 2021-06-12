#include <iostream>

#include <clang/Tooling/CommonOptionsParser.h>
#include "clang/Tooling/Tooling.h"
#include <llvm/Support/CommandLine.h>
#include <clang/Frontend/FrontendActions.h>

using namespace clang::tooling;

#include "sample.h"

// Apply a custom category to all command-line options so that they are the
// only ones displayed.
static llvm::cl::OptionCategory MyToolCategory("my-tool options");

// CommonOptionsParser declares HelpMessage with a description of the common
// command-line options related to the compilation database and input files.
// It's nice to have this help message in all tools.
static llvm::cl::extrahelp CommonHelp(CommonOptionsParser::HelpMessage);

// A help message for this specific tool can be added afterwards.
static llvm::cl::extrahelp MoreHelp("\nMore help text...\n");

int main(int argc, const char **argv) 
{
    // CommonOptionsParser constructor will parse arguments and create a
    // CompilationDatabase.  In case of error it will terminate the program.
    auto OptionsParser = CommonOptionsParser::create(argc, argv, MyToolCategory);

    ClangTool Tool(OptionsParser->getCompilations(),
                 OptionsParser->getSourcePathList());
    return Tool.run(newFrontendActionFactory<clang::SyntaxOnlyAction>().get());
}