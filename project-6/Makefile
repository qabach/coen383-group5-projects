CC = g++

edit : main.o 
	g++ -std=c++11 -pthread -Wall -o test main.o
	gcc -o ctest main.o

	
main.o: main.cpp 
	cc -c main.cpp
	
clean:
	rm test ctest main.o 

	
