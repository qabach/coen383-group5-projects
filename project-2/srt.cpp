#include "srt.hpp"
using namespace std;

//calculate remaining time for each job
int remainingTime(Job a)
{
    return a.getServ() - a.getComp();
}

//for sorting the queue based on remaining time, arrival time is tiebreaker
bool compareFunc(Job a, Job b)
{
    int aTimeLeft = remainingTime(a);
    int bTimeLeft = remainingTime(b);
    if (aTimeLeft == bTimeLeft)
    {
        return a.getArr() < b.getArr();
    }
    else
    {
        return aTimeLeft < bTimeLeft;
    }
}

overStat srt(List a)
{
    cout << "****************SRT*********************" << endl;
    deque<Job> input_queue;
    deque<Job> current_queue;

    deque<string> finishedQueue;
    int quantumAmount = 100;
    int numProcessedJobs = 0;
    double totalResponseTime = 0;
    double totalWaitTime = 0;
    double totalTurnaroundTime = 0;
    // copy generated jobs from input list to queue
    const Node *tmp = nullptr;
    for (tmp = a.getHead(); tmp != nullptr; tmp = tmp->getNext())
    {
        input_queue.push_back(tmp->data);
    }
    // print out the jobs list
    cout << " *** SRT Scheduler Process List *** " << endl;
    for (int i = 0; i < input_queue.size(); i++)
    {
        cout << "Name: " << input_queue[i].getName() << endl;
        cout << "Arrival: " << input_queue[i].getArr() << endl;
        cout << "Service: " << input_queue[i].getServ() << endl;
        cout << "Priority: " << input_queue[i].getPri() << endl;
        cout << endl;
    }
    cout << " *** END OF SRT Scheduler Process List *** " << endl;
    int quantum;
    for (quantum = 0; quantum < quantumAmount; quantum++)
    {
        bool currQueueChanged = false;
        //add new jobs from input queue if they've arrived
        while (!input_queue.empty() && input_queue.front().getArr() <= quantum)
        {
            current_queue.push_back(input_queue.front());
            input_queue.pop_front();
            currQueueChanged = true;
        }
        // CPU idle if the job has not arrived
        if (current_queue.empty())
        {
            finishedQueue.push_back("idle");
            continue;
        }
        //resort queue if new processes arrived
        if (currQueueChanged)
        {
            sort(current_queue.begin(), current_queue.end(), compareFunc);
        }
        //if job gets CPU for first time, set responseTime
        if (current_queue[0].getComp() == 0)
        {
            double res = double(quantum - current_queue[0].getArr());
            current_queue[0].setRes(res);
            totalResponseTime += res;
        }
        //Execute current job
        current_queue[0].setComp(current_queue[0].getComp() + 1);
        finishedQueue.push_back(current_queue[0].getName());
        //If current job finished, remove from queue and update stats
        if (remainingTime(current_queue[0]) == 0)
        {
            double turn = double(quantum - current_queue[0].getArr());
            current_queue[0].setTurn(turn);
            double wait = double(current_queue[0].getTurn() - current_queue[0].getServ());
            current_queue[0].setWait(wait);
            totalTurnaroundTime += turn;
            totalWaitTime += wait;
            numProcessedJobs += 1;
            current_queue.pop_front();
        }
    }
    //finish the remaining processes if they've already started
    while (!current_queue.empty())
    {
        if (current_queue[0].getComp() == 0)
        {
            current_queue.pop_front();
            continue;
        }
        current_queue[0].setComp(current_queue[0].getComp() + 1);
        finishedQueue.push_back(current_queue[0].getName());
        if (remainingTime(current_queue[0]) == 0)
        {
            double turn = quantum - current_queue[0].getArr();
            current_queue[0].setTurn(turn);
            double wait = current_queue[0].getTurn() - current_queue[0].getServ();
            current_queue[0].setWait(wait);
            totalTurnaroundTime += turn;
            totalWaitTime += wait;
            numProcessedJobs += 1;
            current_queue.pop_front();
            quantum++;
        }
    }
    //print stats for the run
    //print out time chart
    cout << "Time Chart from 0 to 99 quanta:" << endl;
    for (int i = 0; i < quantumAmount; i++)
    {
        for (int j = 0; j < i; j++)
        {
            cout << "."; // one dot represents one quantum time
        }
        cout << finishedQueue[0] << endl;
        finishedQueue.pop_front();
    }
    printAlgoStats(totalResponseTime, totalTurnaroundTime, totalWaitTime, numProcessedJobs);

    overStat retVal = retStat(totalResponseTime, totalTurnaroundTime, totalWaitTime, numProcessedJobs);
    return retVal;
}