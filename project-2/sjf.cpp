#include "sjf.hpp"

void sjf(const List &list)
{
	List sjfList, finishedList;
	int t = 0;
	Node * curNode;
	const Node * pointer = list.getHead();
	const Node * next;
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
				curNode->data.stats.waitTime = curNode->data.getTurn() + curNode->data.getServ();

				//add current job from (sjfList) to (finishedList)
				finishedList.pushDataNS(curNode->data);
				sjfList.deleteHeadNode();
			}
			else
			{
				curNode = NULL;
			}
		}

		t++;
	}
	sjfList.clr();
	std::cout << "This is SJF:" << std::endl;
	finishedList.printListOnlyName();
	finishedList.clr();
}