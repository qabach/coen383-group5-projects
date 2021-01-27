/*
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Project-2
 Author: Quan Bach
 
 Highest Priority First - preemptive Scheduler Implementation File
 This file is the implementation of HPF-preemptive scheduler
 
 */

#ifndef HPFpreemptive_hpp
#define HPFpreemptive_hpp

#include <string>
#include "roundRobin.hpp"
#include "stats.hpp"

// utility struct to compute statistics for each priority queue 
struct statistics
{
    int response_time           = 0;
    int total_TurnAroundTime    = 0;
    int total_wait_time         = 0;
    int processed_jobs          = 0;
};

// ultility struct to contain all priority queues and level count
struct HPF_system_queue
{
    // priority queues
    private:
        std::deque<Job> priority_1;
        std::deque<Job> priority_2;
        std::deque<Job> priority_3;
        std::deque<Job> priority_4;
    
    //
    public:
        std::deque<Job> queue_list [4] =
        {
            priority_1,
            priority_2,
            priority_3,
            priority_4
        };
    
    const int levels_count = 4;
    
};

overStat HPFpre_emptive (List * input_list);

#endif /* HPFpreemptive_hpp */
