//
//  multithreads_seller.cpp
//  coen383-project3
//
//  Created by Quan Bach  on 1/31/21.
//

#include "multithreads_seller.hpp"


//initialize pthread utility variables
pthread_cond_t condition    = PTHREAD_COND_INITIALIZER;
pthread_mutex_t stdout_lock = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock        = PTHREAD_MUTEX_INITIALIZER;





//time of closing; end_time is in the 59th mininute once opening
const int END_TIME = 59;

// queues for 10 sellers
std::deque<Job> ticketbooth_queues [10];



/* CRITICAL SECTION */
//number of seats
int num_of_seats = 100;
// logs for each type of
std::vector<std::string> H_log;
std::vector<std::string> M_log;
std::vector<std::string> L_log;
//chronicle log of events
std::multimap <std::string, std::string> chronicle_log;
/* END OF CRITICAL SECTION */

//key set for chronicle log
std::set<std::string> keySet;
/* FUNCTION DEFINITION: wake up all threads */
//function to wake up all threads
void wakeup_all_seller_threads()
{
    pthread_mutex_lock(&lock);
    pthread_cond_broadcast(&condition);
    pthread_mutex_unlock(&lock);
}


/* FUNCTION DEFINITION: thread function */
void * sell (void * data)
{
    auto *incoming = (std::tuple<std::string,int> *) data;
    
    pthread_mutex_lock(&stdout_lock);
    std::cout << std::get<0>(*incoming) << ", " << std::get<1>(*incoming) << " " << int_to_string(std::get<1>(*incoming)) << std::endl;
    pthread_mutex_unlock(&stdout_lock);
    
    int booth_ID = std::get<1>(*incoming);
    auto seller_name = std::get<0>(*incoming);
    int time_now = 0; //initialize time now for each thread; each thread will track its own time
    int customer_ID = 1; //starting number of customer ID
    
    //main loop
    //condition for loop to run: still have time left, still have seat left
    while (time_now <= END_TIME && num_of_seats > 0)
    {
        //serving customers
        if (ticketbooth_queues[booth_ID].size() == 0)
        {
            time_now++; //increment time
            continue; //just sleep if no customer
        }
        else // service customers in line
        {
            //update time now if customer has not arrived
            if (time_now < ticketbooth_queues[booth_ID][0].getArr())
            {
                time_now = ticketbooth_queues[booth_ID][0].getArr();
            }
            
            switch (booth_ID) //perform tasks based on seller type
            {
                case 0:
                    pthread_mutex_lock(&lock);
                    if (num_of_seats == 0)//check again if seat is still available

                    {
                        continue; //exit
                    }
                    else
                    {
                        
                        //create the log message
                        auto log_str = seller_name + " starts serving a new customer";
                        chronicle_log.insert(std::pair<std::string,std::string>(int_to_string(time_now),log_str)); //insert to log
                        
                        //add key to keySet
                        keySet.insert(int_to_string(time_now));
                        
                        num_of_seats--; //issue ticket
                        
                        //create ticket number
                        auto ticket_str = seller_name + int_to_string(customer_ID);
                        
                        //update log based on seller type
                        H_log.push_back(ticket_str);
                        
                        //update time now with the service time
                        time_now += ticketbooth_queues[booth_ID][0].getServ();
                        
                        //new log message
                        log_str = seller_name + " issued ticket " + ticket_str;
                        chronicle_log.insert(std::pair<std::string,std::string>(int_to_string(time_now),log_str)); //insert to log
                        
                        //add key to keySet
                        keySet.insert(int_to_string(time_now));
                        
                        //increment customer ID
                        customer_ID++;
                        
                        //remove served customer
                        ticketbooth_queues[booth_ID].pop_front();
                    }
                    pthread_mutex_unlock(&lock);
                    break;
                case 1 ... 3:
                    pthread_mutex_lock(&lock);
                    if (num_of_seats == 0)//check again if seat is still available

                    {
                        continue; //exit
                    }
                    else
                    {
                        
                        //create the log message
                        auto log_str = seller_name + " starts serving a new customer";
                        chronicle_log.insert(std::pair<std::string,std::string>(int_to_string(time_now),log_str)); //insert to log
                        
                        //add key to keySet
                        keySet.insert(int_to_string(time_now));
                        
                        num_of_seats--; //issue ticket
                        
                        //create ticket number
                        auto ticket_str = seller_name + int_to_string(customer_ID);
                        
                        //update log based on seller type
                        M_log.push_back(ticket_str);
                        
                        //update time now with the service time
                        time_now += ticketbooth_queues[booth_ID][0].getServ();
                        
                        //new log message
                        log_str = seller_name + " issued ticket " + ticket_str;
                        chronicle_log.insert(std::pair<std::string,std::string>(int_to_string(time_now),log_str)); //insert to log
                        
                        //add key to keySet
                        keySet.insert(int_to_string(time_now));
                        
                        //increment customer ID
                        customer_ID++;
                        
                        //remove served customer
                        ticketbooth_queues[booth_ID].pop_front();
                    }
                    pthread_mutex_unlock(&lock);
                    break;
                case 4 ... 9:
                    pthread_mutex_lock(&lock);
                    if (num_of_seats == 0)//check again if seat is still available

                    {
                        continue; //exit
                    }
                    else
                    {
                        
                        //create the log message
                        auto log_str = seller_name + " starts serving a new customer";
                        chronicle_log.insert(std::pair<std::string,std::string>(int_to_string(time_now),log_str)); //insert to log
                        
                        //add key to keySet
                        keySet.insert(int_to_string(time_now));
                        
                        num_of_seats--; //issue ticket
                        
                        //create ticket number
                        auto ticket_str = seller_name + int_to_string(customer_ID);
                        
                        //update log based on seller type
                        L_log.push_back(ticket_str);
                        
                        //update time now with the service time
                        time_now += ticketbooth_queues[booth_ID][0].getServ();
                        
                        //new log message
                        log_str = seller_name + " issued ticket " + ticket_str;
                        chronicle_log.insert(std::pair<std::string,std::string>(int_to_string(time_now),log_str)); //insert to log
                        
                        //add key to keySet
                        keySet.insert(int_to_string(time_now));
                        
                        //increment customer ID
                        customer_ID++;
                        
                        //remove served customer
                        ticketbooth_queues[booth_ID].pop_front();
                    }
                    pthread_mutex_unlock(&lock);
                    break;
                
                default:
                    break;
            }
        }
    }
    return NULL;
}


