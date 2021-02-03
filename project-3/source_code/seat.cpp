#include "seat.hpp"

Seat::Seat()
{
	int rc = pthread_mutex_init(&lockTEST,NULL);
	assert(rc ==0);
	timeLeft = 0;
	isServed = false;
}

Seat::Seat(Job j, int response_time, int waiting_time, std::string ticket_num, int ticket_issued_time, bool served)
{
	job = j;
	int rc = pthread_mutex_init(&lockTEST,NULL);
	assert(rc ==0);
	timeLeft = j.getServ();
	isServed = served;
    
    _ticket_number = ticket_num;
    _ticket_issued_time = ticket_issued_time;
    _waiting_time = waiting_time;
    _response_time = response_time;

}

Seat::~Seat()
{
	int rc = pthread_mutex_destroy(&lockTEST);
	assert(rc ==0);
}


bool Seat::isFinished()
{
    if(timeLeft)
    {
        return false;
    }
    return true;
}
