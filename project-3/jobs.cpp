#include "jobs.hpp"

//class for your basic Job; (copied from project2)
Job::Job()
{
	arrivalTime = 0;
	serviceTime = 0;
	name = "None";	
}

//Makes the Job Class with parameters
//Param: a->arrival, b->service, nam-> name of service
Job::Job(int a, int b, std::string nam = "None")
{
	arrivalTime = a;
	serviceTime = b;
	name = nam;
	
}

Seat::Seat()
{
	int rc = pthread_mutex_init(&lock,NULL);
	assert(rc ==0);
	timeLeft = 0;
	isServed = false;
}

Seat::Seat(Job j)
{
	job = j;
	int rc = pthread_mutex_init(&lock,NULL);
	assert(rc ==0);
	timeLeft = j.getServ();
	isServed = false;
	
}

Seat::~Seat()
{
	int rc = pthread_mutex_destroy(&lock);
	assert(rc ==0);
}
