//
//  MFU.cpp
//  Project_4
//
//  Created by YujobIteratorun on 2/13/21
//

#include "MFU.hpp"
#include <cassert>

#define SCALE 1000

size_t MFU(CustomQueue queue, double &rate)
{
	std::cout << std::endl <<"************************* MFU ****************************" << std::endl;
    
	//define
    Memory memory = Memory();
    size_t hit = 0, miss = 0;
    std::vector<Job *> inMemoryJobList;
    std::vector<Job *> processedJobList;
    std::vector<int> lastAccessedJobNumberList;
    
	//print
	int freeMemorySize = memory.getFreeMemNum();
    std::cout << "freeMemorySize: " << freeMemorySize << std::endl;
    std::cout << "ProcessSize: " << queue.size() << std::endl;
 
    for(int globalTime = 0; globalTime < 60; ++globalTime)
    {
    	std::cout << "<-----------Second: " << globalTime << "----------->" << std::endl;

    	//check which processes to delete from memory
    	for(int i =0 ; i< inMemoryJobList.size(); ++i)
    	{	
			//if completion == service time
    		if(inMemoryJobList[i]->getComp() == inMemoryJobList[i]->getServ())
    		{	
				//print
    			MFUprintTimeStamp(memory, inMemoryJobList[i], globalTime, "exit");

				//remove job from memory
    			memory.removeProcessFromMem(inMemoryJobList[i]);

    			//remove job from inMemoryJobList
    			inMemoryJobList.erase(inMemoryJobList.begin() + i);
    			--i;

    			continue;
    		}
    	}

    	//load more jobs from queue
    	while(memory.getFreeMemNum() >=4 && !queue.isEmpty() && queue.front().getArr() < globalTime)
		{
			//pop job from queue
			Job * job = new Job(queue.popProcess());
			assert(job != nullptr);

			//insert job to memory
			int memoryLocation = memory.getFreePage();
			memory.insertPageToMem(job, 0);

			//insert job to every list
			inMemoryJobList.push_back(job);
			processedJobList.push_back(job);
			lastAccessedJobNumberList.push_back(0);

			//insert page No.0 to job
			inMemoryJobList.back()->insertPage(0, memoryLocation);
			
			//MFUpushMore(memory, job);

			//print
			MFUprintTimeStamp(memory, job, globalTime, "enter");
		}

		//this is the 100ms that happens
		for(int i = 0; i < 10; ++i)
		{
			//go through each job and check whather job is in memory
			for(std::vector<Job *>::iterator jobIterator = inMemoryJobList.begin(); jobIterator != inMemoryJobList.end(); ++jobIterator)
			{
				//increment job time
				(*jobIterator)->incrementComp(); 
				
				//find the locality reference
				int position = jobIterator - inMemoryJobList.begin();
				int freeMemorySize = memory.getFreeMemNum();
				lastAccessedJobNumberList[position] = locality_reference(lastAccessedJobNumberList[position], (*jobIterator)->size);

				//Choice 1: if page number is exist in job
				if((*jobIterator)->isListed(lastAccessedJobNumberList[position])){
					assert(lastAccessedJobNumberList[position] < (*jobIterator)->getSize());

					//choice 1 will increment hit
					++hit;

					//reset time of the chosen page
					(*jobIterator)->resetTime(lastAccessedJobNumberList[position]);

					//increment hit count of page	
					(*jobIterator)->getPage(lastAccessedJobNumberList[position]).incrementHitCount();			

					//print
					MFUprintTimeStampMS(
						(*jobIterator)->getName(),
						lastAccessedJobNumberList[position],
						globalTime * SCALE + i,
						(*jobIterator)->getPage(lastAccessedJobNumberList[position]).getPageInMemory(),
						"",
						-1);

					continue;
				}

				//Choice 2: if no free page, then perform MFU
				else if(memory.getFreeMemNum() <= 0)
				{
					//find the page with most hit count
					std::vector<Page> pageList = (*jobIterator)->getPageList();
					int maxHitCount = 0;
					int pagePosition = 0;
					std::vector<Page>::iterator pageIterator;
					for(pageIterator = pageList.begin(); pageIterator != pageList.end(); ++pageIterator)
					{
						if((*pageIterator).getHitCount() > maxHitCount)
						{
							maxHitCount = (*pageIterator).getHitCount();
							pagePosition = pageIterator - pageList.begin();
						}
					}

					//remove page from old place by setting setInMemory = -1
					(*jobIterator)->getPage(pagePosition).setInMemory(-1);

					//insert page to to new place in job
					int pageMemoryLocation = (*jobIterator)->getPage(pagePosition).getPageInMemory();
					(*jobIterator)->insertPage(lastAccessedJobNumberList[position], pageMemoryLocation);
					(*jobIterator)->resetTime(lastAccessedJobNumberList[position]);
				}

				//Choice 3: insert page inside memory if there are some free pages
				else
				{
					//1. insert page to job
					int memoryLocation = memory.getFreePage();
					(*jobIterator)->insertPage(lastAccessedJobNumberList[position], memoryLocation);
					(*jobIterator)->resetTime(lastAccessedJobNumberList[position]);

					//2. insert page to memory
					memory.insertPageToMem(*jobIterator, lastAccessedJobNumberList[position]);

					//3. increment hit count of page
					(*jobIterator)->getPage(lastAccessedJobNumberList[position]).incrementHitCount();

					//print time stamp
					MFUprintTimeStampMS(
						(*jobIterator)->getName(),
						lastAccessedJobNumberList[position],
						globalTime * SCALE + i,
						-1,
						"",
						-1);
				}
				
				//increment time of every page in job
				(*jobIterator)->advTime();

				//Choice 2 and 3 will increment miss
				++miss;
			}
			

		} 
		std::cout << "<-----------End of Second: " << globalTime << "----------->" <<std::endl;
    }

    std::cout << "Jobs Missed: " << queue.size()<< std::endl;

	//remove rest of processing jobs in processedJobList
    while(!processedJobList.empty())
    {
    	Job *temp = processedJobList[0];
    	processedJobList[0] = nullptr;
    	delete temp;
    	processedJobList.erase(processedJobList.begin());
    }

    std::cout << "************************"<< std::endl;
    std::cout << "Hit/Miss ratio: " << (double)hit/miss << std::endl;

	//calculate rate
    rate = (double)hit/miss;

    return 150 - queue.size();
}

