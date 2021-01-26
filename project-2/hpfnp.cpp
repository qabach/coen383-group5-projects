#include "hpfnp.hpp"
#include "stats.hpp"


//does highest prioirty first, (FCFS for each prioirty)
void hpfnp(const List &a)
{
	List p1, p2, p3, p4, finished;
	int t;
	const Node * ref;
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
	computeStats(finished);
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
void insertStats(const Job &data, double &at, double &aw,
	double &ar, int&c)
{
	//just add the average wait time, average response time, and average turnaround time
	aw += data.getWait();
	ar += data.getRes();
	at += data.getTurn();
	++c;
}

//prints out an indiviudal stat
void subprintStat(std::string s, double &a, int &b)
{
	//if its not 0 print this. otherwise give N/A
	if(b)
	{
		std::cout << s << a/b << std::endl;
	}
	else
	{
		std::cout << s << "N/A" << std::endl;
	}
		
}

//prints out the given stats
void printStats(double a[], int c[], int size =5)
{
	//if the size is not 5 just reutrn
	if(size != 5)
	{
		return;
	}
	//for each q. print out some sort of stat
	for(int i =0; i<size-1 ; ++i)
	{
		subprintStat("Q"+std::to_string(i+1) +": ",a[i],c[i]);
	}
	std::cout << "Total: " << a[4]/c[4] << std::endl << std::endl;
	
}

void computeStats(const List &a)
{
	const Node * temp;
	double qatt[5];
	double qawt[5];
	double qart[5];
	int count[5];
	//initialize everything to 0
	for(int i = 0; i < 5; ++i)
	{
		qatt[i] = 0;
		qawt[i] = 0;
		qart[i] = 0;
		count[i] = 0;
	}
	//count how many items are in the queue per prioirty queue and in total.
	for(temp =a.getHead(); temp != nullptr; temp = temp->getNext())
	{
		switch(temp->data.getPri())
		{
			case 1:
				insertStats(temp->data,qatt[0],qawt[0],qart[0],count[0]);
				break;
			case 2:
				insertStats(temp->data,qatt[1],qawt[1],qart[1],count[1]);
				break;
			case 3:
				insertStats(temp->data,qatt[2],qawt[2],qart[2],count[2]);
				break;
			case 4:
				insertStats(temp->data,qatt[3],qawt[3],qart[3],count[3]);
				break;
			default:
				std::cout << "error" <<std::endl;
				return;
		}
		insertStats(temp->data,qatt[4],qawt[4],qart[4],count[4]);
	}
	//print out all the finished jobs
	//std::cout << "Jobs: " <<std::endl;
	//a.printList();
	//print out the time chart 
	std::cout << "Time Chart: " <<std::endl;
	//printing out stats
	printTimeChart(a);
	cout << "*************** Algorithm Statistic ****************" << endl;
	std::cout << "Avg Turn:" << std::endl;
	printStats(qatt,count);
	std::cout << "Avg Wait:" << std::endl;
	printStats(qawt,count);
	std::cout << "Avg Resp:" << std::endl;
	printStats(qart,count);
	std::cout << "Throughput:" << std::endl;
	std::cout << "Q1: " << count[0]/100.0 << std::endl;
	std::cout << "Q2: " << count[1]/100.0 << std::endl;
	std::cout << "Q3: " << count[2]/100.0 << std::endl;
	std::cout << "Q4: " << count[3]/100.0 << std::endl;
	std::cout << "Total: " << count[4]/100.0 << std::endl;

}
