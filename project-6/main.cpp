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
 
 Project 6
 
 */

#include <iostream>
#include <string>
#include <sys/types.h>  //for pid_t
#include <unistd.h>     //for pipe
#include <sys/time.h>   //time
#include <cstdlib>      //for rand


const int RUN_TIME = 30; //in seconds
const int BUFFE_SIZE = 32;
const int READ_END = 0;
const int WRITE_END = 1;
const int NUM_OF_CHILDREN = 1;


int main()
{
    
    //initialize random sead
    srand(time(NULL));
    //read message
    char read_msg[BUFFE_SIZE];
    
    //file descriptors for tje pipe
    int fd[2];
    
    //children process id
    pid_t pid;
    
    //create a pipe
    if (pipe(fd) == -1) //error
    {
        std::cout << stderr << " - pipe() failed" << std::endl;
        return 401;
    }
    
    //TODO: change const number of children above to 5; now is set to 1 to test print out time
    //fork NUM_OF_CHILDREN chilren processes
    for(int i = 0; i < NUM_OF_CHILDREN; i++)
    {
        pid = fork();
        if (pid > 0)
        {
            std::cout << "Child " << i + 1 << " forked." << std::endl;
            continue;
        }
        else
        {
            break; // if a child, get out of loop. **Note: bad practice I think?
        }
    }
        
    if (pid > 0) //code for parent process
    {
        std::cout << "Parent here!" << std::endl;
        //close write end of pipe
        close(fd[WRITE_END]);
        
        //TODO: add select() and timer then uncomment to read from pipe; otherwise process will terminate as soon as parent read i.e. run only once.
        //TODO: add write to output file
        /*
        read(fd[READ_END],read_msg,BUFFE_SIZE);

        //print out msg
        std::cout << "Parent got: " << read_msg << std::endl;
        
        //close read end after done
        close(fd[READ_END]);
        */
        

    }
    else if (pid ==0) //code for children process
    {

        //initialize time mark 1 for each children
        struct timeval start_time;
        struct timeval time_now;
        gettimeofday(&start_time, NULL);

        time_now = start_time;
        int time_elapsed = 0;
        //close read end of pipe
        close(fd[READ_END]);
        
        while (time_now.tv_sec - start_time.tv_sec < RUN_TIME)
        {
            //TODO: add random sleep of 0-4 seconds
            
            //update time now
            gettimeofday(&time_now, NULL);
            
            //compute seconds and milliseconds
            int sec = time_now.tv_sec - start_time.tv_sec;
            double msec = (time_now.tv_usec)/1000.0;
            
            //combine to get time string
            std::string time_str = std::to_string(sec) + ":" + std::to_string(msec);
            
            
            std::cout << "tsec : " << int(time_now.tv_sec) << " ssec: " << int(start_time.tv_sec) << std::endl;
    
            std::cout << "SEC: " << sec << " MSEC: " << msec << std::endl;
            std::cout << "Time stamp: " << time_str << " Child: " << getpid() << std::endl;
            
            //TODO: once add select() in parent, uncomment to write to pipe
            /*
             
            //write message to pipe
            char write_msg[BUFFE_SIZE]  = "Hello world";
            write(fd[WRITE_END],write_msg,strlen(write_msg)+1);
            
             */
        }
        //cose write end after done
        close(fd[WRITE_END]);
    }
    else
    {
        std::cout << stderr << " - fork() failed." << std::endl;
        return 402;
    }
    return 0;

}