// void pMFU(Memory &memory, std::vector<Job *> &jobs, Job * insert, int num, int timestamp)
// {
// 	int time = -1;
// 	std::vector<Job *>::iterator job;
// 	int position;

// 	//check every job.
// 	for(std::vector<Job *>::iterator jobIterator = jobs.begin(); jobIterator != jobs.end(); ++jobIterator)
// 	{
// 		for(int i = 0; i < (*jobIterator)->getSize(); ++i)
// 		{
// 			if((*jobIterator)->isListed(i) && (*jobIterator)->returnTime(i) > time)
// 			{
// 				jobIteratorposition = jobIterator;
// 				position = i;
// 			}
			
// 		}
// 	}

// 	int memoryLocation = (*jobIteratorposition)->removePage(position);
// 	memory.removePageFromMem(*jobIteratorposition,position);
//     insert->insertPage(num,memoryLocation);
// 	insert->resetTime(num);
// 	memory.insertPageToMem(insert, num);
// 	MFUprintTimeStampMS(insert->getName(), 
// 						num, 
// 						timestamp, 
// 						-1,
// 						(*jobIteratorposition)->getName(),
// 						position);
// }

//push the remaining 3 pages into memeory randomly
void MFUpushMore(Memory &m, Job * process)
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
		int memoryLocation = m.getFreePage();
		process->insertPage(num,memoryLocation);
		process->resetTime(num);
		m.insertPageToMem(process, num);
	}

}

void MFUprintTimeStamp(Memory &m, Job * process, int timestamp, std::string in)
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

