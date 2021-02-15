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
 
 Project 4
 
 */
#include <iostream>
#include <vector>
#include <ctime>
#include "linked.hpp"
#include "memory.hpp"
#include "LRU.hpp"
#include "MFUfromLFU.hpp"
#include "LFU.hpp"
#include "FIFO.hpp"
#include "random2.hpp"

using namespace std;
void printStats(std::vector<std::tuple<int,int,int>> stats_vec);

void printStats(std::vector<std::tuple<int,int,int>> stats_vec);


int main()
{
    CustomQueue q;
    q.generateProcesses();

    std::vector<std::tuple<int,int,int>> stats_vec_rand;
        for (int i = 0; i < 5; i++)
        {   CustomQueue cq;
            cq.generateProcesses();
            auto stats = Random_paging(cq);
            stats_vec_rand.push_back(stats);
        }
        printStats(stats_vec_rand);
        std::cout << "***** END OF Random *****" << std::endl << std::endl;

    
    for (int i =0; i < 5 ; ++i)
    {	
    	double c;
    	CustomQueue q;
    	q.generateProcesses();
    	std::cout<<"-----------60 seconds--------------" <<std::endl;
    	a2+= LRU(q, c, true);
    	a+= c;
    	std::cout<<std::endl;
    	std::cout<<"---------------100 References----------" <<std::endl;
    	b2= LRU(q, c, false);
    	b+= c;
    	std::cout<<std::endl;
    }
    std::cout <<"LRU avg # of hit/miss of 60s: "
    << a/5.0<< std::endl;
    std::cout <<"LRU avg # of hit/miss of 100 References: "
    << b/5.0 <<std::endl;
    std::cout <<"LRU avg # of processes switched of 60s: "
    << a2/5.0<<std::endl;
    std::cout <<"LRU avg # of processes of 100 References: "
    << b2/5.0<<std::endl;

    
    std::vector<std::tuple<int,int,int>> stats_vec;
    for (int i = 0; i < 5; i++)
    {   CustomQueue cq;
        cq.generateProcesses();
        auto stats = LFU_paging(cq);
        stats_vec.push_back(stats);
    }
    printStats(stats_vec);
    std::cout << "***** END OF LFU *****" << std::endl << std::endl;

    std::vector<std::tuple<int,int,int>> stats_vec_MFU;
    for (int i = 0; i < 5; i++)
    {
        auto stats = MFU_paging(q);
        stats_vec_MFU.push_back(stats);
    }
    printStats(stats_vec_MFU);
    std::cout << "***** END OF MFU *****" << std::endl << std::endl;
  
    
    
    std::vector<std::tuple<int,int,int>> stats_vec;
    for (int i = 0; i < 5; i++)
    {
        std::cout << "******************** RUN " << i+1 << " ******************" << std::endl;
        CustomQueue cq;
        cq.generateProcesses();
        auto stats = FIFO(cq);
        stats_vec.push_back(stats);
    }
    printStats(stats_vec);
    std::cout << "***** END OF FIFO *****" << std::endl << std::endl;
    
    return 0;
}

void printStats(std::vector<std::tuple<int,int,int>> stats_vec)
{
    std::cout << std::endl << "**************** OVERALL STATISTICS ********************" << std::endl;
    
    double avg_swapped_in = 0.0;
    double avg_hit = 0.0;
    double avg_miss = 0.0;

    for (int i = 0; i< stats_vec.size();i++)
    {
        avg_swapped_in += std::get<0>(stats_vec[i]);
        avg_hit += std::get<1>(stats_vec[i]);
        avg_miss += std::get<2>(stats_vec[i]);
    }
    
    std::cout << "Average swapped in:  " << avg_swapped_in/double(stats_vec.size()) << std::endl;
    std::cout << "Average hit       :  " << avg_hit/double(stats_vec.size()) << std::endl;
    std::cout << "Average miss      :  " << avg_miss/double(stats_vec.size()) << std::endl;
    std::cout << "Hit/Miss ratio: " << (avg_hit/double(stats_vec.size()))/(avg_miss/double(stats_vec.size())) << std::endl;

}


