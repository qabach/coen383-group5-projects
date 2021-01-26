#include "srt.hpp"
#include "stats.hpp"
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

void srt(List a)
{
    cout << "****************SRT*********************" << endl;
    deque<Job> input_queue;
    deque<Job> current_queue;

    List finishedQueue = List();
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
    std::cout << " *** SRT Sheduler Process List *** " << std::endl;
    for (int i = 0; i < input_queue.size(); i++)
    {
        std::cout << "Name: " << input_queue[i].getName() << std::endl;
        std::cout << "Arrival: " << input_queue[i].getArr() << std::endl;
        std::cout << "Service: " << input_queue[i].getServ() << std::endl;
        std::cout << "Priority: " << input_queue[i].getPri() << std::endl;
        std::cout << std::endl;
    }
    std::cout << " *** END OF SRT Sheduler Process List *** " << std::endl;
    int quantum;
    for (quantum = 0; quantum < quantumAmount; quantum++)
    {
        cout << "Quantum: " << quantum << endl;
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
            continue;
        }
        //resort queue if new processes arrived
        if (currQueueChanged)
        {
            sort(current_queue.begin(), current_queue.end(), compareFunc);
            cout << "Queue changed." << endl;
            for (int i = 0; i < current_queue.size(); i++)
            {
                cout << current_queue[i].getName() << " ";
            }
            cout << endl;
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
        cout << "Served Process: " << current_queue[0].getName() << " Time Left: " << remainingTime(current_queue[0]) << endl;
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
            finishedQueue.insertData(current_queue[0]);
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
        cout << "Served Process: " << current_queue[0].getName() << " Time Left: " << remainingTime(current_queue[0]) << endl;
        if (remainingTime(current_queue[0]) == 0)
        {
            double turn = quantum - current_queue[0].getArr();
            current_queue[0].setTurn(turn);
            double wait = current_queue[0].getTurn() - current_queue[0].getServ();
            current_queue[0].setWait(wait);
            totalTurnaroundTime += turn;
            totalWaitTime += wait;
            numProcessedJobs += 1;
            finishedQueue.insertData(current_queue[0]);
            current_queue.pop_front();
            quantum++;
        }
    }
    //print stats for the run
    printTimeChart(finishedQueue);
    printAlgoStats(totalResponseTime, totalTurnaroundTime, totalWaitTime, numProcessedJobs);
}