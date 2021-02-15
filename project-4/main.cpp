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
#include "LRU.hpp"
#include <pthread.h>
#include <vector>
#include <ctime>

using namespace std;

int main(int argc, const char * argv[])
{
	srand(time(0));
    int n;
    double a, b, a2, b2;
    CustomQueue q;
    q.generateProcesses();
    //Job a = q.popProcess();
    //a.insertPage(1,1);
    //a.insertPage(3,4);
    //cout << a.isListed(1) << endl;
    //a.removePage(1);
    //cout << a.isListed(1) << endl;
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
    /*
    if(argc !=2)
    {
        cout << "not enough arguements" << endl;
        return -1;
    }

    //note that this might create an error maybe.
    string yay = string(argv[1]);
    for(int i =0; i < yay.length(); ++i)
    {
        if(!isdigit(argv[1][i]))
        {
            cout << "Argument is not a number" << endl;
            return -2;
        }
    }
    n = stoi(yay);
    
    */
    return 0;
}

