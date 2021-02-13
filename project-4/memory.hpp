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
    std::vector<std::tuple<int, std::string>> _memMap;
    int _inMemNum;
    std::vector<std::tuple<int, std::string>> _freePage;
    int _freePageNum;
    
public:
    Memory();
    Memory(std::vector<std::tuple<int, std::string>> memMap, int inMemNum );
    Memory(std::vector<std::tuple<int, std::string>> memMap, int inMemNum, std::vector<std::tuple<int, std::string>> frePage, int freePageNum );
    
    
    // getter
    int getInMemNum() { return _inMemNum;}
    int getNumProcess (std::vector<std::tuple<int, std::string>> memMap);
    void printMem();
    
    
    //setter
    void setInMemNum(int inMemNum) { _inMemNum = inMemNum;}

    
};


#endif /* memory_hpp */
