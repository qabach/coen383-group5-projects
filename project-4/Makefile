CC = g++

edit : main.o linked.o FIFO.o utils.o  memory.o LRU.o LFU.o MFUfromLFU.o random2.o
	g++ -std=c++11 -pthread -Wall -o test main.o linked.o FIFO.o \
	utils.o memory.o LRU.o LFU.o MFUfromLFU.o random2.o


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
		
LFU.o: LFU.cpp LFU.hpp
	cc -c LFU.cpp
utils.o: utils.cpp utils.hpp
	cc -c utils.cpp

MFUfromLFU.o: MFUfromLFU.cpp MFUfromLFU.hpp
	cc -c MFUfromLFU.cpp

random2.o: random2.cpp random2.hpp
	cc -c random2.cpp
	
clean:
	rm test main.o linked.o FIFO.o utils.o memory.o LRU.o LFU.o MFUfromLFU.o random2.o


	
