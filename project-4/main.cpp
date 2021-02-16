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
#include <string>
#include "linked.hpp"
#include "memory.hpp"
#include "LRU.hpp"
#include "MFUfromLFU.hpp"
#include "LFU.hpp"
#include "random2.hpp"
#include "FIFO.hpp"


void printStats(std::vector<std::tuple<int,int,int>> stats_vec);

void printStats(std::vector<std::tuple<int,int,int>> stats_vec);


int main(int argc, char * argv[])
{

    
    srand(time(NULL));
    int n;
    bool isRand = false, isLRU = false, 
    	isFIFO = false, isLFU = false, 
    	isMFU = false, isAll = false;
    double a, b, a2, b2;
    CustomQueue q;
    q.generateProcesses();
    if(argc >= 2)
    {
    	std::string yay = std::string(argv[1]);
    	if(yay.compare("Rand") == 0)
    	{
    		isRand = true;
    	}
    	else if(yay.compare("FIFO") == 0)
    	{
    		isFIFO = true;
    	}
    	else if(yay.compare("LRU") == 0)
    	{
    		isLRU = true;
    	}
    	else if(yay.compare("MFU") == 0)
    	{
    		isMFU = true;
    	}
    	else if(yay.compare("LFU") == 0)
    	{
    		isLFU = true;
    	}
    	else
    	{
    		isAll = true;
    	}

    }
    else
    {
    	isAll = true;
    }
    
    std::vector<std::tuple<int,int,int>> stats_vec_rand;
    if(isAll || isRand)
    {
		for (int i = 0; i < 5; i++)
		{
		    std::cout << "******************** RUN " << i+1 << " ******************" << std::endl;
		    auto stats = Random_paging(q);
		    stats_vec_rand.push_back(stats);
		}
		//printStats(stats_vec_rand);
		std::cout << "***** END OF Random *****" << std::endl << std::endl;
	}
	std::vector<std::tuple<int,int,int>> stats_vec;
    if(isAll || isLFU)
    {
		for (int i = 0; i < 5; i++)
		{
		    auto stats = LFU_paging(q);
		    stats_vec.push_back(stats);
		}
		//printStats(stats_vec);
		std::cout << "***** END OF LFU *****" << std::endl << std::endl;
	}
	std::vector<std::tuple<int,int,int>> stats_vec_MFU;
    if(isAll || isMFU)
    {
		for (int i = 0; i < 5; i++)
		{
		    std::cout << "******************** RUN " << i+1 << " ******************" << std::endl;
		    auto stats = MFU_paging(q);
		    stats_vec_MFU.push_back(stats);
		}
		//printStats(stats_vec_MFU);
		std::cout << "***** END OF MFU *****" << std::endl << std::endl;
    }
   	std::vector<std::tuple<int,int,int>> stats_vec_FIFO;     
    if(isAll || isFIFO)
    {

		for (int i = 0; i < 5; i++)
		{
		    std::cout << "******************** RUN " << i+1 << " ******************" << std::endl;
		    auto stats = FIFO(q);
		    stats_vec_FIFO.push_back(stats);
		}
		printStats(stats_vec_FIFO);
		std::cout << "***** END OF FIFO *****" << std::endl << std::endl;
    }
    std::vector<std::tuple<int,int,int>> stats_vecLFU1, stats_vecLFU2;
    if(isAll || isLRU)
    {
    	for (int i = 0; i < 5; i++)
		{
			std::cout << "******************** RUN " << i+1 << " ******************" << std::endl;
			auto stats = LRU(q, true);
			auto stats2 = LRU(q, false);
			stats_vecLFU1.push_back(stats);
			stats_vecLFU2.push_back(stats2);
		}
	}
		//printStats(stats_vecLFU1);
		//printStats(stats_vecLFU2);
	std::cout << "***** END OF LRU *****" << std::endl << std::endl;
	std::cout << "***** Stats  *****" << std::endl << std::endl;
	std::cout << "***** 60 Seconds  *****" << std::endl << std::endl;
	std::cout << std::endl
		<< "***** Rand *****" << std::endl;
	printStats(stats_vec_rand);
	std::cout << std::endl 
		<< std::endl << "***** LFU *****" << std::endl;
	printStats(stats_vec);
	std::cout << std::endl 
		<< std::endl << "***** MFU *****" << std::endl;
	printStats(stats_vec_MFU);
	std::cout << std::endl 
		<< std::endl << "***** FIFO *****" << std::endl;
	printStats(stats_vec_FIFO);
	std::cout << std::endl 
		<< std::endl << "***** LRU *****" << std::endl;
	printStats(stats_vecLFU1);
	std::cout << std::endl << std::endl;
	std::cout << "***** 100 Page Ref  *****" << std::endl;
	printStats(stats_vecLFU2);
    
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


