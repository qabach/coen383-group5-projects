CC = g++

edit : main.o linked.o
	g++ -o test main.o linked.o

main.o: main.cpp linked.hpp
	cc -c main.cpp

linked.o: linked.cpp linked.hpp
	cc -c linked.cpp

clean:
	rm test main.o linked.o