/* FUNCTION DEFINITION: populate_jobs */
//function to populate jobs in to 10 queues
void populate_jobs(int count)
{
    // populate each queue
    for (int i = 0; i < 10; i++)
    {
        //seed randome each queue
        srand(int(time(NULL)));
        List yay;
        yay = List();
        int arr, serv, pri;
        Job jobs;
        switch (i)
        {
            case 0:
                for (int j = 0; j < count; j++)
                {
                    auto n = "C" + std::to_string(j);
                    //rand() % (max_number + 1 - minimum_number) + minimum_number for range min-max
                    arr = rand() % (59 + 1 - 0) + 0;
                    serv = rand() % (2 + 1 - 1) + 1;
                    pri = (rand() % 4) + 1;
                    jobs = Job(arr, serv, pri, n);
                    yay.insertData(jobs);
                }
                break;
            case 1 ... 3:
                for (int j = 0; j < count; j++)
                {
                    auto n = "C" + std::to_string(j);
                    //rand() % (max_number + 1 - minimum_number) + minimum_number for range min-max
                    arr = rand() % (59 + 1 - 0) + 0;
                    serv = rand() % (4 + 1 - 2) + 2;
                    pri = (rand() % 4) + 1;
                    jobs = Job(arr, serv, pri, n);
                    yay.insertData(jobs);
                }
                break;
            case 4 ... 9:
                for (int j = 0; j < count; j++)
                {
                    auto n = "C" + std::to_string(j);
                    //rand() % (max_number + 1 - minimum_number) + minimum_number for range min-max
                    arr = rand() % (59 + 1 - 0) + 0;
                    serv = rand() % (7 + 1 - 4) + 4;
                    pri = (rand() % 4) + 1;
                    jobs = Job(arr, serv, pri, n);
                    yay.insertData(jobs);
                }
                break;

            default:
                break;
        }
        
        //copy jobs to queue
        // copy generated jobs from input list to queue
        const Node * tmp = nullptr;
        for (tmp = yay.getHead(); tmp != nullptr; tmp = tmp->getNext())
        {
            ticketbooth_queues[i].push_back(tmp->data);
        }
        //clear yay
        yay.clr();
        //delete tmp
        tmp = nullptr;
        delete tmp;
    }
}


