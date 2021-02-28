CC = g++

edit : main.o 
	g++ -std=c++11 -pthread -Wall -o test main.o 

pipe: template_pipe.o
	g++ -std=c++11 -pthread -Wall -o pipe template_pipe.o 
	
template_pipe.o: template_pipe.cpp
	cc -c template_pipe.cpp
	
main.o: main.cpp 
	cc -c main.cpp
	
clean:
	rm test pipe main.o template_pipe.o


	
