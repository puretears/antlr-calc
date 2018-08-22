#ifndef MY_VISITOR_H
#define MY_VISITOR_H

#include <map>
#include <string>
#include <iostream>

#include "antlr4-runtime.h"
#include "antlr4-runtime-cpp/CalculationLexer.h"
#include "antlr4-runtime-cpp/CalculationParser.h"
#include "antlr4-runtime-cpp/CalculationBaseVisitor.h"

using std::map;
using std::cout;
using std::endl;
using std::string;
using antlrcpp::Any;

class MyVisitor: public CalculationBaseVisitor {
    map<string, int> symbols;
public:
    MyVisitor(): symbols(map<string, int>()) {}

public:
    virtual antlrcpp::Any visitResult(CalculationParser::ResultContext *ctx) override {
        int value = std::stoi(ctx->getText());

        #ifdef DEBUG
        cout<<"CALLED: visitResult"<<endl;
        cout<<"Number: "<<value<<endl;
        #endif

        return value;
    }

    virtual antlrcpp::Any visitAssignment(CalculationParser::AssignmentContext *ctx) override {
        // IDENTIFIER '=' expression
        string varName = ctx->IDENTIFIER()->toString();
        int value = visit(ctx->expression());

        symbols[varName] = value;

        #ifdef DEBUG
        cout<<"CALLED: visitAssignment"<<endl;
        cout<<"["<<varName<<"]="<<value<<endl;
        #endif

        return value;
    }

    virtual antlrcpp::Any visitAddSub(
        CalculationParser::AddSubContext *ctx) override {

        int left = visit(ctx->expression()[0]);
        int right = visit(ctx->expression()[1]);
        int result = 0;

        if (ctx->OP->getType() == CalculationParser::ADD) {
            result = left + right;
        }
        else {
            result = left - right;
        }

        #ifdef DEBUG
        cout<<"CALLED: visitAddSub"<<endl;
        cout<<"RESULT: "<<result<<endl;
        #endif

        return result;
    }

    virtual antlrcpp::Any visitMulDiv(
        CalculationParser::MulDivContext *ctx) override {

        int left = visit(ctx->expression()[0]);
        int right = visit(ctx->expression()[1]);
        int result = 0;

        if (ctx->OP->getType() == CalculationParser::MUL) {
            result = left * right;
        }
        else {
            result = left / right;
        }

        #ifdef DEBUG
        cout<<"CALLED: visitMulDiv"<<endl;
        cout<<"RESULT: "<<result<<endl;
        #endif

        return result;
    }

    virtual antlrcpp::Any visitIden(CalculationParser::IdenContext *ctx) override {
        int value = symbols[ctx->IDENTIFIER()->getText()];

        #ifdef DEBUG
        cout<<"CALLED: visitIden"<<endl;
        cout<<"Value: "<<value<<endl;
        #endif

        return value;
    }

    virtual antlrcpp::Any visitParen(
        CalculationParser::ParenContext *ctx) override {
        int value = visit(ctx->expression());

        #ifdef DEBUG
        cout<<"CALLED: visitParen"<<endl;
        cout<<"(expr): "<<value<<endl;
        #endif

        return value;
    }
};

#endif
