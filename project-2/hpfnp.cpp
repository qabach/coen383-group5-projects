#include "hpfnp.hpp"
#include "stats.hpp"


//does highest prioirty first, (FCFS for each prioirty)
//store stats in stats
//not that thins stored in vector should be q1,q2,q3,q4,total in that order.
void hpfnp(const List &a, std::vector<struct overStat> &stats)
{
	List p1, p2, p3, p4, finished;
	int t;
	const Node * ref;
	stats.clear();
	//get the first element in the queue
	ref = a.getHead();
	t = ref->data.getArr();
	//fill all the prioirty queus first
	ref = fillQueues(ref,p1,p2,p3,p4,t);
		//print out all the finished jobs
	std::cout << "******************** HPFNP ********************" 
		<< std::endl;
	std::cout << "******************** Jobs ********************" 			<< std::endl;
	a.printList();
	//when time is not greater than 100 quatumn
	while(t < 100)
	{
		//check all the prioirty queues first if they are empty. If all are empty. Increment time by 1.
		if(p1.length() != 0)
		{
			performJob(p1,finished,t);
		}
		else if(p2.length() != 0)
		{
			performJob(p2,finished,t);
		}
		else if(p3.length() != 0)
		{
			performJob(p3,finished,t);
		}
		else if(p4.length() != 0)
		{
			performJob(p4,finished,t);
		}
		else
		{
			++t;
		}
		//fill all the queues up to that time
		ref = fillQueues(ref,p1,p2,p3,p4,t);
		
	}
	//make sure to clear everything first
	p1.clr();
	p2.clr();
	p3.clr();
	p4.clr();
	//print out the stats
	computeStats(finished, stats);
	//std::cout << "yay" <<std::endl;
	finished.clr();
}
//run a paritcular job given the queue and completion queue.
//returns time taken
void performJob(List &a, List &c, int &t)
{
	Node * temp = a.getHead();
	Job jtemp(temp->data);
	//calulates all the time for a node
	jtemp.stats.turnaroundTime = (t + jtemp.getServ()) - jtemp.getArr();
	jtemp.stats.responseTime = t - jtemp.getArr();
	jtemp.stats.waitTime = jtemp.stats.turnaroundTime - jtemp.getServ();
	//push onto the finished queue and delete from current queue to indicate doneness. also increment the time up to service time.
	c.pushDataNS(jtemp);
	t += jtemp.getServ();
	a.deleteHeadNode();
	
	//std::cout << "yay" <<std::endl;
	return;
}

//Fills all the queues with jobs up to a time t period.
//returns the node that is greater than time.
const Node * fillQueues(const Node* ref,List &a1,List &a2,List &a3,List &a4, int t)
{
	//go until you reach the end or time happens to be up
	while(ref != nullptr && ref->data.getArr() <= t )
	{
		switch(ref->data.getPri())
		{
			case 1:
				a1.pushDataNS(ref->data);
				break;
			case 2:
				a2.pushDataNS(ref->data);
				break;
			case 3:
				a3.pushDataNS(ref->data);
				break;
			case 4:
				a4.pushDataNS(ref->data);
				break;
			default:
				return ref;
		}
		ref = ref->getNext();
	}
	return ref;
}

//used for calculating stats. inserts data into the each prioirty queue stat.
void insertStats(const Job &data, std::vector<struct overStat> &stats, int &count, int pos)
{
	//just add the average wait time, average response time, and average turnaround time
	stats[pos].AveTurnaroundTime += data.getTurn();
	stats[pos].AveWaitTime += data.getWait();
	stats[pos].AveResponseTime += data.getRes();
	++count;
}

//prints out the given stats
void printStats(std::vector<struct overStat> &stats, int size =5)
{
	//if the size is not 5 just reutrn
	if(size != 5)
	{
		return;
	}
	cout << "*************** Algorithm Statistic ****************" << endl;
	//for each q. print out some sort of stat
	for(int i =0; i<size-1 ; ++i)
	{
		std::cout<<"Q"+std::to_string(i+1) +": " <<std::endl;
		std::cout << "Avg Turn: " << stats[i].AveTurnaroundTime << std::endl;
		std::cout << "Avg Wait: " << stats[i].AveWaitTime  << std::endl;
		std::cout << "Avg Resp: " << stats[i].AveResponseTime  << std::endl;
		std::cout << "Throughput:" << stats[i].AveThroughput << std::endl;
	}
	std::cout << "Total: " << std::endl;
	std::cout << "Avg Turn: " << stats[4].AveTurnaroundTime << std::endl;
		std::cout << "Avg Wait: " << stats[4].AveWaitTime  << std::endl;
		std::cout << "Avg Resp: " << stats[4].AveResponseTime  << std::endl;
		std::cout << "Throughput:" << stats[4].AveThroughput << std::endl;
	
}

void computeStats(const List &a, std::vector<struct overStat> &stats)
{
	const Node * temp;
	int count[5];
	//initialize everything to 0
	for(int i = 0; i < 5; ++i)
	{
		//struct overStat a= {0,0,0,0}; 
		overStat a;
		stats.push_back(a);
		count[i] = 0;
	}
	//count how many items are in the queue per prioirty queue and in total.
	for(temp =a.getHead(); temp != nullptr; temp = temp->getNext())
	{
		switch(temp->data.getPri())
		{
			case 1:
				insertStats(temp->data,stats,
					count[0],0);
				break;
			case 2:
				insertStats(temp->data,stats,
					count[1],1);
				break;
			case 3:
				insertStats(temp->data,stats,
					count[2],2);
				break;
			case 4:
				insertStats(temp->data,stats,
					count[3],3);
				break;
			default:
				std::cout << "error" <<std::endl;
				return;
		}
		insertStats(temp->data,stats,
			count[4],4);
	}
	//print out all the finished jobs
	//std::cout << "Jobs: " <<std::endl;
	//a.printList();
	//print out the time chart 
	std::cout << "Time Chart: " <<std::endl;
	//printing out stats
	printTimeChart(a);
	//make the necessary calulations
	for(int i = 0; i < 5; ++i)
	{
		if(count[i] !=0)
		{
			stats[i].AveTurnaroundTime = (double)stats[i].AveTurnaroundTime / count[i];
			stats[i].AveResponseTime = (double)stats[i].AveResponseTime / count[i];
			stats[i].AveWaitTime = (double)stats[i].AveWaitTime / count[i];
			stats[i].AveThroughput = (double)count[i]/100;
		}
	}
	//print the stats
	printStats(stats);

}
