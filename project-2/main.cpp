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
#include "srt.hpp"
#include "HPFpreemptive.hpp"

using namespace std;

// Const number of workload
const int WORKLOAD = 5;

// RR demo func declaration
//void round_robin_demo();

//Generate a Random Job
//Paramas: a->the List working with, startpoint -> where you want to start,
//count -> how many elements

int generateJob(List &a, int startpoint, int count)
{
    int i;
    Job jobs;
    int arr, serv, pri;
    //generate the random values for a job.
    for (i = startpoint; i <= startpoint + count - 1; ++i)
    {
        string n = "P" + to_string(i);
        arr = rand() % 100;
        serv = (rand() % 11) + 1;
        pri = (rand() % 4) + 1;
        jobs = Job(arr, serv, pri, n);
        a.insertData(jobs);
    }
    return i;
}

int main()
{
	cout << "Note: this is C++" <<endl;
    
    // keep track of the running total stats for each algorithm
    overStat statEndingValue;
    
    for (int i = 0; i < WORKLOAD; i++)
    {
        cout << "***************************** RUN "<< i+1 << " *********************************" << endl << endl;
        List yay;
        int seed = 1;
        int count, count2;
        srand(time(NULL));
        yay = List();
        //generate 10 jobs
      
        count = generateJob(yay,1,10);
        count2 = 2;
      
        //generatate more jobs if needed
        while (yay.notIdle())
        {

            count = generateJob(yay,count,count2);
            count2 += 5;
        }
        cout <<"Starting # of Jobs: " << yay.length() << endl;
        
        // keep track of the running total stats for each algorithm
        overStat statRunningValue;
        
        //run 6 algorithm
        statRunningValue = FCFS(&yay);     // First Come First Serve
        //round_robin_scheduler(&yay);    
  	    // sjf(yay);                       // Shortest Job First 
        // srt(yay);                       // Shortest Remaining Time First 
        // hpfnp(yay);                     // Highest Priority First - non_preemptive
        // HPFpre_emptive(&yay);           // Highest Priority First - preemptive
        
        statEndingValue.AveResponseTime += statRunningValue.AveResponseTime;
        statEndingValue.AveWaitTime += statRunningValue.AveWaitTime;
        statEndingValue.AveTurnaroundTime += statRunningValue.AveTurnaroundTime;
        statEndingValue.AveThroughput += statRunningValue.AveThroughput;
        
        yay.clr();
    }
    printOverStat(statEndingValue);
	
    // Round Robin Demo
    //round_robin_demo();
    
    cout << "end of program" <<endl;
    return 0;
}

