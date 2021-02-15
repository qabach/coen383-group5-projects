//
//  random2.hpp
//  COEN383
//
//  Created by Pauldin Bebla on 2/15/21.
//

#ifndef random2_h
#define random2_h

#include <deque>
#include <iostream>
#include <vector>
#include <string>
#include "linked.hpp"
#include "utils.hpp"
#include "memory.hpp"
#include <cstdlib>
#include <ctime>
std::tuple<int,int,int> Random_paging(CustomQueue customer_queue);

//print time log
void print_time_log_rand (Job *job, int time, int last_reference,Memory *memory_map, int free_space, Job * ptr, int page_to_evict);
#endif /* random2_h */
