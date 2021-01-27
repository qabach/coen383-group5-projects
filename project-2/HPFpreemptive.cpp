/*
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Project-2
 Author: Quan Bach
 
 Highest Priority First - preemptive Scheduler Implementation File
 This file is the implementation of HPF-preemptive scheduler
 
 */


/*
 
High Priority First - preemptive Scheduler Implementation
 pre-emptive by Round Robin
 time slice = 1 quanta
 run volume = 100 quantas
 
*/

#include "HPFpreemptive.hpp"


overStat HPFpre_emptive (List * input_list)
{
    // send system message if the job list is empty
    if (input_list == nullptr)
    {
        std::cout << "SYSTEM_MESSAGE: Process List is empty." << std::endl;
        std::cout << std::endl;
    }
    
    // list of statistics for each queue
    statistics q1_stat;
    statistics q2_stat;
    statistics q3_stat;
    statistics q4_stat;
    statistics stat_list [4] = {
        q1_stat,
        q2_stat,
        q3_stat,
        q4_stat
    };
    
    // local variables
    std::deque<Job> process_queue;              // queue for jobs
    std::deque<Job> finished_queue;             // queue for finished jobs
    std::deque<std::string> time_chart ;        // time_chart
    int quantas_limit = 100;
    
    // copy generated jobs from input list to queue
    const Node * tmp = nullptr;
    for (tmp = input_list->getHead(); tmp != nullptr; tmp = tmp->getNext())
    {
        process_queue.push_back(tmp->data);
    }
    std::cout << "Jobs list's size: " << process_queue.size() << std::endl;
    
    // print out the jobs list
    std::cout << " *** HPF-preemptive Scheduler Process List *** " << std::endl;
    for (int i = 0; i < process_queue.size(); i++)
    {
        std::cout << "Name: "    << process_queue[i].getName()  << std::endl;
        std::cout << "Arrival: " << process_queue[i].getArr()   << std::endl;
        std::cout << "Service: " << process_queue[i].getServ()  << std::endl;
        std::cout << "Priority: "<< process_queue[i].getPri()   << std::endl;
        std::cout << std::endl;
    }
    std::cout << " *** END OF HPF-preemptive Scheduler Process List *** " << std::endl;
        
    // for each quantum time pass:
    //  - check the processed queue for jobs arrival
    //  - idle if no jobs
    //  - if there are jobs, add them to queue based on priority
    //  - round robin the first non-empty queue with highest priority
    
    // create a HPF queue struct to simulate multi-queues scheduler
    HPF_system_queue hpf_queue;
    
    // main loop
    for (int quantum = 0; quantum < quantas_limit; quantum++)
    {
        //loop thru the queue add the job from processed queue to HPF queue at this instance of quantum
        for (int idx = 0; idx < process_queue.size(); idx++)
        {
            if (process_queue[idx].getArr() == quantum)
            {
                hpf_queue.queue_list[process_queue[idx].getPri()-1].push_back(process_queue[idx]);
                process_queue.pop_front();
            }
        }
        
        //loop through the queue list to check if each queue is empty
        bool jobServiced = false;
        int i = 0;
        while (i <= hpf_queue.levels_count && !jobServiced)
        {
            // the case of all the queues are empty
            if (i == hpf_queue.levels_count)
            {
                time_chart.push_back("<idle>"); // log in CPU idle if no job in any queue
                i++;
                continue;
            }
            
            // if queue at index i is empty, continue
            if (hpf_queue.queue_list[i].size() == 0)
            {
                i++;
                continue;
            }
            else // case when find the first non-empty queue
            {
                // service job i.e. increment the completion
                hpf_queue.queue_list[i][0].completion++;
                
                // compute response time once
                // check if the process already recorded in time chart
                // if the process name is already recorded in time chart, its response time is already computed
                if (std::find(time_chart.begin(),time_chart.end(),hpf_queue.queue_list[i][0].getName()) == time_chart.end())
                {
                    stat_list[i].response_time += quantum - hpf_queue.queue_list[i][0].getArr(); // compute the respone time 
                }
                
                // log job to time chart
                std:string time_chart_log;
                time_chart_log = hpf_queue.queue_list[i][0].getName() + "-p" + to_string(hpf_queue.queue_list[i][0].getPri());
                time_chart.push_back(time_chart_log);
                
                stat_list[i].processed_jobs++;     // increment the jobs processed thus far
                
                // compute time left of job
                int time_left;
                time_left = hpf_queue.queue_list[i][0].getServ() - hpf_queue.queue_list[i][0].completion;
                // if job is done, pop from queue and push to finished queue
                if (time_left == 0)
                {
                    finished_queue.push_back(hpf_queue.queue_list[i][0]);
                    hpf_queue.queue_list[i].pop_front();
                }
                else // if job is not done, perform round robin on job.
                {
                    hpf_queue.queue_list[i].push_back(hpf_queue.queue_list[i][0]); // append the job to the end of queue
                    hpf_queue.queue_list[i].pop_front(); // pop the front
                }
                jobServiced = true;
            }
        }
        // increment wait time in all jobs for all queues
        for (int r = 0; r < hpf_queue.levels_count; r++)
        {
            for (int s = 0; s < hpf_queue.queue_list[r].size(); s++)
            {
                hpf_queue.queue_list[r][s].stats.waitTime ++;
            }
        }
    }
    //print out time chart
    std::cout << "Time Chart from 0 to 99 quanta:" << std::endl;
    for (int i = 0; i < quantas_limit;i++)
    {
        for (int j = 0; j < i;j++)
        {
            std::cout << "."; // one dot represents one quantum time
        }
        if (i < time_chart.size())
        {
            std::cout << time_chart[i] << std::endl;
        }
        else
        {
            std::cout << "<idle>" << std::endl; //print out idle if no job
        }
    }
    
    
    // loop thru the finished queue to compute the statistics for each queues
    for (int j = 0; j < finished_queue.size(); j++)
    {
        stat_list[finished_queue[j].getPri()-1].total_wait_time += finished_queue[j].stats.waitTime;
        
        // compute Turn Around Time
        // TAT = Wait_time + Service_Time
        stat_list[finished_queue[j].getPri()-1].total_TurnAroundTime = stat_list[finished_queue[j].getPri()-1].total_wait_time + finished_queue[j].completion;
    }
    
    // variables to compute overall stats
    double totalResponseTime   = 0.0;
    double totalTurnarounTime  = 0.0;
    double totalWaitTime       = 0.0;
    int numProcessedJobs    = 0;
    
    
    // print out statistics for each queue
    for(int i = 0; i < hpf_queue.levels_count; i++)
    {
        std::cout << "*************** STATISTICS FOR QUEUE " << i+1 << " *************";
        printAlgoStats(stat_list[i].response_time, stat_list[i].total_TurnAroundTime, stat_list[i].total_wait_time, stat_list[i].processed_jobs);
        totalResponseTime   += stat_list[i].response_time;
        totalTurnarounTime  += stat_list[i].total_TurnAroundTime;
        totalWaitTime       += stat_list[i].total_wait_time;
        numProcessedJobs    += stat_list[i].processed_jobs;
    }
    
    std::cout << "*************** OVERALL STATISTICS FOR  ALL QUEUE *************";
    printAlgoStats(totalResponseTime, totalTurnarounTime, totalWaitTime, numProcessedJobs);

    // free memory
    tmp = nullptr;
    delete tmp;
    
    // Compute avg overall stats of all the queues
    overStat retVal = retStat(totalResponseTime, totalTurnarounTime, totalWaitTime, numProcessedJobs);
    return retVal;
}
