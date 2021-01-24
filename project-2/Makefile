CC = g++

edit : main.o linked.o hpfnp.o
	g++ -o test main.o linked.o hpfnp.o

main.o: main.cpp linked.hpp
	cc -c main.cpp

linked.o: linked.cpp linked.hpp
	cc -c linked.cpp

hpfnp.o: hpfnp.cpp hpfnp.hpp
	cc -c hpfnp.cpp

clean:
	rm test main.o linked.o hpfnp.o
