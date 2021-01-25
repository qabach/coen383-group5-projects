CC = g++

edit : main.o linked.o hpfnp.o roundRobin.o
	g++ -o test main.o linked.o hpfnp.o roundRobin.o

main.o: main.cpp linked.hpp
	cc -c main.cpp

linked.o: linked.cpp linked.hpp
	cc -c linked.cpp

hpfnp.o: hpfnp.cpp hpfnp.hpp
	cc -c hpfnp.cpp
	
roundRobin.o: roundRobin.cpp roundRobin.hpp
	cc -c roundRobin.cpp

clean:
	rm test main.o linked.o hpfnp.o roundRobin.o
