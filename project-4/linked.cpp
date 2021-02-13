#include <iostream>
#include "linked.hpp"

Page::Page() : pNum(0), pageInMem(0)
{

}

Page::Page(int pn,int pnm ) 
	: pNum(pn), pageInMem(pnm)
{

}

ExtPage::ExtPage() : Page(), name(""), time(0)
{
}

ExtPage::ExtPage(Page a): Page(a.getPageNum(), a.getPageInMemory())
{

}
ExtPage::ExtPage(int pn,int pnm, int timestamp, std::string n ) : Page(pn,pnm), time(timestamp), name(n)
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
	
}

//deconstructs Job
Job::~Job()
{
	for(std::vector<Page *>::iterator it = pages.begin();
	it != pages.end(); ++it)
	{
		if(*it!= nullptr)
		{
			free(*it);
		}
	}
}
//check if page inside the process, if not, insert and return true.
//note true if page was inserted, false if not.
bool Job::insertPage(int pageNum, int pageInMem)
{
	for(std::vector<Page *>::iterator it = pages.begin();
	it != pages.end(); ++it)
	{
		if((*it)->getPageNum() == pageNum)
		{
			return false;
		}
	}
	pages.push_back(new Page(pageNum, pageInMem));
	return true;
}

//just put in the page without checking anything 
void Job::insertPageNoCheck(int pageNum, int pageInMem)
{
	pages.push_back(new Page(pageNum, pageInMem));
}

//returns a page requested by user
const Page * Job::requestPage(int pn) const
{
	for(std::vector<Page *>::const_iterator it = pages.cbegin();
	it != pages.cend(); ++it)
	{
		if((*it)->getPageNum() == pn)
		{
			return *it;
		}
	}
	return NULL;
}
//removes a Page
void Job::removePage(int pageNum)
{
	for(std::vector<Page *>::iterator it = pages.begin();
	it != pages.end(); ++it)
	{
		if((*it)->getPageNum() == pageNum)
		{
			if(*it!= nullptr)
			{
				free(*it);
			}
			pages.erase(it);
			return;
		}
	}
}

//checks to see if page is inside job. if not return false
bool Job::isListed(int pageNum)
{
	for(std::vector<Page *>::iterator it = pages.begin();
	it != pages.end(); ++it)
	{
		if((*it)->getPageNum() == pageNum)
		{
			return true;
		}
	}
	return false;
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









