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

char *userinput;
ssize_t len = 0;
char *commands[1000];
char *withincommands[1000];
char fullcommand[1000];
char history[21][1000];
char path_to_history[1000];
int hist_number =0;

int main()
{

    getcwd(home, sizeof(home));

    //For History Reading history.txt
    FILE * file_history;
    char *lin;

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

            // Checking Redirection
            
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
                //Executing other commands

                if(strcmp(withincommands[0], "history")==0)
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


                else
                {
                    execute(fullcommand);
                }

            }
            


        }

    }

}