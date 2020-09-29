#include "headers.h"

void set_env(char *command)
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

    if (numwithincom != 3)
        printf("Error: setenv should only have 2 arguements\n");

    else
    {
        int setflag = setenv(withincommands[1], withincommands[2], 1);
        if(setflag < 0)
            printf("Error: Couldn't set the environment variable\n");
    }

}
    