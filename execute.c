#include "headers.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
#include "set_env.h"
#include "unset_env.h"
#include "jobs.h"
#include "kjob.h"
#include "bg.h"
#include "overkill.h"
#include "fg.h"
#include <sys/types.h>
#include <sys/wait.h>

void execute(char *command)
{
    char fullcommand[1000];
    strcpy(fullcommand, command);


    char *withincommands[1000];
    char *withincommandsremAnd[1000];
    int countis=0;

    // Get subcommands out
    withincommands[0] = strtok(fullcommand, "\r\t "); 
    int numwithincom = 0;
    while (withincommands[numwithincom] != NULL) 
    {  
        numwithincom++;
        withincommands[numwithincom] = strtok(NULL, "\r\t "); 
    } 

    if(strcmp(withincommands[0],"pwd")==0)
    {
        pwd();
    }

    else if(strcmp(withincommands[0], "exit")==0)
    {
        exit(0);
    }

    else if(strcmp(withincommands[0], "echo")==0)
    {
        echo(command);
    }
    
    else if(strcmp(withincommands[0], "cd")==0)
    {
        cd(command);
    }

    else if(strcmp(withincommands[0], "ls")==0)
    {
        ls(command);
    }

    else if(strcmp(withincommands[0], "pinfo")==0)
    {
        pinfo(command);
    }

    else if(strcmp(withincommands[0], "jobs")==0)
    {
        jobs();
    }

    else if(strcmp(withincommands[0], "kjob")==0)
    {
        kjob(command);
    }

    else if(strcmp(withincommands[0], "bg")==0)
    {
        bg(command);
    }

    else if(strcmp(withincommands[0], "fg")==0)
    {
        fg(command);
    }

    else if(strcmp(withincommands[0], "overkill")==0)
    {
        overkill();
    }

    else if(strcmp(withincommands[0], "history")==0)
    {
        int numbercommands;
        if(numwithincom == 1)
        {
            numbercommands=10;
        }
        else
        {
            numbercommands=atoi(withincommands[1]);
        }
        
        if(numbercommands>10)
        {
            printf("Error maximum number of commands allowed is 10\n");
        }
        else
        {
            if(hist_number -numbercommands <0)
            {
                numbercommands = hist_number;
            }
            for(int i = hist_number-numbercommands; i<=hist_number-1; i++)
            {
                printf("%s",history[i]);
            } 
        }
    }

    else if(strcmp(withincommands[0], "setenv") == 0)
    {
        set_env(command);
    }

    else if(strcmp(withincommands[0], "unsetenv") == 0)
    {
        unset_env(command);
    }

    else
    {   

    //Check for presence of & parameter
    char params[1000];
    int and_flag=0;
    for(int i=0;i<numwithincom;i++)
    {
        strcpy(params, "");
        strcpy(params, withincommands[i]);
        if(strcmp(params, "&")==0)
        {
            and_flag=1;
        }
        else
        {
            withincommandsremAnd[countis] = withincommands[i];
            countis++;
        }
        
    }
    
    // Creating my child process
    pid_t pid=fork();
    
    //Check for Child process
    if(pid==0)
    {
        int s = execvp(withincommands[0], withincommandsremAnd);   
        if(s==-1)
        {
            printf("%s: Command not found\n", withincommands[0]);
        }

        exit(0);
    }

    //Check for Parent process
    else if(pid>0)
    {
        //If and absent then run in foreground hence wait for child
        if(and_flag==0)
        {
            waitpid(pid, NULL, 0);
        }
        else
        {
            printf("Starting background process %s with pid [%d]\n", withincommands[0], pid+1);
            job_pid[num_jobs]=pid;
            strcpy(job_name[num_jobs], withincommands[0]);
            num_jobs++;
        }
               
    }

    else
    {
        printf("fork() failed\n");
    }
    }
}



