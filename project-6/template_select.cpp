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
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ioctl.h>


int select_template()
{
    char buffer[128];
    int result, nread;
    fd_set inputs, inputfds; // 2 sets of file descriptors bit-arrays
    struct timeval timeout;
    FD_ZERO(&inputs); // initialize inputs to the empty set
    FD_SET(0, &inputs); // set file descriptor 0 (stdin)
    // Wait for input on stdin for a maximum of 2.5 seconds.
    for (;;)
    {
        inputfds = inputs;
        // 2.5 seconds.
        timeout.tv_sec = 2;
        timeout.tv_usec = 500000;
        // Get select() results. FD_SETSIZE = 1024 bits/FDs
        result = select(FD_SETSIZE, &inputfds,
                        (fd_set *) 0, (fd_set *) 0, &timeout);
        // Check the results.
        // No input: the program loops again.
        // Got input: print what was typed, then terminate.
        // Error: terminate.
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
                if (FD_ISSET(0, &inputfds))
                {
                    ioctl(0,FIONREAD,&nread); // read # of bytes available // on stdin and set nread arg // to that value
                    if (nread == 0)
                    {
                        printf("Keyboard input done.\n");
                        exit(0);
                    }
                    nread = read(0,buffer,nread);
                    buffer[nread] = 0;
                    printf("Read %d characters from the keyboard: %s",nread, buffer);
                }
                break;
            }
        }
    }
}
