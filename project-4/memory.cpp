//
//  memory.cpp
//  Project_4_AT
//
//  Created by Anh Tuk on 2/12/21.
//

#include "memory.hpp"
#include <cassert>


// ******************************************************************************
//              CONSTRUCTOR
// ******************************************************************************
Memory::Memory()
{
    Job * process;
    //process = new Job();
    
    for( int i = 0; i < 100; i++)
    {
        _memMap.push_back(std::make_tuple(i, nullptr));
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
        _freePage.push_back(it-freePage.begin());
    }
}


// ******************************************************************************
//             GETTER
// ******************************************************************************
int getNumProcess (std::vector<std::tuple<int, Job*>> memMap)
{
    //std::set<std::tuple<int, Job>> memMapSet;
    std::set<std::string> memMapSet;
    
    for(auto it = memMap.begin() ; it != memMap.end(); ++it)
    {
    	auto temp = std::get<1>(*it);
    	std::string processName;
    	if(temp != nullptr)
    	{
        	processName = std::get<1>(*it)->getName();
        	memMapSet.insert(processName);
        }
        //std::find(memMap.begin(), memMap.end(), *it);
        
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
    	auto temp = std::get<1>(*it);
    	if(temp != nullptr)
    	{
        	std::cout << temp->getName() << " ";
        }
        else
        {
        	std::cout << ". ";
        }
    }
    std::cout << ">";
}

void Memory::printFreePageList()
{
    std::cout << std::endl << "Free Page List " << std::endl;
    std::cout << "< ";

    for(std::vector<int>::iterator it = _freePage.begin() ; it != _freePage.end(); ++it)
    {
        std::cout << *it << "  " ;
    }
    std::cout << ">";
}


int Memory::getFreePage()
{
    if(_freePage.size() >= 1)
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
	assert(_memMap.size() <=100);
    auto it = _memMap.begin();
    int memLoc = getFreePage();
    //std::cout << "memLocm: " << memLoc << std::endl;
    _memMap.erase(it+memLoc);
    assert(memLoc >= 0 && memLoc <=99);
    if(memLoc ==0)
    {
    	it = _memMap.begin();
    }
    if(memLoc == _memMap.size())
    {
    	_memMap.push_back(std::make_tuple(memLoc, process));
    }
    else
    {
    	_memMap.insert(it+memLoc, std::make_tuple(memLoc, process));
    }
    process->insertPage(pageNum,memLoc);
    _inMemNum++;
    //_memMap.push_back(std::make_tuple(memLoc, process));
    
    auto it2 = _freePage.begin();
    _freePage.erase(_freePage.begin());
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
    (itt+pageNum)->setMem(true);
    (itt+pageNum)->setInMemory(memLoc);
    //std::cout << itt->isInMem() << " ";
}


void Memory::removePageFromMem(Job * process, int pageNum)
{
    
    int memLoc = process->getPageVec()->at(pageNum).getPageInMemory();
    process->removePage(pageNum);
    //std::cout << "memLocd: " << memLoc << std::endl;
    assert(memLoc>=0 && memLoc <= 99);
    auto itt = process->getPageVec()->begin();
    (itt+pageNum)->setMem(false);
    (itt+pageNum)->setInMemory(-1);
    
    auto it = _memMap.begin();
    _memMap.erase(it+memLoc);               // erase process page out of mem
    
    Job * noneProcess;
    noneProcess = nullptr;
    if(memLoc > _memMap.size())
    {
    	_memMap.push_back(std::make_tuple(memLoc, noneProcess));
    }
    else
    {
    	_memMap.insert(it+memLoc, std::make_tuple(memLoc, noneProcess));
    }
    // push a None process to the memMap
    _inMemNum--;
    
   
    _freePage.push_back(memLoc);
    
    _freePageNum++;
    
    //_memMap.erase(it+memLoc);

}

void Memory::removeProcessFromMem(Job * process)
{
    for(auto i = 0 ; i != _memMap.size(); ++i)
    {
    	auto temp = std::get<1>(_memMap[i]);
    	if(temp == process)
    	{
    		_memMap.erase(_memMap.begin() + i); 
    		Job * noneProcess;
			noneProcess = nullptr;
			if(i > _memMap.size())
			{
				_memMap.push_back(std::make_tuple(i, noneProcess));
			}
			else
			{
				_memMap.insert(_memMap.begin()+i, std::make_tuple(i, noneProcess));
			}
			_inMemNum--;
    
   
    		_freePage.push_back(i);
    
    		_freePageNum++;
		}
	}
	auto a = process->getPageVec();
	for(auto it = a->begin(); it != a->end() ; ++it)
	{
		(it)->setMem(false);
    	(it)->setInMemory(-1);
	}
   
}




