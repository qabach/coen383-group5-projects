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
#include <pthread.h>
#include <string>

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

/* function declarations */
// thread function
void * sell (void * seller_type); //**Note: char * is implemented in the original preview document which causes error 'no matching function'

// thread utility function
void wakeup_all_seller_threads();




int main(int argc, const char * argv[])
{
    pthread_t threadID[10];
    std::string seller_type;
    
    //Create necessary data structures for simulator
    //Create buyers list for each seller ticket queue based on
    //the N value within an hour (60 count of 1 min) and have them in the sller queue
    
    //Create 10 threads representing the 10 sellers

    //create the H seller
    seller_type = "H";
    pthread_create(&threadID[0], NULL, sell, &seller_type);
    
    //create 3 M's sellers
    seller_type = "M";
    for (int i = 1; i < 5; i++)
        pthread_create(&threadID[i], NULL, sell, &seller_type);
    
    //create 6 L's sellers
    seller_type = "L";
    for (int i = 4; i < 10; i++)
        pthread_create(&threadID[i], NULL, sell, &seller_type);
    
    //wakeup all seller threads
    wakeup_all_seller_threads();
    
    //wakit for all the seller threads to exit
    for (int i = 0; i < 10; i++)
        pthread_join(threadID[i], NULL); //**Note &tids[i] was used in the original preview which causes 'no matching func' error.
    
    // Print out similation results
    
    
    return 0;
}



/* Implementation of  declared functions */

// thread function
void * sell (void * seller_type)
{
    bool moreWork = false;
    
    while(moreWork)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_unlock(&mutex);
        
        //serve any buyer available in this seller queue that is ready
        // now buy ticket till done with all relevant buyers in their queue
        
    }
    return NULL; //thread exits
}


//function to wake up all threads
void wakeup_all_seller_threads()
{
    pthread_mutex_lock(&mutex);
    pthread_cond_broadcast(&cond);
    pthread_mutex_unlock(&mutex);
}
