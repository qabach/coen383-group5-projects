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


#include "multithreads_seller.hpp"

using namespace std;

int main(int argc, const char * argv[])
{

    int n;
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

    multithreads_ticket_seller(n);
    
    
    return 0;
}

