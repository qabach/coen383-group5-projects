CC = g++

edit : main.o linked.o hpfnp.o roundRobin.o FCFS.o srt.o stats.o HPFpreemptive.o sjf.o
	g++ -std=c++11 -o test main.o linked.o hpfnp.o roundRobin.o FCFS.o \
	srt.o stats.o HPFpreemptive.o sjf.o

main.o: main.cpp linked.hpp
	cc -c main.cpp

linked.o: linked.cpp linked.hpp
	cc -c linked.cpp

hpfnp.o: hpfnp.cpp hpfnp.hpp
	cc -c hpfnp.cpp
	
roundRobin.o: roundRobin.cpp roundRobin.hpp
	cc -c roundRobin.cpp

FCFS.o: FCFS.cpp FCFS.hpp
	cc -c FCFS.cpp 

srt.o: srt.cpp srt.hpp
	cc -c srt.cpp
	
stats.o: stats.cpp stats.hpp
	cc -c stats.cpp

HPFpreemptive.o: HPFpreemptive.cpp HPFpreemptive.o
	cc -c HPFpreemptive.cpp

sjf.o: sjf.cpp sjf.hpp
	cc -c sjf.cpp 
	
clean:
	rm test main.o linked.o hpfnp.o roundRobin.o \
	FCFS.o stats.o srt.o HPFpreemptive.o sjf.o
	
