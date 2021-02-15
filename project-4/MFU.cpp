//
//  MFU.cpp
//  Project_4
//
//  Created by Yukun on 2/13/21
//

#include "MFU.hpp"

void pMFU(Memory &m, std::vector<Job> &jobs, int &insertLoc, int num);

void MFU(CustomQueue queue) {
	std::cout << std::endl <<"************************* MFU ****************************" << std::endl;
    
    Memory memory = Memory();
    size_t hit = 0, miss = 0;
    
    int freeMemorySize = memory.getFreeMemNum();
	std::cout << "freeMemorySize: " << freeMemorySize << std::endl;
    
    std::vector<Job> inMemoryJobList;
    std::vector<int> lastAccessedJobList;
    
	// if (freeMemorySize >= 4){
	// 	Job job = queue.popProcess();

	// 	int memoryLocation = memory.getFreePage();
	// 	std::cout << "memoryLocation: " << memoryLocation << std::endl;

	// 	memory.insertPageToMem(job, memoryLocation);
	// 	inMemoryJobList.push_back(job);
	// 	inMemoryJobList.back().insertPage(0, memoryLocation);
	// 	lastAccessed.push_back(0);

	// 	++miss;
		    
	// }

	
	std::vector<Job>::iterator arrivedJobIterator = queue.processes.begin();
	std::deque<Job> arrivedJobList;

    for(float globalTime = 0; globalTime < 60; globalTime = globalTime + 0.1) {

		while(arrivedJobIterator != queue.processes.end() && (*arrivedJobIterator).arrivelTime <= globalTime) {
			arrivedJobList.push_back(*arrivedJobIterator);
			arrivedJobIterator++;
		}

		if(memory.getFreeMemNum() >= 4 && !arrivedJobList.empty()) {
			Job job = arrivedJobList.pop_front();
			int memoryLocation = memory.getFreePage();
			memory.insertPageToMem(job, memoryLocation);
			inMemoryJobList.push_back(job);
			inMemoryJobList.back().insertPage(0, memoryLocation);
			lastAccessedJobList.push_back(0);
		}

		for(std::vector<Job>::iterator jobIterator = inMemoryJobList.begin(); jobIterator != inMemoryJobList.end(); ++jobIterator)
			{
				//for each job find the locality reference
				int position = jobIterator - inMemoryJobList.begin();
				int freeMemSize = memory.getFreeMemNum();
				// lastAccessedJobList[position] = locality_reference(lastAccessedJobList[position], k->size);
				int nextPageNumber = locality_reference(lastAccessedJobList[position], freeMemSize);

				//if its listed reset timer of last accessed
				if(k->isListed(pos)) {
					++hit;
					// k->resetTime(pos);
					continue;
				}
				//if if not and size not free perform LRU
				else if(freeMemSize <= 0) {
					pMFU(memory, inMemoryJobList, position, nextPageNumber);
				}
				//just insert page inside memoryMap if found something free
				else
				{
					int memLoc = myMem.getFreePage(myMem);
					std::cout << "memLoc: " << memLoc << std::endl;
					myMem.insertPageToMem(*k, lastAccessed[pos], memLoc);
					inMem[pos].insertPage(lastAccessed[pos],memLoc);
					
				}
				k->advTime();
				++miss;
			}
			

		} 
    	myMem.printMem();
    	myMem.printFreePageList();
    }
}


void pMFU(Memory &m, std::vector<Job> &jobs, int &insert, int num)
{
	int time = -1;
	std::vector<Job>::iterator kpos;
	int pos;
	//check every job.
	for(std::vector<Job>::iterator k = jobs.begin(); k != jobs.end(); ++k)
	{
		for(int i =0; i < k->getSize(); ++i)
		{
			if(k->isListed(i) && k->returnTime(i) > time)
			{
				kpos = k;
				pos = i;
			}
			
		}
	}
	int memLoc = kpos->removePage(pos);
    std::cout << "memLoc: " << memLoc << std::endl;
	m.insertPageToMem(jobs[insert], num, memLoc);
	jobs[insert].insertPage(num,memLoc);


}
