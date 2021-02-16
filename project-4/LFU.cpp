/*
 
 Santa Clara University
 COEN 383 - Ad. Operating Systems
 Winter 2021
 Group 5
    Author: Quan Bach
 
 Project 4
    This file is the implementation of the Least Frequently Used swapping algorithm
 
 */

#include "LFU.hpp"


const int TIME_LIMIT = 60; //msec; time to run the simulator in miliseconds i.e. 1 minute

std::tuple<int,int,int> LFU_paging (CustomQueue customer_queue, bool sim)
{
    //Program Announcement
    std::cout << "********** LEAST FREQUENTLY USED **********" << std::endl << std::endl;
    
    //for the 2nd option of 100 jobs
    int counter = 0;
    //memory map
    Memory memory_map;
    memory_map = Memory();
    
    //process list
    auto process_list = customer_queue.getProcessList();
    
    //local variables
    //queue to keep track of jobs currently have pages in memory i.e. servicing queue
    std::deque<Job> servicing_queue;
    
    //waiting queue to keep in jobs that are waiting for free memory and queue is updated over time
    std::deque<Job> waiting_queue;
    
    //list to keep track of the last reference number for each job in the servicing queue
    std::deque<int> last_reference;
    
    //finish queue to keep track of completed jobs
    std::deque<Job> finished_queue;
    
    //array of frequency for each slot of memory
    std::vector<int> freq_array(100,0); //initialize to all 0 with 100 slots represent each memory slot
    
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
            //increment the frequency of that slot
            freq_array[memLoc]++;
            //add to memory map
            memory_map.insertPageToMem(job, 0);
            swapped_in++;
            //pop job out of waitingt queue
            waiting_queue.pop_front();
            pushMore(memory_map,job);
            print_time_log_g(&servicing_queue.back(), time, 0, last_reference.back(), &memory_map, memory_map.getFreeMemNum(),nullptr,0);
            print_timestamp_log(memory_map, &servicing_queue.back(), time, "enter");
            std::cout << std::endl << std::endl;
                           
        }
        if(counter >= 100 && !sim)
		{
			return std::make_tuple(swapped_in,hit,miss);
		}
        
        //for every 100ms tick i.e. 10 ticks of 100ms in 1s
        for (int tick = 0; tick < 10; tick++)
        {
            //each job will request a reference page
            for (int i = 0; i < servicing_queue.size(); i++)
            {

                //skip if job is already completed i.e. service time <= completion time
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
                    //update the reference frequency
                    freq_array[servicing_queue[i].requestPage(new_page).getPageInMemory()]++;
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
                        //find the first idx with min
                        int minIdx = std::min_element(freq_array.begin(),freq_array.end()) - freq_array.begin();
                        
                        //remove page from memory
                        auto * job_to_evict = std::get<1>(memory_map.getMemMap()[minIdx]);
                        int page_to_evict = -1;
                        //need to get page number to evict
                        for (int x = 0; x < job_to_evict->getSize();x++)
                        {
                            if (job_to_evict->requestPage(x).getPageInMemory() == minIdx)
                                page_to_evict = job_to_evict->requestPage(x).getPageNum();
                        }
                        
                        print_time_log_g(&servicing_queue[i], time, tick, last_reference[i], &memory_map, memory_map.getFreeMemNum(),job_to_evict,page_to_evict);

                        
                        //remove page from memory
                        memory_map.removePageFromMem(job_to_evict, page_to_evict);
                        //add new page to memory
                        memory_map.insertPageToMem(&servicing_queue[i], new_page);
                        //update the frequency map
                        freq_array[minIdx] = 1;
                    }
                    //else, add
                    else
                    {
                        print_time_log_g(&servicing_queue[i], time, tick, last_reference[i], &memory_map, memory_map.getFreeMemNum(),nullptr,0);
                        //add new page
                        memory_map.insertPageToMem(&servicing_queue[i], new_page);
                        //increment the frequency of this new page
                        freq_array[servicing_queue[i].requestPage(new_page).getPageInMemory()]++;
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
                for(int k = 0; k < servicing_queue[idx].getSize();k++)
                {
                    if (servicing_queue[idx].requestPage(k).getPageInMemory() >= 0)
                    {
                        freq_array[servicing_queue[idx].requestPage(k).getPageInMemory()] = 0;
                        memory_map.removePageFromMem(&servicing_queue[idx], k); //remove pages from memory once job is done
                        //memory_map.printMem();
                        
                    }

                }
                print_timestamp_log(memory_map, &servicing_queue[idx], time, "exit");
            }
        }
    }
    
    std::cout << "Swapped in: " << swapped_in << std::endl;
    std::cout << "Hit: " << hit << std::endl;
    std::cout << "Miss: " << miss << std::endl;
    std::cout << "Hit/Miss ratio: " << double(hit)/double(miss) << std::endl;

    
    return std::make_tuple(swapped_in,hit,miss);
}
