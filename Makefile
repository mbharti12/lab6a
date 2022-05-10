CXX=g++
#CXX=clang++
CXXFLAGS=-g
BINARIES=testWordCount WordCount

all: lab6Test
	./lab6Test

lab6Test: lab6Test.o WordCount.o tddFuncs.o
	${CXX} $^ ${CXXFLAGS} -o $@

clean:
	/bin/rm -f ${BINARIES} *.o