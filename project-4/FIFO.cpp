
#include "FIFO.hpp"


const int TIME_LIMIT = 60; //msec; time to run the simulator in miliseconds i.e. 1 minute

std::tuple<int,int,int> FIFO (CustomQueue customer_queue)
{
    //Program Announcement
    std::cout << "********** FIFO **********" << std::endl << std::endl;

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
            //pop job out of waiting queue
            waiting_queue.pop_front();
            //print_time_log(&servicing_queue.back(), time, 0, last_reference.back(), &memory_map, memory_map.getFreeMemNum());
            print_time_log_g(&servicing_queue.back(), time, 0, last_reference.back(), &memory_map, memory_map.getFreeMemNum(),nullptr,0);
            memory_map.printMem();
            std::cout << std::endl;
            std::cout << std::endl;

        }

        //for every 100ms tick i.e. 10 ticks of 100ms in 1s
        for (int tick = 1; tick < 10; tick++)
        {
            //each job will request a reference page
            for (int i = 0; i < servicing_queue.size(); i++)
            {
                //skip if job is already completed i.e. service time == completion time
                if (servicing_queue[i].getServ() <= servicing_queue[i].completion)
                {
                    continue; //just skip to next one
                }
                
                //store prev page number for later use
                int previous_page_num = last_reference[i];
                
                //get the new reference page based on locality reference
                int new_page = locality_reference(last_reference[i], servicing_queue[i].getSize());
                //update the last reference page
                last_reference[i] = new_page;
                
                //if page already in memory, increment the hit++
                if (servicing_queue[i].isListed(new_page))
                {
                    //increment hit
                    hit++;
                    
//                    print_time_log(&servicing_queue[i], time, tick, last_reference[i], &memory_map, memory_map.getFreeMemNum(),nullptr,0);

                }
                //else, add new page into memory
                else
                {
                    //increment miss
                    miss++;
                    //check if memory is full
                    //if full swap first page brought in memory in the current memory
                    if (memory_map.getFreeMemNum() == 0)
                    {
                        double earliestTime = 60;
                        Job * evictJob = nullptr;
                        Page * evictPage = nullptr;
                        int evictPageNum = -1;
                        
                        for(int i = 0; i < servicing_queue.size(); i++)
                        {
                            if (servicing_queue[i].getServ() == servicing_queue[i].completion)
                            {
                                continue; //just skip to next one
                            }
                            
                            
                            for(int j = 0; j < servicing_queue.at(i).getSize(); j++)
                            {
                                if (servicing_queue.at(i).getPageVec()->at(j).isInMem() == true && servicing_queue.at(i).getPageVec()->at(j).getTime() <= earliestTime )
                                {
                                    earliestTime = servicing_queue.at(i).getPageVec()->at(j).getTime();
                                    evictJob = &servicing_queue.at(i);
                                    evictPage = &servicing_queue.at(i).getPageVec()->at(j);
                                    evictPageNum = servicing_queue.at(i).getPageVec()->at(j).getPageNum();
                                }
                            }
                           
                        }
                        
//                        print_time_log(&servicing_queue[i], time, tick, last_reference[i], &memory_map, memory_map.getFreeMemNum(), evictJob , evictPageNum);
                        
                        // evict page
                        memory_map.removePageFromMem(evictJob, evictPageNum);
                        //add new page to memory
                        memory_map.insertPageToMem(&servicing_queue[i], new_page);
                        
                        evictPage->setTime(time + double(tick)/10);
                   
                        
                    }
                    //else, add
                    else
                    {
                        //add new page
                        memory_map.insertPageToMem(&servicing_queue[i], new_page);
                        
                        //updating the time the page got brought into the Memory
                        double timeTick = time + double(tick)/10;
                        Page * insertPage = servicing_queue[i].requestPagePtr(new_page);
                        insertPage->setTime(timeTick);
                       
                        print_time_log_g(&servicing_queue[i], time, tick, last_reference[i], &memory_map, memory_map.getFreeMemNum(),nullptr,0);
                        
                        std::cout << std::endl;

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
                    if (servicing_queue[idx].requestPagePtr(k)->getPageInMemory() >= 0)
                        memory_map.removePageFromMem(&servicing_queue[idx], k); //remove pages from memory once job is done
                }
                memory_map.printMem();
                std::cout << std::endl;
//                servicing_queue.erase(servicing_queue.begin()+idx); //remove job
//                last_reference.erase(last_reference.begin()+idx); //remove job
            }
        }
    }
    
    std::cout << "Swapped in: " << swapped_in << std::endl;
    std::cout << "Hit: " << hit << std::endl;
    std::cout << "Miss: " << miss << std::endl;
    std::cout << "Hit/Miss: " << float(hit)/miss << std::endl;
    
    return std::make_tuple(swapped_in,hit,miss);

}

