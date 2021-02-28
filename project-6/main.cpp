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
 
 Select() Template from professor
 
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

#define NUM_OF_CHILDREN 5
#define TOTAL_SECONDS 30
#define BUFFER_SIZE 64
#define APPEND_SIZE 80
#define READ_END 0
#define WRITE_END 1

int main()
{
	char write_msg[BUFFER_SIZE] = "You're my child process!";
    char read_msg[BUFFER_SIZE];
    char append_msg[APPEND_SIZE];
    fd_set inputs, inputfds; // 2 sets of file descriptors bit-arrays
    struct timeval timeout, current, prev;
    pid_t pid[NUM_OF_CHILDREN]; // child process id
    int fd[NUM_OF_CHILDREN][2]; // file descriptors for the pipe
    int i=0, stat, result, nread;
    
    FD_ZERO(&inputs); // initialize inputs to the empty set
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
    	if (pid[i] > 0)
    	{
    		close(fd[i][WRITE_END]);
    		FD_SET(fd[i][READ_END], &inputs); // set file desciprtor pipe?
    		printf("%d\n",fd[i][READ_END]);
    	}
    	else if (pid[i] == 0)
    	{
    		close(fd[i][READ_END]);
    		srand(time(NULL) + getpid());
    		gettimeofday(&prev, NULL);
			gettimeofday(&current, NULL);
			//keep track of time too.
			int count = 1;
    		while(current.tv_sec - prev.tv_sec < TOTAL_SECONDS)
    		{
    			char num[10], milNum[10], other[35];
    			long int sec;
    			double milsec;
    			sec = current.tv_sec-prev.tv_sec;
    			milsec = current.tv_usec - prev.tv_usec;
    			milsec /=1000;
    			sprintf(num, "%2.02ld:", sec);
    			sprintf(milNum, "%05.3f:", 
    				milsec);
    			sprintf(other, "Child %d message %d\n", 
    				i+1, count);
    			memset(write_msg,'\0',BUFFER_SIZE);
    			strcpy(write_msg, num);
    			strcat(write_msg, milNum);
    			strcat(write_msg, other);
    			write(fd[i][WRITE_END], write_msg, strlen(write_msg)+1);
    			sleep(rand()%3 + 1);
    			++count;
    			gettimeofday(&current, NULL);
    		}
    		close(fd[i][WRITE_END]);
    		return 0;
    	}
    	else
    	{
    		fprintf(stderr, "fork() failed");
        	return 1;
    	}
	}
	
	gettimeofday(&prev, NULL);
	gettimeofday(&current, NULL);
	while(current.tv_sec - prev.tv_sec < TOTAL_SECONDS)
	{
		inputfds = inputs;
		timeout.tv_sec = 2;
        timeout.tv_usec = 5000;
        // Get select() results. FD_SETSIZE = 1024 bits/FDs
        result = select(FD_SETSIZE, &inputfds,
                        (fd_set *) 0, (fd_set *) 0, &timeout);
        gettimeofday(&current, NULL);
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
                	if (FD_ISSET(fd[i][READ_END], &inputfds))
                	{
                    	char num[10], milNum[20], other[35];
                    	long int sec;
                    	double milsec;
    					sec = current.tv_sec-prev.tv_sec;
    					milsec = current.tv_usec - prev.tv_usec;
    					milsec/=1000;
                    	ioctl(fd[i][READ_END],FIONREAD,&nread); 
                    	// read # of bytes available 
                    	// on pipe and set nread arg 
                    	// to that value
                    	if (nread == 0)
                    	{
                    	    printf("Child %d Finished.\n", i+1);
                    	    FD_CLR(fd[i][READ_END],&inputs);
                    	    break;
                    	}
                    	nread = read(fd[i][READ_END],read_msg,nread);
    					sprintf(num, "%2.02ld:", 
    						sec);
    					sprintf(milNum, "%05.3f:Parent:", 
    				milsec);
    					memset(append_msg,'\0',APPEND_SIZE);
    					strcpy(append_msg, num);
    					strcat(append_msg, milNum);
    					printf("%s", append_msg);
                    	printf("%s",read_msg);
                	}
            	}
				break;
        	}
        }
		gettimeofday(&current, NULL);
	}
	for(i = 0; i < NUM_OF_CHILDREN; ++i)
    {
    	waitpid(pid[i],&stat, 0);
    	close(fd[i][READ_END]);
    }
	return 0;
}


