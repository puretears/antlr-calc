CC=clang++
CXXFLAGS=-I/usr/local/include/antlr4-runtime -c -std=c++1z -Werror
LDFLAGS=-L/usr/local/lib -lantlr4-runtime

BUILD_DIR=output
APP=$(BUILD_DIR)/calc
OBJS=$(BUILD_DIR)/main.o $(BUILD_DIR)/CalculationLexer.o $(BUILD_DIR)/CalculationParser.o
SOURCE=main.cpp CalculationLexer.cpp CalculationParser.cpp
VPATH=./antlr4-runtime-cpp

#output/calc : output/main.o output/CalculationLexer.o output/CalculationParser.o
$(APP): $(OBJS)
# clang++ -L/usr/local/lib -lantlr4-runtime output/main.o output/CalculationLexer.o output/CalculationParser.o -o output/calc
	$(CC) $(LDFLAGS) $^ -o $@

$(BUILD_DIR)/%.o: %.cpp
# clang++ -I/usr/local/include/antlr4-runtime -c -std=c++1z -Werror main.cpp -o main.o
	$(CC) $(CXXFLAGS) $< -o $@

# main.o main.d: main.cpp

%.d: %.cpp
	@echo "Generating dependencies of $*"
	@set -e; rm -f $@; \
	$(CC) $(CXXFLAGS) -MM $< > $@.$$$$; \
	sed 's/\($*\)\.o[ :]*/\1.o $@ : /g' < $@.$$$$ > $@; \
	rm -f $@.$$$$
	
include $(SOURCE:.cpp=.d)

.PHONY: clean
clean:
	-rm -rf $(BUILD_DIR)/*
	-rm *.d
