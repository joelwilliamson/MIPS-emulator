#MakeFile allows a program to only recompile the updated files and any files that
#depend on the updated files. MakeFile achieves this objective by tracking the dependencies
#between programs.

#uses the g++ compiler
CXX = g++
#turns on warn-all and explicit dependency tracking
CXXFLAGS += -Wall -MMD -ggdb -std=c++14
EXEC = main
#replaces all occurrences of .o at the end of a name with .d
OBJECTS = register.o processor.o types.o
DEPENDS = ${OBJECTS:.o=.d}

#creates file dependencies in make syntax
${EXEC}: ${OBJECTS} main.o ${LAUNCHER_SCRIPT}
	${CXX} ${CXXFLAGS} ${OBJECTS} main.o -o ${EXEC}

#import all .d files
-include ${DEPENDS} main.d

#put target clean at the end of the makefile
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS} ${LAUNCHER_SCRIPT}

test: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} tests/processor.cpp -o tests/processor
	tests/processor

.PHONY: clean
