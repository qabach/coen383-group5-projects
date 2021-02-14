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
    Job process;
    process = Job();
    
    for( int i = 0; i < 100; i++)
    {
        _memMap.push_back(std::make_tuple(i, process));
    }
    _inMemNum = 0;
    
    for( int i = 0; i < 100; i++)
    {
        _freePage.push_back(i);
    }
    
    _freePageNum = 100;
    
}


Memory:: Memory(std::vector<std::tuple<int, Job>> memMap, int inMemNum )
{
    for(auto it = memMap.begin() ; it != memMap.end(); ++it)
    {
        _memMap.push_back(*it);
    }
    _inMemNum = inMemNum;
}



Memory::Memory(std::vector<std::tuple<int, Job>> memMap, int inMemNum, std::vector<int> freePage, int freePageNum )
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
int getNumProcess (std::vector<std::tuple<int, Job>> memMap)
{
    //std::set<std::tuple<int, Job>> memMapSet;
    std::set<std::string> memMapSet;
    
    for(auto it = memMap.begin() ; it != memMap.end(); ++it)
    {
        std::string processName = std::get<1>(*it).getName();
        //std::find(memMap.begin(), memMap.end(), *it);
        
        memMapSet.insert(processName);
    }
    
    return memMapSet.size();
}


void Memory::printMem()
{
    //sort(_memMap.begin(), _memMap.end());

   
    std::cout << "Number of Processes in Memory: " << _inMemNum << std::endl;
    std::cout << "Number of Free Page in Memory: " << _freePageNum << std::endl;
    std::cout << "Memory Map " << std::endl;
    std::cout << "<";

    for(auto it = _memMap.begin() ; it != _memMap.end(); ++it)
    {
        std::cout << std::get<1>(*it).getName() << "  " ;
    }
    std::cout << ">";
}

void Memory::printFreePageList()
{
    std::cout << std::endl << "Free Page List " << std::endl;
    std::cout << "<";

    for(auto it = _freePage.begin() ; it != _freePage.end(); ++it)
    {
        std::cout << *it << "  " ;
    }
    std::cout << ">";
}


int Memory::getFreePage()
{
    return _freePage.front();
}





// ******************************************************************************
//             SETTER
// ******************************************************************************
void Memory::insertPageToMem(Job * process, int pageNum)
{
    auto it = _memMap.begin();
    int memLoc = getFreePage();
    std::cout << "memLoc: " << memLoc << std::endl;
    _memMap.insert(it+memLoc, std::make_tuple(memLoc, *process));
    //_memMap.push_back(std::make_tuple(memLoc, process));
    
    auto it2 = _freePage.begin();
    _freePage.erase(it2);
    
    //std::vector<Page> myPage = process.getPageVec();
    //std::cout << "Page Vector: " << std::endl;
//    for(auto itt = process->getPageVec()->begin(); itt != process->getPageVec()->end(); itt++)
//    {
//        itt->changeMem();
//        std::cout << itt->isInMem() << " ";
//    }
    
    //process.getPageVec().at(pageNum).changeMem();
    
    auto itt = process->getPageVec()->begin();
    itt->changeMem();
    //std::cout << itt->isInMem() << " ";
    _memMap.insert(it+memLoc, std::make_tuple(memLoc, *process));
    
}


void Memory::removePageFromMem(Job process, int pageNum)
{
    
}




