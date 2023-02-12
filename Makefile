all: bf.o
	g++ -o bf bf.o

bf.o: bf.cpp
	g++ -std=c++20 -O3 -Wall -pedantic-errors -c bf.cpp

.PHONY: clean

clean:
	rm *.o
