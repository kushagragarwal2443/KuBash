#include "headers.h"
#include <sys/types.h>
#include <signal.h>

void bg(char *command)
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

    if (numwithincom != 2)
        printf("Error: bg should only have 1 arguement\n");

    else
    {
        int job_number = atoi(withincommands[1]);

        if(job_number< 0 || job_number > num_jobs)
        {
            printf("Error: jobnumber should be in the range 1-%d\n", num_jobs);
        }
        else
        {
            kill(job_pid[job_number-1], SIGCONT);
        }
    }

}
    