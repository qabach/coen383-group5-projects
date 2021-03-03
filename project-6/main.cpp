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


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>
#include <sys/ioctl.h>
#include <signal.h>     //for kill()



#define NUM_OF_CHILDREN 5
#define TOTAL_SECONDS 30
#define BUFFER_SIZE 90
#define APPEND_SIZE_CHILD 140
#define APPEND_SIZE_PARENT 50
#define READ_END 0
#define WRITE_END 1

int main()
{
    char write_msg[APPEND_SIZE_CHILD]; //limit on how much is being written
    char read_msg[APPEND_SIZE_CHILD]; // limit on how much is being read
    char append_msg[APPEND_SIZE_PARENT]; //Just the size of the parent appending message
    fd_set inputs, inputfds; // 2 sets of file descriptors bit-arrays
    struct timeval timeout, current, prev;
    pid_t pid[NUM_OF_CHILDREN]; // child process id
    int fd[NUM_OF_CHILDREN][2]; // file descriptors for the pipe
    int i=0, stat, result, nread;
    
    FD_ZERO(&inputs); // initialize inputs to the empty set
    //Create 5 children
    for(i = 0; i < NUM_OF_CHILDREN; ++i)
    {
        // Create the pipe.
        if (pipe(fd[i]) == -1)
        {
            fprintf(stderr,"pipe() failed");
            return 1;
        }
        // Fork a child process.
        pid[i] = fork();
        if (pid[i] > 0) //if parent clost write end just conintue
        {
            close(fd[i][WRITE_END]);
            FD_SET(fd[i][READ_END], &inputs); // add file desciprtor pipe
        }
        else if (pid[i] == 0) //if children, close read end and do these
        {
            close(fd[i][READ_END]); //close read end
            srand(time(NULL) + getpid()); //set the random seed
            gettimeofday(&prev, NULL);
            gettimeofday(&current, NULL);
            //keep track of time too.
            int count = 1;
            
            //Child 5 code here
            if(i == 4)
            {
            	char mess[18] = "Enter message: \n";
            	int k = 0;
                while(current.tv_sec - prev.tv_sec < TOTAL_SECONDS)
                {
                    char * sec, * milsec, * others;
                    sec = (char *)malloc(10);
                    milsec = (char *)malloc(10);
                    others = (char *)malloc(22);
                    memset(sec,'\0',10);
                    memset(milsec,'\0',10);
                    memset(others,'\0',22);
                    long int _sec;
                    double _milsec;
                    
                    //prompt for input message from terminal
                    char * read_msg;
                    read_msg = (char *)malloc(BUFFER_SIZE);
                    memset(read_msg,'\0',BUFFER_SIZE);
                    char * out_msg;
                    out_msg = (char *)malloc(APPEND_SIZE_CHILD);
                    if(k!=BUFFER_SIZE-2)
                    	write(1,mess,18);
                    k = read(0, read_msg, BUFFER_SIZE-2); //0 for fd indicates stdin
                    //getting the time after reading
                    gettimeofday(&current, NULL);
                    _sec = current.tv_sec-prev.tv_sec;
                    _milsec = current.tv_usec/10000.0
                    	- prev.tv_usec/10000.0; //since milsec resets every sec; dont need to take the different
                    //sorry it does because it gets current time
                    if(_milsec < 0)
                    {
                    	_milsec +=100;
                    	--_sec;
                    }
                    
                    if(k==BUFFER_SIZE-2)
                    {
                    	strncat(read_msg,"\n",2);
                    }
                    char * copy_msg;
                    copy_msg = (char *)malloc(BUFFER_SIZE);
                    strncpy(copy_msg, read_msg, BUFFER_SIZE-1);
                    
                    sprintf(sec, "%02ld:", _sec);
                    sprintf(milsec, "%06.3f:",_milsec);
                    sprintf(others, "Child %d message %d : ",i+1, count);
                    
                    //send msg to parent
                    memset(out_msg,'\0',BUFFER_SIZE);
                    strcat(out_msg, sec);
                    strcat(out_msg, milsec);
                    strcat(out_msg, others);
                    strcat(out_msg, copy_msg);
                    write(fd[i][WRITE_END], out_msg, APPEND_SIZE_CHILD);
                    ++count;
					
					//get the new time and free everything
                    gettimeofday(&current, NULL);
                    free(out_msg);
                    free(copy_msg);
                    free(read_msg);
                    free(sec);
                    free(milsec);
                    free(others);
                }
                return 0;
            }
            //other children here, loop for the Total amount of seconds (30 seconds)
            while(current.tv_sec - prev.tv_sec < TOTAL_SECONDS)
            {
                char num[10], milNum[10], other[35];
                long int sec;
                double milsec;
                 //calculate time and finish append child messages
                sec = current.tv_sec-prev.tv_sec;
                milsec = current.tv_usec/10000.0 - prev.tv_usec/10000.0;
                if(milsec < 0)
                {
                    milsec +=100;
                    --sec;
                }
                sprintf(num, "%02ld:", sec);
                sprintf(milNum, "%06.3f:",
                    milsec);
                sprintf(other, "Child %d message %d\n",
                    i+1, count);
                memset(write_msg,'\0',BUFFER_SIZE);
                strcat(write_msg, num);
                strcat(write_msg, milNum);
                strcat(write_msg, other);
                
                //write to pipe and sleep for a random time
                write(fd[i][WRITE_END], write_msg, strlen(write_msg)+1);
                sleep(rand()%3 + 1);
                ++count;
                gettimeofday(&current, NULL);
            }
            close(fd[i][WRITE_END]);
            return 0;
        }
        else //if there was an error
        {
            fprintf(stderr, "fork() failed");
            return 1;
        }
    }
    
    //get the time to caultate timestamp
    gettimeofday(&prev, NULL);
    gettimeofday(&current, NULL);
    
    //open up out.txt
    FILE *filePtr;
    filePtr = fopen("output.txt", "w");
    
    if (filePtr == NULL ) //if file had failed to open
    {
        printf( "output.txt file failed to open." ) ;
    }
    else
    {
        printf( "Open output.txt \n" ) ;
        //while it hasn't past the total time specified(30 seconds)
        while(current.tv_sec - prev.tv_sec < TOTAL_SECONDS)
        {
            inputfds = inputs;
            timeout.tv_sec = 2;
            timeout.tv_usec = 50000;
            // Get select() results. FD_SETSIZE = 1024 bits/FDs
            result = select(FD_SETSIZE, &inputfds,
                            (fd_set *) 0, (fd_set *) 0, &timeout);
                            
            gettimeofday(&current, NULL); //get current time
            switch(result)
            {
                case 0: { // timeout w/o input
                    printf("@");
                    fflush(stdout);
                    break;
                }
                case -1:
                { // error
                    perror("select");
                    exit(1);
                }
                    // If, during the wait, we have some action on the file descriptor,
                    // we read the input on stdin and echo it whenever an
                    // <end of line> character is received, until that input is Ctrl-D.
                default:
                {   // Got input
                    for(int i =0;i<NUM_OF_CHILDREN; ++i)
                    {
                    	//check each set to see what pipes are available
                        if (FD_ISSET(fd[i][READ_END], &inputfds))
                        {
                            char num[10], milNum[20], other[35];
                            long int sec;
                            double milsec;
                            gettimeofday(&current, NULL); //get current time
                            //calulate the time
                            sec = current.tv_sec-prev.tv_sec;
                            milsec = current.tv_usec/10000.0 
                            	- prev.tv_usec/10000.0;
                            if(milsec < 0)
                    		{
                    			milsec +=100;
                    			--sec;
                    		}		
                    		
                            ioctl(fd[i][READ_END],FIONREAD,&nread);
                            // read # of bytes available
                            // on pipe
                            if (nread == 0) //check to see if nothing is to be read. if there is nothing just exit the loop and end
                            {
                                printf("Child %d Finished.\n", i+1);
                                FD_CLR(fd[i][READ_END],&inputs);
                                break;
                            }
                            //just read only to the append_size_child
                            nread = read(fd[i][READ_END],read_msg,
                            	APPEND_SIZE_CHILD);
                            	
                            //append timestamp to message from child
                            sprintf(num, "%02ld:",
                                sec);
                            sprintf(milNum, "%06.3f:Parent:",
                        milsec);
                            memset(append_msg,'\0',APPEND_SIZE_PARENT);
                            strcpy(append_msg, num);
                            strcat(append_msg, milNum);
                            
                            //write to out.txt
                            fprintf(filePtr,"%s", append_msg);
                            fputs(read_msg,filePtr);
                        }
                    }
                    break;
                }
            }
            gettimeofday(&current, NULL); //get time again
        }
    }
    //terminate child 5 after 30s
    kill(pid[4],SIGKILL);
    
    //close every pipe and wait for children to end
    for(i = 0; i < NUM_OF_CHILDREN; ++i)
    {
        waitpid(pid[i],&stat, 0);
        close(fd[i][READ_END]);
    }
    
    //close file and finish
    printf("Close output.txt \n") ;
    fclose(filePtr);
    
    return 0;
}