void MFUprintTimeStampMS(std::string cProc, int cPage, int timestamp, int PageInMem, std::string rProc, int Page_TBE)
{
	std::cout << "Seconds: " << timestamp/SCALE << ".";
	if(timestamp % SCALE < 10)
	{
		std::cout << "0";
	}
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


// void pMFU(Memory &m, std::vector<Job> &jobs, int &insertLoc, int num);

// void MFU(CustomQueue queue) {
// 	std::cout << std::endl <<"************************* MFU ****************************" << std::endl;
    
//     Memory memory = Memory();
//     size_t hit = 0, miss = 0;
    
//     int freeMemorySize = memory.getFreeMemNum();
// 	std::cout << "freeMemorySize: " << freeMemorySize << std::endl;
    
//     std::vector<Job> inMemoryJobList;
//     std::vector<int> lastAccessedJobNumberListJobList;
    
// 	// if (freeMemorySize >= 4){
// 	// 	Job job = queue.popProcess();

// 	// 	int memoryLocation = memory.getFreePage();
// 	// 	std::cout << "memoryLocation: " << memoryLocation << std::endl;

// 	// 	memory.insertPageToMem(job, memoryLocation);
// 	// 	inMemoryJobList.push_bacjobIterator(job);
// 	// 	inMemoryJobList.bacjobIterator().insertPage(0, memoryLocation);
// 	// 	lastAccessedJobNumberList.push_bacjobIterator(0);

// 	// 	++miss;
		    
// 	// }

	
// 	std::vector<Job>::iterator arrivedJobIterator = queue.processes.begin();
// 	std::deque<Job> arrivedJobList;

//     for(float globalTime = 0; globalTime < 60; globalTime = globalTime + 0.1) {

// 		while(arrivedJobIterator != queue.processes.end() && (*arrivedJobIterator).arrivelTime <= globalTime) {
// 			arrivedJobList.push_bacjobIterator(*arrivedJobIterator);
// 			arrivedJobIterator++;
// 		}

// 		if(memory.getFreeMemNum() >= 4 && !arrivedJobList.empty()) {
// 			Job job = arrivedJobList.pop_front();
// 			int memoryLocation = memory.getFreePage();
// 			memory.insertPageToMem(job, memoryLocation);
// 			inMemoryJobList.push_bacjobIterator(job);
// 			inMemoryJobList.bacjobIterator().insertPage(0, memoryLocation);
// 			lastAccessedJobNumberListJobList.push_bacjobIterator(0);
// 		}

// 		for(std::vector<Job>::iterator jobIterator = inMemoryJobList.begin(); jobIterator != inMemoryJobList.end(); ++jobIterator)
// 			{
// 				//for each job find the locality reference
// 				int positionition = jobIterator - inMemoryJobList.begin();
// 				int freeMemorySize = memory.getFreeMemNum();
// 				// lastAccessedJobNumberListJobList[positionition] = locality_reference(lastAccessedJobNumberListJobList[positionition], jobIterator->size);
// 				int nextPageNumber = locality_reference(lastAccessedJobNumberListJobList[positionition], freeMemorySize);

// 				//if its listed reset timer of last accessed
// 				if(jobIterator->isListed(position)) {
// 					++hit;
// 					// jobIterator->resetTime(position);
// 					continue;
// 				}
// 				//if if not and size not free perform LRU
// 				else if(freeMemorySize <= 0) {
// 					pMFU(memory, inMemoryJobList, positionition, nextPageNumber);
// 				}
// 				//just insert page inside memoryMap if found something free
// 				else
// 				{
// 					int memoryLocation = memory.getFreePage(memory);
// 					std::cout << "memoryLocation: " << memoryLocation << std::endl;
// 					memory.insertPageToMem(*jobIterator, lastAccessedJobNumberList[position], memoryLocation);
// 					inMemoryJobList[position].insertPage(lastAccessedJobNumberList[position],memoryLocation);
					
// 				}
// 				jobIterator->advTime();
// 				++miss;
// 			}
			

// 		} 
//     	memory.printMem();
//     	memory.printFreePageList();
//     }
// }


// void pMFU(Memory &m, std::vector<Job> &jobs, int &insert, int num)
// {
// 	int time = -1;
// 	std::vector<Job>::iterator jobIteratorposition;
// 	int position;
// 	//checjobIterator every job.
// 	for(std::vector<Job>::iterator jobIterator = jobs.begin(); jobIterator != jobs.end(); ++jobIterator)
// 	{
// 		for(int i =0; i < jobIterator->getSize(); ++i)
// 		{
// 			if(jobIterator->isListed(i) && jobIterator->returnTime(i) > time)
// 			{
// 				jobIteratorposition = jobIterator;
// 				position = i;
// 			}
			
// 		}
// 	}
// 	int memoryLocation = jobIteratorposition->removePage(position);
//     std::cout << "memoryLocation: " << memoryLocation << std::endl;
// 	m.insertPageToMem(jobs[insert], num, memoryLocation);
// 	jobs[insert].insertPage(num,memoryLocation);


// }
