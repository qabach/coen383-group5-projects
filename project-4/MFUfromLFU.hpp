/*
 
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Group 5
    Author: Quan Bach
 
 Project 4
    This file is the implementation of the Most Frequently Used swapping algorithm
 */

#ifndef MFUfromLFU_hpp
#define MFUfromLFU_hpp

#include <deque>
#include <iostream>
#include <vector>
#include <string>
#include "linked.hpp"
#include "utils.hpp"
#include "memory.hpp"

//Least Frequently Used Swapping Algorithm
std::tuple<int,int,int> MFU_paging(CustomQueue customer_queue);

//print time log
void print_time_log_MFU (Job *job, int time, int last_reference,Memory *memory_map, int free_space, Job * ptr, int page_to_evict);
#endif /* MFU_hpp */
