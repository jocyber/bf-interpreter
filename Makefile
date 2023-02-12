CXXFLAGS := -std=c++20 -O3 -Wall -pedantic-errors

all: bf.o tape.o
	g++ -o bf bf.o tape.o

bf.o: bf.cpp
	g++ ${CXXFLAGS} -c bf.cpp

tape.o: tape.cpp
	g++ ${CXXFLAGS} -c tape.cpp

.PHONY: clean

clean:
	rm *.o
	rm bf
