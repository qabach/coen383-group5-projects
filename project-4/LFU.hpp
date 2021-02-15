/*
 
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Group 5
    Author: Quan Bach
 
 Project 4
    This file is the implementation of the Least Frequently Used swapping algorithm 
 */

#ifndef LFU_hpp
#define LFU_hpp

#include <deque>
#include <iostream>
#include <vector>
#include "linked.hpp"
#include "utils.hpp"
#include "memory.hpp"

//Least Frequently Used Swapping Algorithm
void LFU_paging(CustomQueue customer_queue);

//print time log 
void print_time_log (Job *job, int time, int last_reference,Memory *memory_map, int free_space);
#endif /* LFU_hpp */
