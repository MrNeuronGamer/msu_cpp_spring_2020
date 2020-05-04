CC = g++
STANDART = -std=c++14

test: bigint.o test.o
		$(CC) $(STANDART) -O0 -o test bigint.o test.o

bigint.o : bigint.cpp bigint.h
	$(CC) $(STANDART) -O0 -c bigint.cpp

test.o : test.cpp bigint.h
	$(CC) $(STANDART) -O0 -c test.cpp
