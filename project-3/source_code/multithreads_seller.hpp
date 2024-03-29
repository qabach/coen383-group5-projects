/*
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Project-3
 Author: Quan Bach
 Multi-threads seller implementation 
 Created by Quan Bach  on 1/31/21
 */

#ifndef multithreads_seller_hpp
#define multithreads_seller_hpp

#include <iostream>
#include <pthread.h>
#include <tuple>
#include <vector>
#include <deque>
#include <map>
#include <ctime>
#include <set>
#include "linked.hpp"
#include "seat.hpp"
#include "displayMatrix.hpp"

void multithreads_ticket_seller (int count);



//thread function
void * sell (void * seller_type);

//thread utility function
void wakeup_all_seller_threads();

//function to populate job in queues
void populate_jobs(int count);

//function to convert int to string with leading 0
std::string int_to_string(int num);


#endif /* multithreads_seller_hpp */
