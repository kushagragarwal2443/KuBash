#include "headers.h"
#include <sys/types.h>
#include <signal.h>

void kjob(char *command)
{
    char fullcommand[1000];
    strcpy(fullcommand, command);
    char *withincommands[1000];

    // Get args out
    withincommands[0] = strtok(fullcommand, "\r\t "); 
    int numwithincom = 0;
    while (withincommands[numwithincom] != NULL) 
    {  
        numwithincom++;
        withincommands[numwithincom] = strtok(NULL, "\r\t "); 
    } 

    if (numwithincom != 3)
        printf("Error: kjob should only have 2 arguements\n");

    else
    {
        int job_number = atoi(withincommands[1]);
        int sig_number = atoi(withincommands[2]);

        if(job_number< 0 || job_number > num_jobs)
        {
            printf("Error: jobnumber should be in the range 1-%d\n", num_jobs);
        }
        else
        {   
            if(sig_number == 9)
            {
                kjobkill_flag = 1;
            }
            kill(job_pid[job_number-1], sig_number);
        }
    }

}
    