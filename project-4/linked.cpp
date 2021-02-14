#include <iostream>
#include "linked.hpp"

Page::Page() : pNum(0), pageInMem(0), time(0), inMem(false)
{

}

Page::Page(int pn,int pnm, int t, bool b ) 
	: pNum(pn), pageInMem(pnm), time(t), inMem(b)
{

}
Page::Page(const Page &a) 
	: pNum(a.pNum), pageInMem(a.pageInMem), time(a.time), inMem(a.inMem)
{

}

ExtPage::ExtPage() : Page(), name("")
{
}

ExtPage::ExtPage(Page a): 
	Page(a.getPageNum(), a.getPageInMemory(), a.getTime(), a.isInMem())
{

}
ExtPage::ExtPage(int pn,int pnm, int timestamp, std::string n ) : Page(pn,pnm, timestamp, false), name(n)
{
}

//Makes the Default Job Class
Job::Job()
{
	arrivalTime = 0;
	serviceTime = 0;
	completion =0;
	processName = "None";	
	size = 0;
	stats.waitTime = 0;
	stats.responseTime = 0;
	stats.turnaroundTime = 0;
}

//Makes the Job Class with parameters
//Param: a->arrival, b->service, nam-> name of service
Job::Job(int a, int b, int s, std::string nam = "None")
{
	arrivalTime = a;
	serviceTime = b;
	completion =0;
	size = s;
	processName = nam;
	stats.waitTime = 0;
	stats.responseTime = 0;
	stats.turnaroundTime = 0;
	for(int i = 0; i < s; ++i)
	{
		pages.push_back(Page(i, 0,0, false));
	}
	
}


//deconstructs Job
Job::~Job()
{
}

bool Job::insertPage(int pageNum, int pageInMem, int time)
{
	pages[pageNum].setTime(time);
	insertPageNoCheck(pageNum,pageInMem);
	return true;
}

//check if page inside the process, if not, insert and return true.
//note true if page was inserted, false if not. (Deprecated)
bool Job::insertPage(int pageNum, int pageInMem)
{
	insertPageNoCheck(pageNum,pageInMem);
	return true;
}

//check if page inside the process, if not, insert and return true.
//note true if page was inserted, false if not. (Deprecated)
void Job::insertPageNoCheck(int pageNum, int pageInMem)
{
	pages[pageNum].setInMemory(pageInMem);
	pages[pageNum].setMem(true);
}

//returns a page requested by user 
const Page Job::requestPage(int pn) const
{
	return pages[pn];
}

//returns a page requested by user 
Page Job::requestPage(int pn)
{
	return pages[pn];
}
//removes a Page from mem( please make sure 
int Job::removePage(int pageNum)
{
	pages[pageNum].setMem(false);
	return pages[pageNum].getPageInMemory();
}

//checks to see if page is inside job. if not return false
bool Job::isListed(int pageNum)
{
	return pages[pageNum].isInMem();
}

void Job::advTime()
{
	for(int i = 0; i < size; ++i)
	{
		pages[i].incrementTime();
	}
}

//the comparision function for jobs in sort
bool compareJobs(Job a, Job b)
{
	return a.getArr() < b.getArr();
}

void CustomQueue::generateProcesses()
{
	const int num[4] = {5, 11, 17, 31};
	int serv, size, arr;
	for(int i = 0; i < 150; ++i)
	{
		serv = rand() % 5 + 1;
		arr = rand() % 60;
		size = num[rand()%4];
		processes.push_back(
			Job(arr ,serv ,size , "P" + std::to_string(i)));
	}
	sort(processes.begin(),processes.end(), compareJobs);
	
	//just output change later

	for(int i = 0; i < 100; ++i)
	{
		std::cout<< processes[i].getName() << " "
			<< processes[i].getArr()  << std::endl;
	}
	
}

Job CustomQueue::popProcess()
{
	if(processes.begin() != processes.end())
	{
		return *processes.erase(processes.begin());
	}
	return Job();
		
}


void Job::setPageInMem(int pageNum)
{
    pages.at(pageNum).changeMem();
}

void Job::printProcessPages()
{
    for(auto it = pages.begin(); it != pages.end(); it++)
    {
        std::cout << it->getPageNum() << "  " ;
    }
    std::cout << std::endl;
}


void Job::printProcessPagesBool()
{
    std::cout << std::endl << "Print Pages of Process Bool" << std::endl;
    for(auto it = pages.begin(); it != pages.end(); it++)
    {
        std::cout << it->isInMem() << "  " ;
    }
    std::cout << std::endl;
}









