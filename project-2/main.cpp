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
        
        // keep track of the running total stats for each algorithm

        overStat statRunningValueFCFS;
        overStat rr_stats;
        overStat hpfe_stats;
        overStat srt_stats;
        overStat sjfStats;

        //run 6 algorithm
        statRunningValueFCFS = FCFS(&yay);                // First Come First Serve
        rr_stats    = round_robin_scheduler(&yay);        // Round Robin
  	    sjfStats = sjf(yay);                              // Shortest Job First
        srt_stats   = srt(yay);                           // Shortest Remaining Time First
        hpfnp(yay,stats1);                                // Highest Priority First - non_preemptive
        hpfe_stats  = HPFpre_emptive(&yay);               // Highest Priority First - preemptive
        
        // FCFS Overall Average Statistics after WORKLOAD runs
        statEndingValueFCFS.AveResponseTime += statRunningValueFCFS.AveResponseTime;
        statEndingValueFCFS.AveWaitTime += statRunningValueFCFS.AveWaitTime;
        statEndingValueFCFS.AveTurnaroundTime += statRunningValueFCFS.AveTurnaroundTime;
        statEndingValueFCFS.AveThroughput += statRunningValueFCFS.AveThroughput;
        
        // Round Robin overall avg stats after WORKLOAD runs
        rr_endingStats.AveResponseTime      += rr_stats.AveResponseTime;
        rr_endingStats.AveWaitTime          += rr_stats.AveWaitTime;
        rr_endingStats.AveTurnaroundTime    += rr_stats.AveTurnaroundTime;
        rr_endingStats.AveThroughput        += rr_stats.AveThroughput;
    
        // SRT overall avg stats after WORKLOAD runs
        srt_endingStats.AveResponseTime += srt_stats.AveResponseTime;
        srt_endingStats.AveWaitTime += srt_stats.AveWaitTime;
        srt_endingStats.AveTurnaroundTime += srt_stats.AveTurnaroundTime;
        srt_endingStats.AveThroughput += srt_stats.AveThroughput;
        
        // HPF preemptive overall avg stats after WORKLOAD runs
        hpfe_endingStats.AveResponseTime    += hpfe_stats.AveResponseTime;
        hpfe_endingStats.AveWaitTime        += hpfe_stats.AveWaitTime;
        hpfe_endingStats.AveTurnaroundTime  += hpfe_stats.AveTurnaroundTime;
        hpfe_endingStats.AveThroughput      += hpfe_stats.AveThroughput;
        
        // HPF non-preemptive overall avg stats after WORKLOAD runs
        for(int j = 0; j < 5 ;++j)
        {





