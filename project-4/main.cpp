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
#include <pthread.h>
#include <vector>
#include <ctime>

using namespace std;

int main(int argc, const char * argv[])
{
	srand(time(0));
    int n;
    CustomQueue q;
    q.generateProcesses();
    Job a = q.popProcess();
    a.insertPage(1,1);
    a.insertPage(3,4);
    cout << a.isListed(1) << endl;
    a.removePage(1);
    cout << a.isListed(1) << endl;
    
    Memory myMem;
    myMem = Memory();
    myMem.printMem();
    
    
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
    
    
    return 0;
}

