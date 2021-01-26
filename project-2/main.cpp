/*
 
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Group 5
    Anh Truong
    Pauldin Bebla
    Quan Bach
    Travis Le
    Yukun Zhang
 
 Project 2
 
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "linked.hpp"
#include "FCFS.hpp"
#include "stats.hpp"
#include "hpfnp.hpp"
#include "sjf.hpp"
#include "roundRobin.hpp"

using namespace std;

// Const number of workload
const int WORKLOAD = 5;

// RR demo func declaration
void round_robin_demo();


//Generate a Random Job
//Paramas: a->the List working with, startpoint -> where you want to start,
//count -> how many elements


int generateJob(List &a, int startpoint, int count)
{
    int i;
    Job jobs;
    int arr, serv, pri;
    //generate the random values for a job.
    for(i = startpoint;  i <= startpoint + count - 1; ++i)
    {
        string n = "P" + to_string(i);
        arr = rand() %100;
        serv = (rand() % 11) + 1;
        pri = (rand() % 4) + 1;
        jobs=Job(arr, serv, pri,n);
        a.insertData(jobs);
    }
    return i;
}


int main()
{
	cout << "Note: this is C++" <<endl;
	List yay;
	int seed = 1;
	int count, count2;
	srand(time(NULL));
	yay = List();
	//generate 10 jobs
	count = generateJob(yay,1,10);
	count2 = 5;
	//generatate more jobs if needed
	while(yay.notIdle())
	{
		count = generateJob(yay,count,count2);
		count2 += 5;
	}
	cout <<"Starting # of Jobs: " << yay.length() << endl;
	//run algo
	hpfnp(yay);
	sjf(yay);
  FCFS(&yay);     // First Come First Serve
	yay.clr();
	
  // Round Robin Demo
  round_robin_demo();
    

    
   cout << "end of program" <<endl;
   return 0;

    
}

void round_robin_demo()
{
    for (int i = 0; i < WORKLOAD; i++)
    {
        cout << "*** Round Robin run: " << i+1 << " ***" << endl;
        List yay;
        time_t seed = time(NULL);
        int count, count2;
        srand(seed);
        yay = List();
        //generate 10 jobs
        count = generateJob(yay,1,10);
        count2 = 2;
        //generatate more jobs if needed
        while(yay.notIdle())
        {
            count = generateJob(yay,count,count2);
            count2 *= 2;
        }        
        // Round-Robin Scheduler
        round_robin_scheduler(&yay);
        
        yay.clr();
    }
}





