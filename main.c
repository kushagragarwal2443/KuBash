#include "prompt.h"
#include "pwd.h"
#include "echo.h"
#include "cd.h"
#include "ls.h"
#include "headers.h"
#include "pinfo.h"
#include "execute.h"
#include "redirection.h"
#include "piping.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

char *userinput;
ssize_t len = 0;
char *commands[1000];
char *withincommands[1000];
char fullcommand[1000];
char path_to_history[1000];

void delete_all()
{
    for (int j = 0; j < num_jobs; j++)
    {
        job_pid[j] = 0;
        strcpy(job_name[j], "");
    }  

    num_jobs = 0;

}

void delete_pr(int id)
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

void check_child()
{
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    if(overkill_flag == 1)
    {
        delete_all();
        return;
    }

    for(int i = 0; i < num_jobs; i++)
    {
        if(( WIFEXITED(status) || kjobkill_flag == 1 ) && pid == job_pid[i])
        {
            if(WEXITSTATUS(status) == 0)
            {
                fprintf(stderr, "%s with pid %d: exited normally with exit status: %d\n", job_name[i], pid+1, WEXITSTATUS(status));
                prompt();
            }
            else
            {
                fprintf(stderr, "%s with pid %d: exitted abnormally\n", job_name[i], pid+1);
                prompt();
            }

            fflush(stdout);
            delete_pr(pid);
            
            if(kjobkill_flag == 1)
            {
                kjobkill_flag = 0;
            }
        }
    }
}

int main()
{
    
    num_jobs=0;
    overkill_flag = 0;
    kjobkill_flag = 0;
    for(long long int i=0;i<1000;i++)
    {
        strcpy(job_name[i], "");
        job_pid[i] = 0;
    }

    getcwd(home, sizeof(home));
    getcwd(last_working_dir, sizeof(last_working_dir));
    
    //For History Reading history.txt
    FILE * file_history;
    char *lin;
    hist_number = 0;

    strcpy(path_to_history, home);
    strcat(path_to_history, "/history.txt");
    
    if(file_history=fopen(path_to_history, "r"))
    {
        while(getline(&lin, &len, file_history) != -1)
        {
            strcpy(history[hist_number], "");
            strcpy(history[hist_number], lin); 
            hist_number++;           
        }

    }

    while (1)
    {
        signal(SIGCHLD, check_child);
        prompt();
        
        getline(&userinput, &len, stdin);

        // **********************Working on history*************************
        
        if(hist_number<20)
        {
            strcpy(history[hist_number], userinput);
            hist_number++;
        }
        else
        {
            for(int i = 0;i<19;i++)
            {
                strcpy(history[i], history[i+1]);
            }
            strcpy(history[19], userinput);
        }
        FILE *write_hist = fopen(path_to_history, "w");
        for(int i=0;i<hist_number;i++)
        {
            int results = fputs(history[i], write_hist);
        }
        fclose(write_hist);

        //**************** Done with history ****************************


               

        commands[0] = strtok(userinput, ";\n"); 
        int numcom = 0;
        while (commands[numcom] != NULL) 
        {  
            numcom++;
            commands[numcom] = strtok(NULL, ";\n");
            
        } 

        for( int i=0; i<numcom; i++)
        {

            strcpy(fullcommand, commands[i]);
            
            withincommands[0] = strtok(commands[i], "\r\t "); 
            int numwithincom = 0;
            while (withincommands[numwithincom] != NULL) 
            {  
                numwithincom++;
                withincommands[numwithincom] = strtok(NULL, "\r\t ");
                
            } 

            // Checking Piping and Redirection
            
            char *output_redirec = strstr(fullcommand, ">");
            char *input_redirec = strstr(fullcommand, "<");
            char *piping_check = strstr(fullcommand, "|");

            if(piping_check != NULL)
            {
                piping(fullcommand);
            }

            else if((output_redirec != NULL) || (input_redirec != NULL))
            {
                redirection(fullcommand);
            }

            else
            {
                execute(fullcommand);
            }
        }

    }

}