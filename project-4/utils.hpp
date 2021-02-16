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
 
 Project 4
 
 */

#ifndef utils_hpp
#define utils_hpp

#include <cmath>
#include <string>
#include "memory.hpp"
#include "linked.hpp"

int locality_reference(int reference_page, int num_of_pages);
void print_time_log_g(Job *job, int time, int tick, int last_reference, Memory *memory_map, int free_space, Job * ptr, int page_to_evict);
//push the remaining 3 pages into memeory
void pushMore(Memory &m, Job * process);
void print_timestamp_log(Memory &m, Job * process, int timestamp, std::string in);

#endif /* utils_hpp */
