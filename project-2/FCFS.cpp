//
//  FCFS.cpp
//  Project_2_AT
//
//  Created by Anh Tuk on 1/23/21.
//

#include <iostream>
#include "FCFS.hpp"

overStat FCFS(List * oriProcessQueue)
{
    cout << endl << "******************** FCFS ********************" << endl;
    
    // create an empty queue
    List processQueue;
    processQueue = List();
    
    // Node pointer to the head of the original process queue
    Node * nodePtr = oriProcessQueue->getHead();
    
    // Copy oriProcessQueue (jobs) into new queue
    while(nodePtr != nullptr)
    {
        processQueue.insertData(nodePtr->data);
        nodePtr = nodePtr->getNext();
    }
    
    // print out the created job list
    cout << "Job Queue: " << endl;
    //processQueue->printListOnlyName();
    oriProcessQueue->printList();
    
    // pointer to current Job
    Node * currentNode = nullptr;
    currentNode = processQueue.getHead();  // currentNode point to the front of the queue (job to be processed)
    
    int numProcessedJobs = 0;           // total number of jobs get processed at least once

    double totalResponseTime = 0;
    double totalWaitTime = 0;
    double totalTurnarounTime = 0;
    
    // queue to hold the number of job got processed so far
    List finishedQueue;                 // queue of finished jobs for FCFS
    finishedQueue = List();
   
    
    int timeslice = 0;                  // to keep track of the timeslice
    
    // while job queue is not empty and current time does not exceed 99
    while(currentNode != nullptr && timeslice < 100)
    {
        // **TRACING** Print the job at the head node to be processed at each timeslice
        // cout << endl << "Current time: " << timeslice << endl << endl;
        // currentNode->printData();
        
        // job cannot arrive before the passing of time
        if (timeslice < currentNode->getJob().getArr())
        {
            timeslice++;
        }
        
        else
        {
            int responseTime = timeslice - currentNode->getJob().getArr();
            totalResponseTime += responseTime;
            
            timeslice += currentNode->getJob().getServ();
            
            int turnaroundTime = timeslice - currentNode->getJob().getArr();
            totalTurnarounTime += turnaroundTime;
            
            int waitTime = turnaroundTime - currentNode->getJob().getServ();
            totalWaitTime += waitTime;
            
            // set the waitTime, responseTime, and turnaroundTime to the Job in the current Node
            currentNode->setJobStats(waitTime, responseTime, turnaroundTime);
            
            numProcessedJobs++;         // total number of job has been processed
            
            // **TRACING** print out waitTime, responseTime, and turnaroundTime of the Job in the current Node
            // printStats(currentNode);
            
            finishedQueue.pushDataNS(currentNode->getJob());        // insert the processed job to the finishedQueue
            processQueue.deleteHeadNode();                         // move the processed job out of the queue's head
            
            // **TRACING** print out processedQueue for each timeslide
            // cout << "Processed Queue: " << endl;
            // finishedQueue.printListOnlyName();
            
            currentNode = processQueue.getHead();                  // move the next job to front of the queue
        }
    }
    // print out the stats for each run
    printAlgoStats(totalResponseTime, totalTurnarounTime, totalWaitTime, numProcessedJobs);     // print stats for this run
    // print out the timechart for each run
    printTimeChart(finishedQueue);          // print the time chart
    
    // return the stats to main to keep the total overall average
    overStat retVal = retStat(totalResponseTime, totalTurnarounTime, totalWaitTime, numProcessedJobs);
    return retVal;
}

