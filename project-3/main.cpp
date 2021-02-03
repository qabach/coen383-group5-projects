/*
 
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Group 5
    Anh Truong
    Pauldin Bebla
    Quan Bach
    Travis Le
    Yukun Zhang
 
 Project 3
 
 */


#include <iostream>
#include <pthread.h>
#include <string>
#include <cctype>
#include <deque>
#include <algorithm>
#include "jobs.hpp"
#include "multithreads_seller.hpp"

using namespace std;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//int counter;
Seat seats[10][10];
deque<Job> queues[10];

/* function declarations */
// thread function
void * sell (void * seller_type); //**Note: char * is implemented in the original preview document which causes error 'no matching function'

// thread utility function
void wakeup_all_seller_threads();


//Miselanoues functions
//generates a job, serve time depends on priority
//0 = low, 1 == middle. else = high
Job generateAJob(const string &name, const int &pri)
{
    Job job;
    int arr, serv;
    arr = rand() % 60;
    if(pri ==0)
    {
        serv = (rand() % 4) + 4;
    }
    else if(pri == 1)
    {
        serv = (rand() % 3) + 2;
    }
    else
    {
        serv = (rand() % 2) + 1;
    }
    job = Job(arr, serv, pri, name);
    return job;
    
}

//for sorting the queue based on arrival time
bool compareFunc(Job a, Job b)
{
    return a.getArr() < b.getArr();
}

int main(int argc, const char * argv[])
{
    // **** THIS SECTION IS BEING COMMENTED OUT FOR TESTING ******
    /* comment out for now since creating error while testing
    pthread_t threadID[10];
    std::string seller_type;
    deque<Job> totalQueues;
    counter = 0;
    int n;
    if(argc !=2)
    {
        cout << "not enough arguements" << endl;
        return -1;
    }
     
    //note that this might create an error maybe.
    string yay = string(argv[1]);
    for(int i =0; i < yay.length(); ++i)
    {
        if(!isdigit(argv[1][i]))
        {
            cout << "Argument is not a number" << endl;
            return -2;
        }
    }
    n = stoi(yay);
    for(int i = 0; i < n * 6; ++i)
    {
        queues[i/n].push_back(generateAJob("L" + to_string(i),0));
    }
    for(int i = 0; i < n * 3; ++i)
    {
        queues[(i/n)+ 6 ].push_back(generateAJob("M" + to_string(i),1));
    }
    for(int i = 0; i < n; ++i)
    {
        queues[9].push_back(generateAJob("H" + to_string(i),2));
    }
    for(int i = 0; i< 10;++i)
    {
            sort(queues[i].begin(), queues[i].end(), compareFunc);
    }
    for(int i =0; i < n * 10; ++i)
    {
        cout << queues[i/n][i%n].name <<":"
        << queues[i/n][i%n].getArr()<< endl;
    }
    */
    
    // CURRENT TESTING
    
    multithreads_ticket_seller(15);
    
    std::cout << "Done " << std::endl;
    
    return 0;
}


/* THIS SECTION IS BEING COMMENTED OUT FOR TESTING
// Implementation of  declared functions

// thread function
void * sell (void * seller_type)
{
    bool moreWork = false;

    while(moreWork)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);

        //serve any buyer available in this seller queue that is ready
        // now buy ticket till done with all relevant buyers in their queue

    }
    return NULL; //thread exits
}


//function to wake up all threads
void wakeup_all_seller_threads()
{
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}

*/
