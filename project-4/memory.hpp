//
//  memory.hpp
//  Project_4_AT
//
//  Created by Anh Tuk on 2/12/21.
//

#ifndef memory_hpp
#define memory_hpp

#include <stdio.h>
#include <set>
#include <tuple>
#include "linked.hpp"
#include <iostream>


class Memory
{
private:
    std::vector<std::tuple<int, Job*>> _memMap;
    int _inMemNum;
    std::vector<int> _freePage;
    int _freePageNum;
    
public:
    Memory();
    Memory(std::vector<std::tuple<int, Job*>> memMap, int inMemNum );
    Memory(std::vector<std::tuple<int, Job*>> memMap, int inMemNum, std::vector<int> frePage, int freePageNum );
    
    
    // getter
    int getInMemNum() { return _inMemNum;}
    int getFreeMemNum() { return _freePageNum;}
    int getNumProcess (std::vector<std::tuple<int, Job*>> memMap);
    int getFreePage();
    void printMem();
    void printFreePageList();
    std::vector<std::tuple<int, Job *>> getMemMap() { return _memMap ;}
   
    
    
    //setter
    void setInMemNum(int inMemNum) { _inMemNum = inMemNum;}
    void setFreeMemNum(int freePageNum) { _freePageNum = freePageNum;}
    
    void insertPageToMem(Job * process, int pageNum);
    void removePageFromMem(Job * process, int pageNum);
    void removeProcessFromMem(Job * process);

    

    
};


#endif /* memory_hpp */
