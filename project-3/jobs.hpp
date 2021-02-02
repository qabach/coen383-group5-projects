#ifndef JOBSNOW
#define JOBSNOW
#include <iostream>
#include <pthread.h>
#include <cassert>
#include "linked.hpp"

//class for your basic Jobs;
class Jobs{
	public:
	//public variables (yay?)
	std::string name;
	int arrivalTime, serviceTime, priority;
	
	//constructors
	Jobs();
	Jobs(int a, int s, int p, std::string name);
    
		
	//getter stuff
	std::string getName(){return name;}
	int getArr(){return arrivalTime;}
	const int getArr() const{return arrivalTime;}
	int getServ(){return serviceTime;}
	const int getServ() const{return serviceTime;}
	 
	
};

class Seat{
	private:
	Jobs job;
	int timeLeft;
	
	public:
	pthread_mutex_t lock;
	bool isServed;
	
	Seat();
	Seat(Jobs j);
	
	//destrucor
	~Seat();
	
	//getters
	int getCustArr(){return job.arrivalTime;}
	const int getCustArr() const{return job.arrivalTime;}
	int getCustServ(){return job.serviceTime;}
	const int getCustServ() const{return job.serviceTime;}
	
	int getTimeLeft(){return timeLeft;}
	const int getTimeLeft() const{return timeLeft;}
	
	//setters
    void decrementTime(){--timeLeft;}
    bool isFinished();

};
#endif
