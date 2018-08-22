#ifndef MY_LISTENER_H
#define MY_LISTENER_H

#include <iostream>

#include "antlr4-runtime-cpp/CalculationBaseListener.h"

using std::cout;
using std::endl;

class MyListener: public CalculationBaseListener {
    int tabs;

    template<typename T> void formatter(T *ctx) {
        for (auto tmp = tabs; tmp != 0; --tmp) {
            cout<<"|>>>";
        }

        if (tabs != 0) { cout<<" "; }

        cout<<ctx->expression()[0]->getText()
            <<ctx->OP->getText()
            <<ctx->expression()[1]->getText()<<endl;
    }

    inline void decreaseTab() { --tabs; }
    inline void increaseTab() { ++tabs; }
public:
    MyListener(): tabs(0) {}

public:
    virtual void enterMulDiv(CalculationParser::MulDivContext * ctx) override {
        formatter(ctx);
        increaseTab();
    }

    virtual void exitMulDiv(CalculationParser::MulDivContext * ctx) override { 
        decreaseTab();
    }

    virtual void enterAddSub(CalculationParser::AddSubContext * ctx) override {
        formatter(ctx);
        increaseTab();
    }

    virtual void exitAddSub(CalculationParser::AddSubContext * ctx) override {
        decreaseTab();
    }
};

#endif
