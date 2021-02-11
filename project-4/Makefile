CC = g++

edit : main.o linked.o 
	g++ -std=c++11 -pthread -o test main.o linked.o 


main.o: main.cpp 
	cc -c main.cpp


linked.o: linked.cpp linked.hpp
	cc -c linked.cpp
	
clean:
	rm test main.o linked.o 


	
