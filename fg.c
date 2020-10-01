#include "headers.h"
#include <sys/types.h>
#include <signal.h>

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
        printf("Hello\n");
    }

}