grammar Calculation;
import Numbers;

@header {
#include <map>
#include <string>
#include <iostream>

#include "antlr4-runtime.h"

using std::map;
using std::cout;
using std::endl;
using std::string;
using antlrcpp::Any;
}

@parser::members {
    map<string, int> symbols;

    int eval(int l, int op, int r) {
        switch (op) {
            case ADD: return l + r;
            case SUB: return l - r;
            case MUL: return l * r;
            case DIV: return l / r;
        }

        return 0;
    }
}

program: statement+;

statement: expression 
    {
        cout<<"EXPR: "<<$expression.v<<endl;
    } # print
    | IDENTIFIER '=' expression
    {
        symbols[$IDENTIFIER.text] = $expression.v;
        cout<<"ASSIGN: "<<symbols[$IDENTIFIER.text]<<endl;
    } 
    # assignment
    | NEWLINE # blank
    ;

expression returns [int v]
    : l=expression OP=('*' | '/') r=expression 
     {
        $v = eval($l.v, $OP.type, $r.v);
        cout<<"MulDiv:"
            <<" L:"<<$l.v
            <<" OP:"<<$OP.text
            <<" R:"<<$r.v<<endl;
    } # mulDiv
    | l=expression OP=('+' | '-') r=expression 
    {
        $v = eval($l.v, $OP.type, $r.v);
        cout<<"AddSub:"
            <<" L:"<<$l.v
            <<" OP:"<<$OP.text
            <<" R:"<<$r.v<<endl;
    } # addSub
    | SIGN=('+' | '-')? Number 
    {
        $SIGN.text == "-" ? $v = -$Number.int : $v = $Number.int;
        cout<<"Number: "<<$v<<endl;
    } # result
    | IDENTIFIER 
    {
        $v = 0;
        if (symbols.count($IDENTIFIER.text) != 0) {
            $v = symbols[$IDENTIFIER.text];
            cout<<"Variable: "<<$IDENTIFIER.text<<"="<<$v<<endl;
        }
    } # iden
    | '(' expression ')' 
    {
        $v = $expression.v;
        cout<<"Parenthesis: ("<<$expression.text<<")"<<endl;
    } # paren
    ;

MUL: '*';
DIV: '/';
ADD: '+';
SUB: '-';

IDENTIFIER: [a-zA-Z]+;
NEWLINE: '\r'?'\n' -> skip;
SPACES: [ \t]+ -> skip;
