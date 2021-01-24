//
//  roundRobin.hpp
//  coen-383-projects
//
//  Created by Quan Bach  on 1/24/21.
//

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
