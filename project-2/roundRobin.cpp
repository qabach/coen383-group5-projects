/*
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Project-2
 Author: Quan Bach
 
 Round Robin Implementation File 
 This file is the implementation of round robin scheduler
 
 */

#include "roundRobin.hpp"


/*
 
Round Robin Scheduler Implementation
 time slice = 1 quanta
 run volume = 100 quantas
 
*/

overStat round_robin_scheduler(List *input_list)
{
    
    // send system message if the job list is empty
    if (input_list == nullptr)
    {
        std::cout << "SYSTEM_MESSAGE: Process Queue is empty." << std::endl;
        std::cout << std::endl;
    }
        
    // local variables
    std::deque<Job> copy_queue;                // queue to copy from job lists
    std::deque<Job> process_queue;              // queue for jobs
    std::deque<Job> finished_queue;             // queue for finished jobs
    std::deque<std::string> time_chart ;        // time_chart
    int quantas_limit = 100;                    // the amount of CPU run
    
    
    // statistics variables
    double waiting_time         = 0.0;
    double response_time        = 0.0;
    int    jobs_processed_count = 0;
    
        
    // copy generated jobs from input list to queue
    const Node * tmp = nullptr;
    for (tmp = input_list->getHead(); tmp != nullptr; tmp = tmp->getNext())
    {
        copy_queue.push_back(tmp->data);
    }
    
    std::cout << "Jobs queue's size: " << copy_queue.size() << std::endl;
    
    // print out the jobs list
    std::cout << " *** RR Sheduler Process List *** " << std::endl;
    for (int i = 0; i < copy_queue.size(); i++)
    {
        std::cout << "Name: "    << copy_queue[i].getName()  << std::endl;
        std::cout << "Arrival: " << copy_queue[i].getArr()   << std::endl;
        std::cout << "Service: " << copy_queue[i].getServ()  << std::endl;
        std::cout << "Priority: "<< copy_queue[i].getPri()   << std::endl;
        std::cout << std::endl;
    }
    std::cout << " *** END OF RR Sheduler Process List *** " << std::endl;
    
    // main loop to run 100 quantas 1-100
    for (int quantum = 0; quantum < quantas_limit; quantum++)
    {
        for (int idx = 0; idx < copy_queue.size(); idx++)
        {
            if (copy_queue[0].getArr() == quantum)
            {
                process_queue.push_back(copy_queue[0]);
                copy_queue.pop_front();
            }
        }
        
        // if the queue is empty, then CPU will idle
        if (process_queue.size() == 0)
        {
            time_chart.push_back("<idle>"); // log in idle when no job
            continue;
        }
        // CPU idle if the job has not arrived
        if (process_queue[0].getArr() > quantum)
        {
            time_chart.push_back("<idle>"); // log in idle when no job
            continue;
        }
        
        // compute response time once
        // check if the process already recorded in time chart
        // if the process name is already recorded in time chart, its response time is already computed
        if (std::find(time_chart.begin(),time_chart.end(),process_queue[0].getName()) == time_chart.end())
        {
            response_time += quantum - process_queue[0].getArr();
            waiting_time += response_time;         // increment waiting time of servicing job in case it has been waiting
            jobs_processed_count++; // increment the count of jobs processed

        }
        
        // increment wait time of all the jobs in queue
        for (int idx = 0; idx < process_queue.size(); idx++)
        {
            process_queue[idx].stats.waitTime += 1;
        }
        
        // increment completion time for current job
        process_queue[0].completion += 1;
        // compute time left for job
        int time_left;
        time_left = process_queue[0].getServ() - process_queue[0].completion; //once service the job, decrement the service time
        
        //add to the time chart
        time_chart.push_back(process_queue[0].getName());
        
        if (time_left == 0) // if time left is 0, then remove the job from the schedule queue and add job to the finished queue
        {
            finished_queue.push_back(process_queue[0]);
            process_queue.pop_front();
        }
        else // if time left is not 0, then move it to the back of the queue with updated service time
        {
            process_queue.push_back(process_queue[0]); // append job at the end of queue
            process_queue.pop_front();            // remove job in front
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
    
    // get all waiting time and completion
    int total_wait_time = 0;
    int total_wait_time_of_finised_jobs = 0;
    int total_completion = 0;
    for (int j = 0; j < process_queue.size(); j++)
    {
        total_wait_time += process_queue[0].stats.waitTime;
    }
    
    for (int j = 0; j < finished_queue.size(); j++)
    {
        total_wait_time_of_finised_jobs += process_queue[0].stats.waitTime;
        total_completion += process_queue[0].completion;
    }
    
    // compute Turn Around Time
    // TAT = Wait_time + Service_Time
    int total_TAT = total_completion + total_wait_time_of_finised_jobs;
    
    // print out statistics 
    printAlgoStats(response_time, total_TAT, total_wait_time_of_finised_jobs, jobs_processed_count);
    

    // Store Average Stats to return
    overStat retVal = retStat(response_time, total_TAT, total_wait_time_of_finised_jobs, jobs_processed_count);

    
    return retVal;
    
}


