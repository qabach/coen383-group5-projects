CC = g++

edit : main.o jobs.o 
	g++ -std=c++11 -pthread -o test main.o jobs.o linked.o multithreads_seller.o

main.o: main.cpp jobs.hpp
	cc -c main.cpp

jobs.o: jobs.cpp jobs.hpp
	cc -c jobs.cpp

linked.o: linked.cpp linked.hpp
	cc -c linked.cpp

multithreads_seller.o: multithreads_seller.cpp multithreads_seller.hpp
	cc -c multithreads_seller.cpp
	
clean:
	rm test main.o jobs.o multithreads_seller.o linked.o

	
