#ifndef SEAT
#define SEAT
#include <iostream>
#include <pthread.h>
#include <cassert>
#include "linked.hpp"


class Seat{
	private:
	Job job;
	int timeLeft;
	
	public:
	pthread_mutex_t lockTEST;
	bool isServed;
    
    //for statistics purposes
    std::string _ticket_number;
    int _ticket_issued_time;
    int _response_time;
    int _waiting_time;
	
	Seat();
    Seat(Job j, int reponse_time, int waiting_time, std::string ticket_num, int ticket_issued_time, bool served);
	
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
