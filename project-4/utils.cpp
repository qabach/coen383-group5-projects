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

#include "utils.hpp"


int locality_reference(int reference_page, int num_of_pages) // num_of_pages can get from Jobs size
{
    int r = rand() % 10; // 0-9
    
    //70% will be within 1 distance
    if (r >= 0 && r <= 6)
    {
        int randnum = rand() % 3; // random a num from 0-2
        
        // [0,1,-1]; one element will be add to page_num
        if (randnum == 2)
            reference_page = (reference_page + num_of_pages -1) % num_of_pages;
        else
            reference_page += randnum;
        
        return reference_page;
    }
    else
    {
        // i is the recent reference page
        //valid range for the next page will be the range outside of  [i-1,i,i+1]
        //full range [0 ... ,i-1, i, i+1, ... 10]
        //rand() % (max_number + 1 - minimum_number) + minimum_number for range min-max
        //procedure:
        //- random a new reference j with 0 <= j <= i-2 or i+2 <= j <= 10
        //- there is a problem with 'i+2 <= j <= 10' since there are job with less than 10 pages i.e. 5 pages
        //- therefore, change to i+2 <= j <= 10 or i+2 <= j <= num_of_pages for job with pages less than 10
        
        int new_page;
        int coin_toss = rand() % 2; //to choose range
        if (coin_toss == 0 && reference_page - 2 >= 0) //first range 0 <= j <= i-2
        {
            //rand() % (max_number + 1 - minimum_number) + minimum_number for range min-max
            int max = reference_page - 2;
            new_page = rand() % (max + 1 - 0) + 0; // range 0:(i-2)
        }
        else if(reference_page + 2 < num_of_pages)
        {
            //check if there are more than 10 pages
            if (num_of_pages < 10)
            {
                int min = reference_page + 2;
                new_page = rand() % (num_of_pages + 1 - min) + min; // range (i+2):num_of_pages
            }
            else
            {
                int min = reference_page + 2;
                new_page = (rand() % (10) + min) % num_of_pages; // range (i+2):10
            }
            
        }
        else
        {
            //rand() % (max_number + 1 - minimum_number) + minimum_number for range min-max
            int max = reference_page - 2;
            new_page = rand() % (max + 1 - 0) + 0; // range 0:(i-2)
        }
        return new_page;
    }
    
}
