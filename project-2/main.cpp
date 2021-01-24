/*
 
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Group 5
    Anh Truong
    Manjiri Parab
    Pauldin Bebla
    Quan Bach
    Travis Le
    Yukun Zhang
 
 Project 2
 
 */

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "linked.hpp"

using namespace std;

//Generate a Random Job
//Paramas: a->the List working with, startpoint -> where you want to start,
//count -> how many elements

int generateJob(List &a, int startpoint, int count)
{
	int i;
	Job jobs;
    int arr, pri, serv;
	//generate the random values for a job.
	for(i = startpoint;  i <= startpoint + count - 1; ++i)
	{
		string n = "P" + to_string(i);
		arr = rand() %100;              // arrival time in range 0-99
        serv = rand() % 10 + 1;         // service time in range 1-10
		pri = rand() % 4 + 1;           // priority of job in range 1-4
		jobs=Job(arr, serv, pri,n);
		a.insertData(jobs);
	}
	return i;
}

// statistics to print out
// each scheduler should calculate its own statistics and return this struct
struct statistics
{
    double average_turn_around_time;
    double average_waiting_time;
    double average_response_time;
};


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
	//print out list
	yay.printList();
	yay.clr();
	yay.printList();
	return 0;

	
}

