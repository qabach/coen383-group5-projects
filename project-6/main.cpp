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
#include <signal.h>     //for kill()


#define NUM_OF_CHILDREN 5
#define TOTAL_SECONDS 30
#define BUFFER_SIZE 64
#define APPEND_SIZE 80
#define READ_END 0
#define WRITE_END 1

int main()
{
    char write_msg[BUFFER_SIZE];
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
            
            //Child 5 code here
            if(i == 4)
            {
                while(1)
                {
                    char * sec, * milsec, * others;
                    sec = (char *)malloc(10);
                    milsec = (char *)malloc(10);
                    others = (char *)malloc(35);
                    memset(sec,'\0',10);
                    memset(milsec,'\0',10);
                    memset(others,'\0',35);
                    long int _sec;
                    double _milsec;
                    _sec = current.tv_sec-prev.tv_sec;
                    _milsec = current.tv_usec; //since milsec resets every sec; dont need to take the different
                    _milsec /=1000;
                    
                    //prompt for input message from terminal
                    char * read_msg;
                    read_msg = (char *)malloc(BUFFER_SIZE);
                    char * out_msg;
                    out_msg = (char *)malloc(BUFFER_SIZE);
                    printf("Enter message: ");
                    read(0, read_msg, BUFFER_SIZE); //0 for fd indicates stdin
                    
                    char * copy_msg;
                    copy_msg = (char *)malloc(8);
                    strncpy(copy_msg, read_msg, 7);
                    
                    sprintf(sec, "%2.02ld:", _sec);
                    sprintf(milsec, "%05.3f:",_milsec);
                    sprintf(others, "Child %d message %d : ",i+1, count);
                    
                    //send msg to parent
                    memset(out_msg,'\0',BUFFER_SIZE);
                    strcat(out_msg, sec);
                    strcat(out_msg, milsec);
                    strcat(out_msg, others);
                    strcat(out_msg, copy_msg);
                    printf("Write message: %s",out_msg);
                    write(fd[i][WRITE_END], out_msg, strlen(out_msg)+1);
                    ++count;
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
                strcat(write_msg, num);
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
//                        printf("%s", append_msg);
//                        printf("%s",read_msg);
                    }
                }
                break;
            }
        }
        gettimeofday(&current, NULL);
    }
    //terminate child 5 after 30s
    close(fd[4][WRITE_END]);
    kill(pid[4],SIGKILL);
    for(i = 0; i < NUM_OF_CHILDREN; ++i)
    {
        waitpid(pid[i],&stat, 0);
        close(fd[i][READ_END]);
    }
    return 0;
}


