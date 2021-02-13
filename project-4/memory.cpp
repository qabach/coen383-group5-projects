//
//  memory.cpp
//  Project_4_AT
//
//  Created by Anh Tuk on 2/12/21.
//

#include "memory.hpp"


// ******************************************************************************
//              CONSTRUCTOR
// ******************************************************************************
Memory::Memory()
{
    for( int i = 0; i < 100; i++)
    {
        _memMap.push_back(std::make_tuple(i,"."));
    }
    _inMemNum = _memMap.size();
    
    std::vector<std::string> _freePage;
    _freePageNum = _freePage.size();
    
}
Memory:: Memory(std::vector<std::tuple<int, std::string>> memMap, int inMemNum )
{
    for( int i = 0; i < inMemNum; i++)
    {
        _memMap.push_back(std::make_tuple(i,"."));
    }
    _inMemNum = inMemNum;
}



Memory::Memory(std::vector<std::tuple<int, std::string>> memMap, int inMemNum, std::vector<std::tuple<int, std::string>> freePage, int freePageNum )
{
    for(auto it = memMap.begin() ; it != memMap.end(); ++it)
    {
        _memMap.push_back(*it);
    }
    _inMemNum = inMemNum;
    
    for(auto it = freePage.begin() ; it != freePage.end(); ++it)
    {
        _freePage.push_back(*it);
    }
}


// ******************************************************************************
//             GETTER
// ******************************************************************************
int getNumProcess (std::vector<std::tuple<int, std::string>> memMap)
{
    int numProcess = 0;
    std::set<std::tuple<int, std::string>> memMapSet;
    
    for(auto it = memMap.begin() ; it != memMap.end(); ++it)
    {
        memMapSet.insert(*it);
    }
    
    return memMapSet.size();
}


void Memory::printMem()
{
    sort(_memMap.begin(), _memMap.end());
    std::cout << "Memory Map" << std::endl;
    std::cout << "<";
    
    for(auto it = _memMap.begin() ; it != _memMap.end(); ++it)
    {
        std::cout << std::get<1>(*it) << "  " ;
    }
    std::cout << ">";
}






// ******************************************************************************
//             SETTER
// ******************************************************************************
