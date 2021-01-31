CC = g++

edit : main.o jobs.o 
	g++ -std=c++11 -pthread -o test main.o jobs.o

main.o: main.cpp jobs.hpp
	cc -c main.cpp

jobs.o: jobs.cpp jobs.hpp
	cc -c jobs.cpp
	
clean:
	rm test main.o jobs.o

	