/* FUNCTION DEFINITION: convert int to string */
std::string int_to_string(int i)
{
    auto re_str = std::to_string(i);
    if (i < 10)
    {
        re_str = "0" + re_str;
        return re_str;
    }
    else
    {
        return re_str;
    }
}


/* FUNCTION DEFINITION: main function */
void multithreads_ticket_seller (int count)
{
    pthread_t threadID[10];
    std::string seller_type;
    
    //Create necessary data structures for simulator
    //Create buyers list for each seller ticket queue based on
    //the N value within an hour (60 count of 1 min) and have them in the seller queue
    
    //populate jobs in to queues
    populate_jobs(count);
    

    // Create seller list
    std::vector<std::tuple<std::string,int>> seller_list;
    
    
    //Print out the description of each seller thread info
    std::cout << "Seller Type / Seller queue ID / Test add leading 0" << std::endl;
    
    //create the H seller
    seller_type = "H";
    std::string seller_name = seller_type + "0";
    int index = 0;
    std::tuple<std::string, int> data = std::make_tuple(seller_name,index);
    seller_list.push_back(data);

    
    //create 3 M's sellers
    std::string seller_type1 = "M";
    for (int i = 1; i < 4; i++)
    {
        std::string seller_name1 = seller_type1 + std::to_string(i);
        data = std::make_tuple(seller_name1,i);
        seller_list.push_back(data);
    }
    
    //create 6 L's sellers
    seller_type = "L";
    index = 1;
    for (int i = 4; i < 10; i++)
    {
        seller_name = seller_type + std::to_string(index);
        data = std::make_tuple(seller_name,i);
        seller_list.push_back(data);
        index++;
    }
    
    //Create 10 threads representing the 10 sellers
    for (int i = 0; i < 10; i++)
    {
        pthread_create(&threadID[i], NULL, sell, &seller_list[i]);
    }
    
    
    
    //wakeup all seller threads
    wakeup_all_seller_threads();
    
    //wait for all the seller threads to exit
    for (int i = 0; i < 10; i++)
        pthread_join(threadID[i], NULL); //**Note &tids[i] was used in the original preview which causes 'no matching func' error.
    
    // Print out simulation results
    std::cout << "***** LOG OF H_TYPE SELLER *****" << std::endl;
    for (int x = 0; x < H_log.size();x++)
    {
        std::cout << H_log[x] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "***** LOG OF M_TYPE SELLER *****" << std::endl;
    for (int x = 0; x < M_log.size();x++)
    {
        std::cout << M_log[x] << " ";
    }
    
    
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "***** LOG OF L_TYPE SELLER *****" << std::endl;
    for (int x = 0; x < L_log.size();x++)
    {
        std::cout << L_log[x] << " ";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    //Size of each log; this should sum up to less than or equal to 100
    std::cout << "*** SIZE OF EACH LOG ***" << std::endl;
    std::cout << H_log.size() << std::endl;
    std::cout << M_log.size() << std::endl;
    std::cout << L_log.size() << std::endl;
    std::cout << "*** CHECK IF: SUM <= 100 ***" << std::endl;

    
    //Chronicle log of events
    std::cout << "***** CHRONICLE LOG OF EVENTS *****" << std::endl;
    for (auto setItr = keySet.begin(); setItr != keySet.end(); setItr++)
    {
        std::cout << "Time stamp: 00:" << setItr->data() << std::endl;
        for (auto itr = chronicle_log.begin(); itr != chronicle_log.end(); itr++)
        {
            if (itr->first == setItr->data())
            {
                std::cout << "   - " << itr->second << std::endl;
            }
        }
        std::cout << std::endl;
    }
    
}


