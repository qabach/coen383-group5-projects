//
//  LRU.hpp
//  Project_4_AT
//
//

#ifndef LRU_hpp
#define LRU_hpp

#include <stdio.h>
#include <set>
#include <tuple>
#include "memory.hpp"
#include "utils.hpp"

std::tuple<int,int,int> LRU(const CustomQueue myQueue, bool sim);
void pLRU(Memory &m, std::vector<Job *> &jobs, Job *insertLoc, int num, int timestamp);
void LRUpushMore(Memory &m, Job * process);
void LRUprintTimeStampMS(std::string cProc, int cPage, int timestamp, int PageInMem, std::string rProc, int Page_TBE);


#endif /* LRU_hpp */
