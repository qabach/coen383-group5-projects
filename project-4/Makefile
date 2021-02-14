CC = g++

edit : main.o linked.o FIFO.o utils.o utils.o memory.o LRU.o
	g++ -std=c++11 -pthread -o test main.o linked.o FIFO.o \
	utils.o memory.o LRU.o


main.o: main.cpp 
	cc -c main.cpp

memory.o: memory.cpp memory.hpp
	cc -c memory.cpp
	
linked.o: linked.cpp linked.hpp
	cc -c linked.cpp
	
	
FIFO.o: FIFO.cpp FIFO.hpp
	cc -c FIFO.cpp
	
LRU.o: LRU.cpp LRU.hpp
	cc -c LRU.cpp
	
utils.o: utils.cpp utils.hpp
	cc -c utils.cpp
	
clean:
	rm test main.o linked.o FIFO.o utils.o memory.o LRU.o


	
