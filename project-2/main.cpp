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
    overStat rr_endingStats;
    overStat hpfe_endingStats;
    overStat statEndingValueHPFNP[5];
    vector<struct overStat> stats1;
    srand(time(NULL));
    for (int i = 0; i < WORKLOAD; i++)
    {
        cout << "***************************** RUN "<< i+1 << " *********************************" << endl << endl;
        List yay;
        int count, count2;
        yay = List();
        //generate 10 jobs
      
        count = generateJob(yay,1,100);
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
        overStat rr_stats;
        overStat hpfe_stats;
        
        //run 6 algorithm
        //statRunningValue = FCFS(&yay);            // First Come First Serve
        rr_stats = round_robin_scheduler(&yay);     // Round Robin
  	    sjf(yay);                                   // Shortest Job First
        srt(yay);                                   // Shortest Remaining Time First
        hpfnp(yay,stats1);                     // Highest Priority First - non_preemptive
        hpfe_stats = HPFpre_emptive(&yay);                       // Highest Priority First - preemptive

        statEndingValue.AveResponseTime += statRunningValue.AveResponseTime;
        statEndingValue.AveWaitTime += statRunningValue.AveWaitTime;
        statEndingValue.AveTurnaroundTime += statRunningValue.AveTurnaroundTime;
        statEndingValue.AveThroughput += statRunningValue.AveThroughput;
        
        // Round Robin overall avg stats after WORKLOAD run
        rr_endingStats.AveResponseTime      += rr_stats.AveResponseTime;
        rr_endingStats.AveWaitTime          += rr_stats.AveWaitTime;
        rr_endingStats.AveTurnaroundTime    += rr_stats.AveTurnaroundTime;
        rr_endingStats.AveThroughput        += rr_stats.AveThroughput;
        
        // HPF preemptive overall avg stats after WORKLOAD run
        hpfe_endingStats.AveResponseTime    += hpfe_stats.AveResponseTime;
        hpfe_endingStats.AveWaitTime        += hpfe_stats.AveWaitTime;
        hpfe_endingStats.AveTurnaroundTime  += hpfe_stats.AveTurnaroundTime;
        hpfe_endingStats.AveThroughput      += hpfe_stats.AveThroughput;
        

        for(int j = 0; j < 5 ;++j)
        {
        	statEndingValueHPFNP[i].AveResponseTime += stats1[i].AveResponseTime;
          statEndingValueHPFNP[i].AveWaitTime += stats1[i].AveWaitTime;
          statEndingValueHPFNP[i].AveTurnaroundTime += stats1[i].AveTurnaroundTime;
          statEndingValueHPFNP[i].AveThroughput += stats1[i].AveThroughput;
        }

        yay.clr();
    }
    cout<<"*************** Avg HPFNP *************** "<<endl;
    for(int j = 0; j < 5 ;++j)
    {	
    		if(j <4)
    		{
    		cout<<"*************** Q" << to_string(j+1)
    			<< "*************** "<<endl;
    		}
    		else
    		{
    			cout<<"*************** Total HPFNP *************** "<<endl;
    		}
		    printOverStat(statEndingValueHPFNP[j]);
    }
    printOverStat(statEndingValue);
    
    cout << "*************** ROUND ROBIN OVERALL STATS **************************";
    printOverStat(rr_endingStats);
    cout << "*************** HPF Preemptive OVERALL STATS ***********************";
    printOverStat(hpfe_endingStats);

    
    cout << "end of program" <<endl;
    return 0;
}

