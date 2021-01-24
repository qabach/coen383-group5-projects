/*
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Project-2
 Author: Quan Bach
 
 Round Robin Header File 
 This file is the implementation of round robin scheduler
 
 */

#ifndef roundRobin_hpp
#define roundRobin_hpp

#include <deque>
#include <iostream>
#include <algorithm> // for find 
#include "linked.hpp"

// statistics to print out
// each scheduler should calculate its own statistics and return this struct
struct statistics
{
    double average_turn_around_time;
    double average_waiting_time;
    double average_response_time;
    double throughput; 
};

struct statistics* round_robin_scheduler(List *input_list);

#endif /* roundRobin_hpp */
