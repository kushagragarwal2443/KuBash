#include "headers.h"
#include "execute.h"
#include "redirection.h"
#include <sys/wait.h> 

void piping(char *command)
{
    // Get subcommands out from pipes
    char *withinpipe[1000];
    withinpipe[0] = strtok(command, "|"); 
    int num_pipe = 0;
    while (withinpipe[num_pipe] != NULL) 
    {  
        num_pipe++;
        withinpipe[num_pipe] = strtok(NULL, "|"); 
    } 

    int pipe_pointers[2];
    int fd=0; 
    
    pid_t pid;

    for(int i=0; i<num_pipe; i++)
    {
        pipe(pipe_pointers);
        pid = fork();
        
        //Child process executes
        if(pid==0)
        {
            dup2(fd, 0);
            if(i+1<num_pipe) 
            {
                dup2(pipe_pointers[1],1);
            }
            close(pipe_pointers[0]);

            char *output_redirec = strstr(withinpipe[i], ">");
            char *input_redirec = strstr(withinpipe[i], "<");

            if((output_redirec != NULL) || (input_redirec != NULL))
            {
                redirection(withinpipe[i]);
            }
            else
            {
                execute(withinpipe[i]);
            }
            
            exit(0);
        }

        //Parent Waits for child to end
        else
        {
            wait(NULL);
            close(pipe_pointers[1]);
            fd = pipe_pointers[0];
        }
    }
}