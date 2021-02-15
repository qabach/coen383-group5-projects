//
//  FIFO.cpp
//  Project_4_AT
//
//  Created by Anh Tuk on 2/13/21.
//

#include "LRU.hpp"
#include <cassert>

void pLRU(Memory &m, std::vector<Job *> &jobs, int &insertLoc, int num);
void LRUpushMore(Memory &m, Job * process);

void LRU(CustomQueue myQueue)
{
//    CustomQueue myQueue;
//    queue.
    
    
    std::cout << std::endl <<"************************* LRU ****************************" << std::endl;
    
    // check memory free page size
    Memory myMem;
    size_t hit = 0, miss = 0;
    myMem = Memory();
    
    int freeMemSize = myMem.getFreeMemNum();
    
    std::vector<Job *> inMem;
    std::vector<int> lastAccessed;
    
    std::cout << "freeMemSize: " << freeMemSize << std::endl;
    //please put in memory until full?
    /*
	while(myMem.getFreeMemNum() >=95 && !myQueue.isEmpty() 
		&& myQueue.front().getArr() < globalTime)
	{
		Job * process = new Job(myQueue.popProcess());
		int memLoc = myMem.getFreePage();
		myMem.insertPageToMem(process, 0);
		inMem.push_back(process);
		inMem.back()->insertPage(0,memLoc);
		lastAccessed.push_back(0);
		LRUpushMore(myMem, process);
		miss+=4;
		    
	}
	*/
    for(int globalTime = 0; globalTime < 60; ++globalTime)
    {
    	while(myMem.getFreeMemNum() >=4 && !myQueue.isEmpty() 
		&& myQueue.front().getArr() < globalTime)
		{
			Job * process = new Job(myQueue.popProcess());
			assert(process!=nullptr);
			int memLoc = myMem.getFreePage();
			myMem.insertPageToMem(process, 0);
			inMem.push_back(process);
			inMem.back()->insertPage(0,memLoc);
			lastAccessed.push_back(0);
			LRUpushMore(myMem, process);
			miss+=4;	
		}
		//the 10ms that happens
		for(int i =0 ; i < 10; ++i)
		{
			for(std::vector<Job *>::iterator k = inMem.begin(); k != inMem.end(); ++k)
			{
				//for each job find the locality reference
				int pos = k - inMem.begin();
				int freeMemSize = myMem.getFreeMemNum();
				lastAccessed[pos] = locality_reference(
					lastAccessed[pos], (*k)->size);
				//std::cout << lastAccessed[pos] << " " 
					//<<(*k)->size<<std::endl;
				//if its listed reset timer of last accessed
				if((*k)->isListed(lastAccessed[pos])){
					assert(lastAccessed[pos] < (*k)->getSize());
					++hit;
					(*k)->resetTime(lastAccessed[pos]);
					continue;
				}
				//if if not and size not free perform LRU
				else if(myMem.getFreeMemNum() <=0)
				{
					pLRU(myMem, inMem, pos, lastAccessed[pos]);
				}
				//just insert page inside memoryMap if found something free
				else
				{
					int memLoc = myMem.getFreePage();
					//std::cout << "memLocb: " << memLoc << std::endl;
					(*k)->insertPage(lastAccessed[pos],memLoc);
					(*k)->resetTime(lastAccessed[pos]);
					myMem.insertPageToMem(*k, lastAccessed[pos]);
					
				}
				(*k)->advTime();
				++miss;
			}
			

		} 
    	myMem.printMem();
    	myMem.printFreePageList();
    }
    while(!inMem.empty())
    {
    	Job *temp = inMem[0];
    	inMem[0] = nullptr;
    	delete temp;
    	inMem.erase(inMem.begin());
    }
}


void pLRU(Memory &m, std::vector<Job *> &jobs, int &insert, int num)
{
	int time = -1;
	std::vector<Job *>::iterator kpos;
	int pos;
	//check every job.
	for(std::vector<Job *>::iterator k = jobs.begin(); k != jobs.end(); ++k)
	{
		for(int i =0; i < (*k)->getSize(); ++i)
		{
			if((*k)->isListed(i) && (*k)->returnTime(i) > time)
			{
				kpos = k;
				pos = i;
			}
			
		}
	}
	//std::cout << pos << "a" <<std::endl;
	int memLoc = (*kpos)->removePage(pos);
	//std::cout << pos <<std::endl;
	m.removePageFromMem(*kpos,pos);
    //std::cout << "memLoct: " << pos << std::endl;
    jobs[insert]->insertPage(num,memLoc);
	jobs[insert]->resetTime(num);
	m.insertPageToMem(jobs[insert], num);
}

void LRUpushMore(Memory &m, Job * process)
{
	std::set<int> s;
	int num =0;
	s.insert(0);
	for(int i =0; i < 3; ++i)
	{
		while(s.find(num) != s.end())
		{
			num = rand() % (process->getSize());
		}
		assert(num < process->getSize());
		s.insert(num);
		int memLoc = m.getFreePage();
		process->insertPage(num,memLoc);
		process->resetTime(num);
		m.insertPageToMem(process, num);
	}

}
