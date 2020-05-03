CC = g++
STANDART = -std=c++14

test:  test.o
		$(CC) $(STANDART) -O0 -o test  test.o


test.o : test.cpp format.h
	$(CC) $(STANDART) -O0 -c test.cpp format.h
