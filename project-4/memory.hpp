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
#include "linked.hpp"
#include <iostream>


class Memory
{
private:
    std::vector<std::tuple<int, Job>> _memMap;
    int _inMemNum;
    std::vector<int> _freePage;
    int _freePageNum;
    
public:
    Memory();
    Memory(std::vector<std::tuple<int, Job>> memMap, int inMemNum );
    Memory(std::vector<std::tuple<int, Job>> memMap, int inMemNum, std::vector<int> frePage, int freePageNum );
    
    
    // getter
    int getInMemNum() { return _inMemNum;}
    int getFreeMemNum() { return _freePageNum;}
    int getNumProcess (std::vector<std::tuple<int, Job>> memMap);
    int getFreePage();
    void printMem();
    void printFreePageList();
   
    
    
    //setter
    void setInMemNum(int inMemNum) { _inMemNum = inMemNum;}
    void setFreeMemNum(int freePageNum) { _freePageNum = freePageNum;}
    
    void insertPageToMem(Job process, int pageNumc);
    void removePageFromMem(Job process, int pageNum);
    

    
};


#endif /* memory_hpp */
