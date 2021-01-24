#include <iostream>
#include <cstdlib>
#include <ctime>
#include "linked.hpp"
#include "hpfnp.hpp"

using namespace std;

//Generate a Random Job
//Paramas: a->the List working with, startpoint -> where you want to start,
//count -> how many elements

int generateJob(List &a, int startpoint, int count)
{
	int i;
	Job jobs;
	int arr, serv, pri;
	//generate the random values for a job.
	for(i = startpoint;  i <= startpoint + count - 1; ++i)
	{
		string n = "P" + to_string(i);
		arr = rand() %100;
		serv = (rand() % 11) + 1;
		pri = (rand() % 4) + 1;
		jobs=Job(arr, serv, pri,n);
		a.insertData(jobs);
	}
	return i;
}


int main()
{
	cout << "Note: this is C++" <<endl;
	List yay;
	int seed = 1;
	int count, count2;
	srand(1);
	yay = List();
	//generate 10 jobs
	count = generateJob(yay,1,10);
	count2 = 2;
	//generatate more jobs if needed
	while(yay.notIdle())
	{
		count = generateJob(yay,count,count2);
		count2 *= 2;
	}
	cout << yay.length() << endl;
	//run algo
	hpfnp(yay);
	yay.clr();
	cout << "end of program" <<endl;
	return 0;

	
}
