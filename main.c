#include "prompt.h"
#include "pwd.h"
#include "headers.h"

char *userinput;
ssize_t len = 0;
char *commands[1000];
char *withincommands[1000];

int main()
{

    getcwd(home, sizeof(home));

    while (1)
    {
        prompt();
        
        getline(&userinput, &len, stdin);
        printf("%s", userinput);

        commands[0] = strtok(userinput, ";\n"); 
        int numcom = 0;
        while (commands[numcom] != NULL) 
        {  
            printf("Command %d, %s\n", numcom+1, commands[numcom]);
            numcom++;
            commands[numcom] = strtok(NULL, ";\n");
            
        } 

        for( int i=0; i<numcom; i++)
        {
            withincommands[0] = strtok(commands[i], "\r\t "); 
            int numwithincom = 0;
            while (withincommands[numwithincom] != NULL) 
            {  
                printf("Command %d, Subcommand %d, %s\n", i+1, numwithincom+1, withincommands[numwithincom]);
                numwithincom++;
                withincommands[numwithincom] = strtok(NULL, "\r\t ");
                
            } 

            if(strcmp(withincommands[0],"pwd")==0)
            {
                pwd();
            }


        }

    }

}