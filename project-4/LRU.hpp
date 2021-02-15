//
//  LRU.hpp
//  Project_4_AT
//
//

#ifndef FIFO_hpp
#define FIFO_hpp

#include <stdio.h>
#include <set>
#include "memory.hpp"
#include "utils.hpp"

size_t LRU(const CustomQueue myQueue, double &rate,bool sim);
void pLRU(Memory &m, std::vector<Job *> &jobs, Job *insertLoc, int num, int timestamp);
void LRUpushMore(Memory &m, Job * process);
void LRUprintTimeStamp(Memory &m, Job * process, int timestamp, std::string in);
void LRUprintTimeStampMS(std::string cProc, int cPage, int timestamp, int PageInMem, std::string rProc, int Page_TBE);


#endif /* FIFO_hpp */
