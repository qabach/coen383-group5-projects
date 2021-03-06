/*
 
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Group 5
    Author: Pauldin Bebla
 
 Project 4
    This file is the implementation of the Random swapping algorithm
 
 */

#include "random2.hpp"


const int TIME_LIMIT = 60; //msec; time to run the simulator in miliseconds i.e. 1 minute
using namespace std;
std::tuple<int,int,int> Random_paging (CustomQueue customer_queue, bool sim)
{
    //srand(time(0));
    //Program Announcement
    std::cout << "********** Random **********" << std::endl << std::endl;
    int counter = 0;
    //memory map
    Memory memory_map;
    memory_map = Memory();
    
    //process list
    vector<Job> process_list = customer_queue.getProcessList();
    
    //local variables
    //queue to keep track of jobs currently have pages in memory i.e. servicing queue
    std::deque<Job> servicing_queue;
    
    //waiting queue to keep in jobs that are waiting for free memory and queue is updated over time
    std::deque<Job> waiting_queue;
    
    //list to keep track of the last reference number for each job in the servicing queue
    std::deque<int> last_reference;
    
    //finish queue to keep track of completed jobs
    std::deque<Job> finished_queue;
    
    //statistics
    int swapped_in = 0;
    int hit = 0;
    int miss = 0;
    
    
    std::cout << "*** TIME LOG ***" << std::endl;
    //main loop for the simulator to loop every 1s
    for (int time = 0; time < TIME_LIMIT; time++)
    {
        //add arrivals job to waiting queue
        while (process_list[0].getArr()  <= time && process_list.size()>0)
        {
            //add job to process queue
            waiting_queue.push_back(process_list[0]);
            //remove the job from process list
            process_list.erase(process_list.begin());
            //decrement j to get back in range for the new updated list
        }
        
        
        //fill memory if have at least 4 pages available
        while (memory_map.getFreeMemNum() >= 4 && waiting_queue.size() > 0)
        {
            //add to servicing queue
            servicing_queue.push_back(waiting_queue[0]);
            Job * job;
            job = &servicing_queue.back();
            //add last reference page
            last_reference.push_back(0);
            
            //get memory location of the page
            int memLoc = memory_map.getFreePage();
            //add to memory map
            memory_map.insertPageToMem(job, 0);
            swapped_in++;
            //pop job out of waitingt queue
            pushMore(memory_map,job);
            waiting_queue.pop_front();
            print_time_log_g(&servicing_queue.back(), time, 0, last_reference.back(), &memory_map, memory_map.getFreeMemNum(),nullptr,0);
            print_timestamp_log(memory_map, &servicing_queue.back(), time, "enter");
            std::cout << std::endl << std::endl;
            //counter++;               
        }
        if(counter >= 100 && !sim)
        {
        	return std::make_tuple(swapped_in,hit,miss);
        }
        
        //for every 100ms tick i.e. 10 ticks of 100ms in 1s
        for (int tick = 0; tick < 10; tick++)
        {
        	std::set<int> repeat;
            //each job will request a reference page
            for (int i = 0; i < servicing_queue.size(); i++)
            {
                //skip if job is already completed i.e. service time == completion time
                if (servicing_queue[i].getServ() <= servicing_queue[i].completion)
                {
                    continue; //just skip to next one
                }
                if(counter >= 100 && !sim)
                {
                	break;
                }
                ++counter;
                //store prev page number for later use
                int previous_page_num = last_reference[i];
                
                //get the new reference page based on locality reference
                int new_page = locality_reference(last_reference[i], servicing_queue[i].getSize());
                //update the last reference page
                last_reference[i] = new_page;
                
                //if page already in memory, increment the freq. used
                if (servicing_queue[i].isListed(new_page))
                {
                    //increment hit
                    hit++;
                    print_time_log_g(&servicing_queue[i], time, tick, last_reference[i], &memory_map, memory_map.getFreeMemNum(),nullptr,0);

                }
                //else, add new page into memory
                else
                {
                    //increment miss
                    miss++;
                    //check if memory is full
                    //if full swap the least freq. used page
                    if (memory_map.getFreeMemNum() == 0)
                    {
                        //evict page and add new page
                        int idx;
                        do{
                        	idx =rand() % memory_map.getInMemNum();
                        }while(repeat.find(idx)!=repeat.end());
                        repeat.insert(idx);
                        
                        //remove page from memory
                        auto * job_to_evict = std::get<1>(memory_map.getMemMap()[idx]);
                        
                        
                        int page_to_evict = -1;
                        //need to get page number to evict
                        for (int x = 0; x < job_to_evict->getSize();x++)
                        {
                            if (job_to_evict->requestPage(x).getPageInMemory() == idx)
                                page_to_evict = job_to_evict->requestPage(x).getPageNum();
                        }
                        
                        print_time_log_g(&servicing_queue[i], time, tick, last_reference[i], &memory_map, memory_map.getFreeMemNum(),job_to_evict,page_to_evict);

                        
                        //remove page from memory
                        memory_map.removePageFromMem(job_to_evict, page_to_evict);
                        //add new page to memory
                        memory_map.insertPageToMem(&servicing_queue[i], new_page);
                    }
                    //else, add
                    else
                    {
                        print_time_log_g(&servicing_queue[i], time, tick, last_reference[i], &memory_map, memory_map.getFreeMemNum(),nullptr,0);
                        //add new page
                        memory_map.insertPageToMem(&servicing_queue[i], new_page);

                    }
                }
            }
        }
        
        //increment service time for job in queue
        for (int i = 0; i < servicing_queue.size(); i++)
        {
            servicing_queue[i].completion++;
        }
        
        //exit job out of queue once finish
        for (int idx = 0; idx < servicing_queue.size(); idx++)
        {
            //if job is complete i.e. service time == completion
            if (servicing_queue[idx].getServ() == servicing_queue[idx].completion)
            {
                /*for(int k = 0; k < servicing_queue[idx].getSize();k++)
                {
                    if (servicing_queue[idx].requestPage(k).getPageInMemory() >= 0)
                    {
                        memory_map.removePageFromMem(&servicing_queue[idx], k); //remove pages from memory once job is done
                        memory_map.printMem();
                        std::cout << std::endl << std::endl;
                    }

                }*/
                memory_map.removeProcessFromMem(&servicing_queue[idx]);
                print_timestamp_log(memory_map, &servicing_queue[idx], time, "exit");
            }
        }
    }
    
    std::cout << "Swapped in: " << swapped_in << std::endl;
    std::cout << "Hit: " << hit << std::endl;
    std::cout << "Miss: " << miss << std::endl;
    
    return std::make_tuple(swapped_in,hit,miss);
}


void print_time_log_rand (Job *job, int time, int last_reference,Memory *memory_map, int free_space, Job * ptr, int page_to_evict)
{
    std::string job_evict = "None";
    std::string page_evict = "None";
    std::cout << "timestamp: " << time << " sec" << std::endl;
    std::cout << "      - Job               : " << job->getName() << std::endl;
    std::cout << "      - Page reference    : " << last_reference << std::endl;
    std::cout << "      - Page in memory    : ";
    for (int num = 0; num < job->getSize();num++)
    {
        if (job->isListed(num))
            std::cout << job->requestPage(num).getPageNum() << " ";
    }
    std::cout << std::endl;
    if (free_space == 0 && ptr != nullptr)
    {
        job_evict  = ptr->getName();
        page_evict = std::to_string(page_to_evict);
        std::cout << "      - Page to evicted   : " << job_evict << "/" << page_evict <<  std::endl;
    }
    else
    {
        std::cout << "      - Page to evicted   : " << job_evict << "/" << page_evict <<  std::endl;
    }
    std::cout << std::endl;
}
