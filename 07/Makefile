CC = g++
STANDART = -std=c++17



test: test.o
	$(CC) -o test test.o

test.o: test.cpp vector.cpp
	$(CC) $(STANDART) -c test.cpp vector.cpp


