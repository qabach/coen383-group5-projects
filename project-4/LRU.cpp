#include "LRU.hpp"
#include <cassert>

#define SCALE 100


std::tuple<int,int,int>  LRU(CustomQueue myQueue, bool sim)
{
    
    
    std::cout << std::endl <<"************************* LRU ****************************" << std::endl;
    
    // check memory free page size
    Memory myMem;
    size_t hit = 0, miss = 0;
    myMem = Memory();
    
    int freeMemSize = myMem.getFreeMemNum();
    
    std::vector<Job *> inMem;
    //this is for checking if we actually need to delete mem
    std::vector<Job *> processed;
    std::vector<int> lastAccessed;
    
    std::cout << "freeMemSize: " << freeMemSize << std::endl;
    std::cout << "ProcessSize: " << myQueue.size() << std::endl;
    int count =0;
    //please put in memory until full?
    for(int globalTime = 0; globalTime < 60; ++globalTime)
    {
    	std::cout << "<-----------Second: " << globalTime
    		<< "----------->" << std::endl;
    	//check which processes to delete from memory
    	
    	for(int i =0 ; i< inMem.size(); ++i)
    	{
    		if(inMem[i]->getComp() == inMem[i]->getServ());
    		{	
    			int j = myMem.getFreeMemNum();
    			LRUprintTimeStamp(myMem, inMem[i], globalTime,"exit");
    			myMem.removeProcessFromMem(inMem[i]);
    			assert(myMem.getFreeMemNum() >=j);
    			inMem.erase(inMem.begin() + i);
    			--i;
    		}
    	}
    	
    	//load more processes in from queue
    	while(myMem.getFreeMemNum() >=4 && !myQueue.isEmpty() 
		&& myQueue.front().getArr() <= globalTime)
		{
			Job * process = new Job(myQueue.popProcess());
			assert(process!=nullptr);
			int memLoc = myMem.getFreePage();
			myMem.insertPageToMem(process, 0);
			inMem.push_back(process);
			inMem.back()->insertPage(0,memLoc);
			processed.push_back(process);
			assert(process->isListed(0));
			lastAccessed.push_back(0);
			LRUpushMore(myMem, process);
			//miss+=4;
			LRUprintTimeStamp(myMem, process, globalTime,"enter");
		}
		//this is the 100ms that happens
		for(int i =1 ; i < 10; ++i)
		{
			//go through each job and check wether job is in memory
			for(std::vector<Job *>::iterator k = inMem.begin(); k != inMem.end(); ++k)
			{
				
				if(count > 100 && !sim)
				{
					break;
				}
				++count;
				//on the last second, increment completion time
				if( i == 9)
				{
					(*k)->incrementComp(); 
				}
				if((*k)->getComp() >= (*k)->getServ())
    			{	
    				(*k)->advTime();
    				continue;
    			}
				//for each job find the locality reference
				int pos = k - inMem.begin();
				int freeMemSize = myMem.getFreeMemNum();
				
				lastAccessed[pos] = locality_reference(
					lastAccessed[pos], (*k)->getSize());
				//if its listed, reset timer of last accessed and increment hit
				if((*k)->isListed(lastAccessed[pos])){
					assert(lastAccessed[pos] < (*k)->getSize());
					++hit;
					(*k)->resetTime(lastAccessed[pos]);
					LRUprintTimeStampMS(
						(*k)->getName(),lastAccessed[pos],
						globalTime * SCALE + i,
						(*k)->requestPage(lastAccessed[pos]).getPageInMemory(),"",-1);
						(*k)->advTime();
					continue;
				}
				//if if not and size not free perform LRU
				else if(myMem.getFreeMemNum() <=0)
				{
					pLRU(myMem, processed, *k, lastAccessed[pos],
						globalTime * SCALE + i);
				}
				//just insert page inside memoryMap if something was free
				else
				{
					int memLoc = myMem.getFreePage();
					(*k)->resetTime(lastAccessed[pos]);
					myMem.insertPageToMem(*k, lastAccessed[pos]);
					assert(memLoc == (*k)->requestPage(lastAccessed[pos]).getPageInMemory());
					LRUprintTimeStampMS(
						(*k)->getName(),lastAccessed[pos],
						globalTime * SCALE + i,-1,"",-1);
				}
				(*k)->advTime();
				++miss;
			}
			

		} 
		std::cout << "<-----------End of Second: " << globalTime
    		<< "----------->" <<std::endl;
    	//myMem.printMem();
    	//myMem.printFreePageList();
		if(count > 100 && !sim)
		{
			break;
		}
    }
    LRUprintTimeStamp(myMem, inMem[0], 60,"End");
    std::cout << "Jobs Missed: " << myQueue.size()<< std::endl;
    while(!processed.empty())
    {
    	Job *temp = processed[0];
    	processed[0] = nullptr;
    	delete temp;
    	processed.erase(processed.begin());
    }
    std::cout << "************************"<< std::endl;
    std::cout << "Hit/Miss ratio: " << (double)hit/miss << std::endl;
    return std::make_tuple(150 - myQueue.size(),hit,miss);
}


void pLRU(Memory &m, std::vector<Job *> &jobs, Job * insert, int num, int timestamp)
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
	int memLoc = (*kpos)->requestPage(pos).getPageInMemory();
	m.removePageFromMem(*kpos,pos);
	insert->resetTime(num);
	m.insertPageToMem(insert, num);
	assert(insert->requestPage(num).isInMem());
	LRUprintTimeStampMS(insert->getName(), num,
		timestamp, -1,(*kpos)->getName(),pos);
}

//push the remaining 3 pages into memeory
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
		//std::cout <<num <<std::endl;
		const int memLoc = m.getFreePage();
		process->insertPage(num,memLoc);
		process->resetTime(num);
		m.insertPageToMem(process, num);
		if(process->isListed(num))
    	{
    		assert(process->isListed(num) && memLoc == process->requestPage(num).getPageInMemory()) ;
    	}
	}

}

void LRUprintTimeStamp(Memory &m, Job * process, int timestamp, std::string in)
{
	std::cout << "----------------------------------" <<std::endl;
	std::cout << "Seconds: " << timestamp 
		<< " Name: " << process->getName() 
		<< " Entry: " << in 
		<< " Size: " << process->getSize() 
		<< " Service Time:" << process->getServ() << std::endl;
	m.printMem();	
	std::cout << std::endl
		<< "----------------------------------" <<std::endl;
}

void LRUprintTimeStampMS(std::string cProc, int cPage, int timestamp, int PageInMem, std::string rProc, int Page_TBE)
{
	std::cout << "Seconds: " << timestamp/SCALE << ".";
	std::cout << timestamp % SCALE
		<< " Name: " << cProc
		<< " Page: " << cPage;
		if(PageInMem >= 0)
		{
			std::cout << " Page-in-Memory: " << PageInMem;
		}
		else
		{
			std::cout <<" Page-in-Memory: None";
		} 
		if(rProc != "" && Page_TBE >= 0)
		{
			std::cout << " Proc/Page-TBE: " 
				<< rProc << "/" << Page_TBE << std::endl;
		}
		else
		{
			std::cout << " Proc/Page-TBE: None" <<std::endl;
		} 
}
