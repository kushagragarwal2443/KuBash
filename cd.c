#include "headers.h"

void cd(char *command)
{
    char *withincommands[1000];
    char position[1000];
    char bigpath[1000];
    char curdir[1000];
    

    // Get subcommands out
    withincommands[0] = strtok(command, "\r\t "); 
    int numwithincom = 0;
    while (withincommands[numwithincom] != NULL) 
    {  
        numwithincom++;
        withincommands[numwithincom] = strtok(NULL, "\r\t "); 
    } 



    // Multiple subcommands error
    if(numwithincom >2)
    {
        printf("cd: too many arguments\n");
    }


    // CD logic starts
    else if(numwithincom == 2)
    {
        if(strcmp(withincommands[1], "-")==0)
        {
            char prevpath[1000];
            char last_last_working_dir[1000];
            strcpy(last_last_working_dir, last_working_dir);
            getcwd(last_working_dir, sizeof(last_working_dir));
            chdir(last_last_working_dir);
            char *pos = strstr(last_last_working_dir, home);
            if(pos!=NULL)
            {
                strcpy(prevpath, "~");
                strcat(prevpath, pos+strlen(home));
            }
            else
            {
                strcpy(prevpath, last_last_working_dir);
            }
            printf("%s\n", prevpath);
        }
        else
        {
            
            getcwd(last_working_dir, sizeof(last_working_dir));
            strcpy(position, withincommands[1]);
            long long length = strlen(position);

            // Get presence of dot and tilda using respective flags
            long long int tildapresent = 0;
            long long int dotpresent = 0;
            for(long long int a=0; a<length; a++)
            {
                if((int)position[a] == 126 )
                {
                    tildapresent=1;
                }
                if((int)position[a] == 46)
                {
                    dotpresent = 1;
                }
            }

            // Fill curdir array with /0 to initialise
            for(int a = 0; a<1000; a++)
            {
                curdir[a]='\0';
            }

            // Store current position in curdir
            getcwd(curdir, sizeof(curdir));

            // Error handling for chdir
            long long int error=0;

            // Start from home directory where our shell resides
            if(tildapresent==1) 
            {
                strcpy(bigpath, home);
                strcat(bigpath, position+1);
                error = chdir(bigpath);
                if(error == 0)
                {
                    getcwd(bigpath, sizeof(bigpath));
                    strcpy(curdir, bigpath);
                    // printf("%s\n", curdir);
                }
                else
                {
                    printf("Directory does not exist\n");                
                }
                
                
            }

            else if(dotpresent == 1)
            {
                strcpy(bigpath, curdir);
                strcat(bigpath, "/");
                strcat(bigpath, position);
                error = chdir(bigpath);
                if(error == 0)
                {
                    getcwd(bigpath, sizeof(bigpath));
                    strcpy(curdir, bigpath);
                    // printf("%s\n", curdir);
                }
                else
                {
                    printf("Directory does not exist\n");    
                }
            }

            else
            {
                strcpy(bigpath, position);
                error = chdir(bigpath);
                if(error == 0)
                {
                    getcwd(bigpath, sizeof(bigpath));
                    strcpy(curdir, bigpath);
                    // printf("%s\n", curdir);
                }
                else
                {
                    printf("Directory does not exist\n");
                }

            }
        }

    }

}