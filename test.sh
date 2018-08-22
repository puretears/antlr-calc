#!/bin/zsh -i

JAVA_OUTPUT=antlr4-runtime-java

antlr4 Calculation.g4 -o $JAVA_OUTPUT
cd $JAVA_OUTPUT
javac Calculation*.java
grun Calculation $1 -gui ../calculation.expr
