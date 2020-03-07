CC = g++
STANDART = -std=c++14

test: allocator.o test_allocator.o
	$(CC) $(STANDART) -O0 -o test allocator.o test_allocator.o 

allocator.o: allocator.cpp allocator.hpp
	$(CC) $(STANDART) -c -O0 allocator.cpp

test_allocator.o: test_allocator.cpp allocator.hpp
	$(CC) $(STANDART) -c -O0 test_allocator.cpp allocator.hpp
clean :
	rm test_allocator.o allocator.o