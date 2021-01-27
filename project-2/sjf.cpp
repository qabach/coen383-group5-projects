#include <iostream>
#include "sjf.hpp"

overStat sjf(const List &list)
{
	std::cout << std::endl << "******************** start SJF ********************" << std::endl;
	
	List sjfList, finishedList;
	int t = 0;
	Node * curNode = NULL;
	const Node * pointer = list.getHead();
	const Node * next;

	int numProcessedJobs = 0;
    double totalResponseTime = 0;
    double totalWaitTime = 0;
    double totalTurnaroundTime = 0;

	while(t < 100)
	{	
		//1. move arrived Nodes from (list) to (sjfList)

		while(pointer != NULL && pointer->data.getArr() <= t)
		{
			next = pointer->getNext();
			sjfList.insertSjf(pointer->data);
			pointer = next;
		}

		//2. check if current job finished.
		//if there is no job or current job finished,
		//then let the head of (sjfList) to be the current job

		if(curNode == NULL || curNode->data.getArr() + curNode->data.getRes() + curNode->data.getServ() <= t)
		{
			if(sjfList.getHead() != NULL)
			{
				curNode = sjfList.getHead();
				sjfList.deleteHeadNode();

				//calculate job stats
				curNode->data.stats.turnaroundTime = t + curNode->data.getServ() - curNode->data.getArr();
				curNode->data.stats.responseTime = t - curNode->data.getArr();
				curNode->data.stats.waitTime = curNode->data.getTurn() - curNode->data.getServ();

				//calculate total stats
				totalTurnaroundTime += curNode->data.stats.turnaroundTime;
				totalResponseTime += curNode->data.stats.responseTime;
				totalWaitTime += curNode->data.stats.waitTime;
				numProcessedJobs++;

				//add current job from (sjfList) to (finishedList)
				finishedList.pushDataNS(curNode->data);
				sjfList.deleteHeadNode();
			}
			else
			{
				curNode = NULL;
			}
		}

		if(curNode == NULL) t++;
		else t += curNode->data.serviceTime;
	}
	sjfList.clr();

	printAlgoStats(totalResponseTime, totalTurnaroundTime, totalWaitTime, numProcessedJobs);
    printTimeChart(finishedList);
    overStat overallStats = retStat(totalResponseTime, totalTurnaroundTime, totalWaitTime, numProcessedJobs);
    
	finishedList.clr();

	std::cout << std::endl << "******************** end SJF ********************" << std::endl;

	return overallStats;
}