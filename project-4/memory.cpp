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
    Job * process;
    process = new Job();
    
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


Memory:: Memory(std::vector<std::tuple<int, Job *>> memMap, int inMemNum )
{
    for(auto it = memMap.begin() ; it != memMap.end(); ++it)
    {
        _memMap.push_back(*it);
    }
    _inMemNum = inMemNum;
}



Memory::Memory(std::vector<std::tuple<int, Job *>> memMap, int inMemNum, std::vector<int> freePage, int freePageNum )
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
    std::cout << "< ";

    for(auto it = _memMap.begin() ; it != _memMap.end(); ++it)
    {
        std::cout << std::get<1>(*it)->getName() << "  " ;
    }
    std::cout << ">";
}

void Memory::printFreePageList()
{
    std::cout << std::endl << "Free Page List " << std::endl;
    std::cout << "< ";

    for(auto it = _freePage.begin() ; it != _freePage.end(); ++it)
    {
        std::cout << *it << "  " ;
    }
    std::cout << ">";
}


int Memory::getFreePage()
{
    if(_freePage.size() > 1)
    {
        return _freePage.front();
    }
    else
    {
        return -1;      // -1 means no freePage
    }
}





// ******************************************************************************
//             SETTER
// ******************************************************************************
void Memory::insertPageToMem(Job * process, int pageNum)
{
    auto it = _memMap.begin();
    int memLoc = getFreePage();
    std::cout << "memLoc: " << memLoc << std::endl;
    _memMap.erase(it+memLoc);
    _memMap.insert(it+memLoc, std::make_tuple(memLoc, process));
    _inMemNum++;
    //_memMap.push_back(std::make_tuple(memLoc, process));
    
    auto it2 = _freePage.begin();
    _freePage.erase(it2);
    _freePageNum--;
    
    //std::vector<Page> myPage = process.getPageVec();
    //std::cout << "Page Vector: " << std::endl;
//    for(auto itt = process->getPageVec()->begin(); itt != process->getPageVec()->end(); itt++)
//    {
//        itt->changeMem();
//        std::cout << itt->isInMem() << " ";
//    }
    //process.getPageVec().at(pageNum).changeMem();
    
    auto itt = process->getPageVec()->begin();
    (itt+pageNum)->changeMem();
    (itt+pageNum)->setInMemory(memLoc);
    //std::cout << itt->isInMem() << " ";
}


void Memory::removePageFromMem(Job * process, int pageNum)
{
    
    
    int memLoc = process->getPageVec()->at(pageNum).getPageInMemory();
    std::cout << "memLoc: " << memLoc << std::endl;
    
    auto it2 = process->getPageVec()->begin();
    (it2 + pageNum)->changeMem();
    (it2 + pageNum)->setInMemory(-1);         // -1 means not in memory
    
    auto it = _memMap.begin();
    _memMap.erase(it+memLoc);               // erase process page out of mem
    
    Job * noneProcess;
    noneProcess = new Job();
    _memMap.push_back(std::make_tuple(memLoc, noneProcess));        // push a None process to the memMap
    _inMemNum--;
    
   
    _freePage.push_back(memLoc);
    
    _freePageNum++;
    
}




