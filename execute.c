#include "headers.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "pinfo.h"
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
        cd(fullcommand);
    }

    else if(strcmp(withincommands[0], "ls")==0)
    {
        ls(fullcommand);
    }

    else if(strcmp(withincommands[0], "pinfo")==0)
    {
        pinfo(fullcommand);
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
        //2 cases arise: 1 with & present other with & absent

        //And present, run it in the background, hence check for end signal
        if(and_flag==1)
        {
            pid_t childpid = fork();

            //Now for the child I have 2 processes child original and child ka child

            //Child ka child to run the process
            if(childpid == 0)
            {
                int s = execvp(withincommands[0], withincommandsremAnd);   
                if(s==-1)
                {
                    printf("%s: Command not found\n", withincommands[0]);
                }

                exit(0);
            }

            //Child ka original to check when the child ends
            else
            {
                int status;

                waitpid(childpid, &status, 0);

                if(WIFEXITED(status))
                {
                    int exit_status = WEXITSTATUS(status);
                    printf("%s with pid %d exited normally\n", withincommands[0], childpid);

                }
                else
                {
                    printf("%s with pid %d exited abnormally\n", withincommands[0], childpid);
                }

                exit(0);
      
            }
        }

        //And absent, run it in the foreground, hence no need to return end signal
        else
        {
            int s = execvp(withincommands[0], withincommands);   
            if(s==-1)
            {
                printf("%s: Command not found\n", withincommands[0]);
            } 
        }
        

    }

    //Check for Parent process
    else if(pid>0)
    {
        //If and absent then run in foreground hence wait for child
        if(and_flag==0)
        {
            waitpid(pid, NULL, 0);
        }       
    }

    else
    {
        printf("fork() failed\n");
    }
    }
}



