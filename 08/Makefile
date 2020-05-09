CC = g++
STANDART = -std=c++14

test: test.o threadpool.o
	$(CC) $(STANDART) -O0 -o test test.o threadpool.o


test.o : test.cpp threadpool.o
	$(CC) $(STANDART) -O0 -c test.cpp threadpool.o

threadpool.o: threadpool.h threadpool.cpp
	$(CC) $(STANDART) -O0 -c threadpool.h threadpool.cpp