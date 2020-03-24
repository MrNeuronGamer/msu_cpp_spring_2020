CC = g++
STANDART = -std=c++14


test.o :test.cpp matrix.hpp
	$(CC) $(STANDART) -O0 -c test.cpp matrix.hpp


matrix.o: matrix.hpp matrix.cpp
	$(CC) $(STANDART) -O0 -c matrix.hpp matrix.cpp

test: matrix.o test.o
	$(CC) $(STANDART) -O0 -o test matrix.o test.o