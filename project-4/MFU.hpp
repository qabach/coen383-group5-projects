//
//  MFU.hpp
//  Project_4
//
//

#ifndef MFU_hpp
#define MFU_hpp

#include <stdio.h>
#include <set>
#include "memory.hpp"
#include "utils.hpp"

size_t MFU(CustomQueue myQueue, double &rate);
void pMFU(Memory &m, std::vector<Job *> &jobs, Job *insertLoc, int num, int timestamp);
void MFUpushMore(Memory &m, Job * process);
void MFUprintTimeStamp(Memory &m, Job * process, int timestamp, std::string in);
void MFUprintTimeStampMS(std::string cProc, int cPage, int timestamp, int PageInMem, std::string rProc, int Page_TBE);


#endif /* MFU_hpp */
