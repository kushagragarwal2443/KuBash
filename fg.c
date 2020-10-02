#include "headers.h"
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>

void delete_process(int id)
{
    for (int i = 0; i < num_jobs; i++)
    {
        if (job_pid[i] == id)
        {
            num_jobs--;

            for (int j = i; j < num_jobs; j++)
            {
                job_pid[j] = job_pid[j+1];
                job_pid[j+1] = 0;
                strcpy(job_name[j], job_name[j+1]);
                strcpy(job_name[j+1], "");
            }                
        }
    }
    
}

void fg(char *command)
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
        printf("Error: fg should only have 1 arguement\n");

    else
    {
        int job_num = atoi(withincommands[1]);
        if(job_num > num_jobs || job_num < 0)
        {
            printf("Error: jobnumber should be in the range 1-%d\n", num_jobs);
        }
        else
        {
        
            signal(SIGTTIN, SIG_IGN);
            signal(SIGTTOU,SIG_IGN);

            tcsetpgrp(STDIN_FILENO,job_pid[job_num-1]);

            kill(job_pid[job_num-1], SIGCONT); // Setting state to running

            delete_process(job_pid[job_num-1]);  // Delete process from our array

            waitpid(-1, NULL, WUNTRACED);  // Wait for foreground process to end

            tcsetpgrp(STDIN_FILENO,getpgrp());
            
            signal(SIGTTIN,SIG_DFL);
            signal(SIGTTOU,SIG_DFL);
        }

    }

}