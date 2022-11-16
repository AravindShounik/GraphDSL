SHELL := /bin/bash
USE_CXX_LEXER := 1

CC       := gcc
CXX      := g++
CLANG    := clang++
CLANGFLAGS:= -g -O3 `llvm-config --system-libs --libs core`
CPPFLAGS :=
CXXFLAGS := -std=c++11 -pedantic -Wall -Wextra

LDLIBS   := -lstdc++

LEX      := flex
LFLAGS   := -v --debug
ifneq (0,${USE_CXX_LEXER})
LFLAGS += --c++
endif

YACC     := bison
YFLAGS   := -v -Wall

ANAME    := main
PNAME    := parser
LNAME    := lexer
CNAME    := context
SNAME		 := semantics
CGNAME   := codegen

${ANAME}: ${ANAME}.o ${CNAME}.o ${PNAME}.o ${LNAME}.o ${SNAME}.o ${CGNAME}.o
	${CLANG} ${CLANGFLAGS} -o $@ $^

# Application dependencies:
${ANAME}.o: ${ANAME}.cc ${CNAME}.o ${SNAME}.o

# Context dependencies:
${CNAME}.o: ${CNAME}.cc ${CNAME}.hh ${PNAME}.hh

# Parser dependencies:
${PNAME}.o: ${PNAME}.cc ${PNAME}.hh

# Lexer dependencies:
${LNAME}.o: ${LNAME}.cc ${PNAME}.hh 

# codegen.cc compilation:
${CGNAME}.o: ${CGNAME}.cc
	${CLANG} ${CLANGFLAGS} -c -o $@ $<

# main.cc compilation:
${ANAME}.o: ${ANAME}.cc
	${CLANG} ${CLANGFLAGS} -c -o $@ $<


# Suppress built-in implicit YACC rule:
%.c: %.y

# Implicit rule for Bison:
%.cc %.hh: %.yy
	${YACC} ${YFLAGS} -o $*.cc --defines=$*.hh $<

# Implicit rule for flex without header generation:
%.cc: %.ll
	${LEX} ${LFLAGS} -o $*.cc $<

%.i: %.cc
	${CXX} -E ${CPPFLAGS} ${CXXFLAGS} -o $@ $<

# test: test1
# 	llc test.ll && gcc test.s -o test
# 	./test
# 	echo $?
# 	rm -f test

clean:
	rm -f $(LNAME:=.cc) $(LNAME:=.hh) $(PNAME:=.hh) $(PNAME:=.cc) 
	rm -f $(PNAME:=.output) position.hh stack.hh location.hh
	rm -f ${ANAME}
	rm -f smake.* *~ *.o *.i *.tab.cc *.tab.hh
	rm -f test*
