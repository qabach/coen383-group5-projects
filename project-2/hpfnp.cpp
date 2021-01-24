#include "hpfnp.hpp"


//does highest prioirty first, (FCFS for each prioirty)
void hpfnp(const List &a)
{
	List p1, p2, p3, p4, finished;
	int t;
	const Node * ref;
	ref = a.getHead();
	t = ref->data.getArr();
	ref = fillQueues(ref,p1,p2,p3,p4,t);
	while(t < 100)
	{
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
		ref = fillQueues(ref,p1,p2,p3,p4,t);
		
	}
	p1.clr();
	p2.clr();
	p3.clr();
	p4.clr();
	finished.printListOnlyName();
	finished.clr();
}
//run a paritcular job given the queue and completion queue.
//returns time taken
void performJob(List &a, List &c, int &t)
{
	Node * temp = a.getHead();
	Job jtemp(temp->data);
	jtemp.stats.turnaroundTime = (t + jtemp.getServ()) - jtemp.getArr();
	jtemp.stats.responseTime = t - jtemp.getArr();
	jtemp.stats.waitTime = jtemp.stats.responseTime
		+jtemp.stats.turnaroundTime;
	c.pushDataNS(jtemp);
	t += jtemp.getServ();
	a.deleteHeadNode();
	
	//std::cout << "yay" <<std::endl;
	return;
}
//returns the node that is greater than time.
const Node * fillQueues(const Node* ref,List &a1,List &a2,List &a3,List &a4, int t)
{
	while(ref != NULL && ref->data.getArr() <= t )
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
