CC = g++
STANDART = -std=c++14


parser.o: parser.cpp parser.hpp
	$(CC) $(STANDART) -O0 -c parser.cpp parser.hpp

test.o :test.cpp parser.hpp
	$(CC) $(STANDART) -O0 -c test.cpp parser.hpp

test: test.o parser.o
	$(CC) $(STANDART) -O0 -o test parser.o test.o
