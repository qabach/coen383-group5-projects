CC = g++

edit : main.o seat.o linked.o multithreads_seller.o displayMatrix.o
	g++ -std=c++11 -pthread -o test main.o seat.o linked.o multithreads_seller.o displayMatrix.o


main.o: main.cpp multithreads_seller.hpp
	cc -c main.cpp

seats.o: seat.cpp seat.hpp
	cc -c seat.cpp

linked.o: linked.cpp linked.hpp
	cc -c linked.cpp

multithreads_seller.o: multithreads_seller.cpp multithreads_seller.hpp
	cc -c multithreads_seller.cpp

displayMatrix.o: displayMatrix.cpp displayMatrix.hpp
	cc -c displayMatrix.cpp
	
displayMatrix.o: displayMatrix.cpp displayMatrix.hpp
	cc -c displayMatrix.cpp
	
clean:
	rm test main.o seat.o multithreads_seller.o linked.o displayMatrix.o


	
