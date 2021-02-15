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
#include "linked.hpp"
#include "memory.hpp"
#include <pthread.h>
#include <vector>
#include <ctime>
#include "random2.hpp"
using namespace std;
void printStats(std::vector<std::tuple<int,int,int>> stats_vec);

int main(int argc, const char * argv[])
{
    CustomQueue q;
    q.generateProcesses();
    std::vector<std::tuple<int,int,int>> stats_vec;
        for (int i = 0; i < 5; i++)
        {   CustomQueue cq;
            cq.generateProcesses();
            auto stats = Random_paging(cq);
            stats_vec.push_back(stats);
        }
        printStats(stats_vec);
        std::cout << "***** END OF Random *****" << std::endl << std::endl;
    return 0;
}

void printStats(std::vector<std::tuple<int,int,int>> stats_vec)
{
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

}

