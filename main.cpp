#include <fstream>
#include <iostream>

#include "antlr4-runtime.h"
#include "antlr4-runtime-cpp/CalculationLexer.h"
#include "antlr4-runtime-cpp/CalculationParser.h"
#include "antlr4-runtime-cpp/CalculationBaseVisitor.h"

// #include "MyVisitor.h"
// #include "MyListener.h"

using std::cout;
using std::endl;
using std::ifstream;

using antlr4::ANTLRInputStream;
using antlr4::CommonTokenStream;
using antlr4::tree::ParseTree;
using antlr4::tree::ParseTreeWalker;

int main(int argc, char* argv[]) {
    ifstream stream;

    if (argc >= 2) {
        stream.open(argv[1]);

        ANTLRInputStream input = ANTLRInputStream(stream);
        CalculationLexer lexer(&input);
        CommonTokenStream tokens(&lexer);
        CalculationParser parser(&tokens);

        CalculationParser::ProgramContext *tree = parser.program();
        CalculationBaseVisitor visitor;
        visitor.visitProgram(tree);

        return 0;
    }
    
    string expr;
    cout<<"CALC>> ";
    std::getline(std::cin, expr);
    unsigned int currLine = 1;

    CalculationParser parser(nullptr);
    parser.setBuildParseTree(false);

    while (!expr.empty()) {
        ANTLRInputStream input(expr + "\n");
        CalculationLexer lexer(&input);

        lexer.setLine(currLine-1);
        lexer.setCharPositionInLine(0);

        CommonTokenStream tokens(&lexer);
        parser.setInputStream(&tokens);
        parser.program();

        cout<<"CALC>> ";
        std::getline(std::cin, expr);
        ++currLine;
    }
}
