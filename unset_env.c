#include "headers.h"

void unset_env(char *command)
{
    char fullcommand[1000];
    strcpy(fullcommand, command);
    char *withincommands[1000];
    int countis=0;

    // Get args out
    withincommands[0] = strtok(fullcommand, "\r\t "); 
    int numwithincom = 0;
    while (withincommands[numwithincom] != NULL) 
    {  
        numwithincom++;
        withincommands[numwithincom] = strtok(NULL, "\r\t "); 
    } 

    if (numwithincom != 2)
        printf("Error: unsetenv should only have 1 arguement\n");

    else
    {
        int setflag = unsetenv(withincommands[1]);
        if(setflag < 0)
            printf("Error: Couldn't unset the environment variable\n");
    }
    
}