#include "headers.h"

void print_ls(char *position, int lflag, int aflag, int countdir)
{
    char curdir[1000];
    char bigpath[1000];
    char currentdir[1000];

    long long int length = strlen(position);
    long long int dirnotexist=0;
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

    // Fill curdir array with \0 to initialise
    for(int a = 0; a<1000; a++)
    {
        curdir[a]='\0';
        currentdir[a]= '\0';
    }

    // Store current position in curdir
    getcwd(curdir, sizeof(curdir));
    getcwd(currentdir, sizeof(currentdir));

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
            dirnotexist=1;             
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
            dirnotexist=1;      
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
            dirnotexist=1;  
        }

    }

    chdir(currentdir);

    

    //curdir contains path to directory specified in input
    //currentdir contains path to actual cwd from where ls was invoked
    

    printf("Hello you are in ls print\n");
    printf("Dir path is : %s\n", curdir);
    printf("CWD path is : %s\n", currentdir);
    printf("Value of aflag is : %d\n", aflag);
    printf("Value of lflag is : %d\n", lflag);
    printf("Dir not present flag: %lld\n", dirnotexist);

}

void ls(char *command)
{
    char *withincommands[1000];
    char subcommpath[1000];
    int lflag=0;
    int aflag=0;
    int countdir=0;

    // Get subcommands out
    withincommands[0] = strtok(command, "\r\t "); 
    int numwithincom = 0;
    while (withincommands[numwithincom] != NULL) 
    {  
        numwithincom++;
        withincommands[numwithincom] = strtok(NULL, "\r\t "); 
    } 

    for(int i=1;i<numwithincom;i++)
    {
        if(strcmp(withincommands[i], "-a") == 0)
        {
            aflag=1;
        }
        if(strcmp(withincommands[i], "-l") == 0)
        {
            lflag=1;
        }
        if(strcmp(withincommands[i], "-al") == 0)
        {
            aflag=1;
            lflag=1;
        }
        if(strcmp(withincommands[i], "-la") == 0)
        {
            aflag=1;
            lflag=1;
        }         
    }

    for(int i=1;i<numwithincom;i++)
    {
        if(strcmp(withincommands[i], "-la") != 0 && strcmp(withincommands[i], "-al") != 0 && strcmp(withincommands[i], "-a") != 0 && strcmp(withincommands[i], "-l") != 0)   
        {
            countdir++;

        }     
    }
    if(countdir == 0)
    {
        strcpy(subcommpath, "");
        strcpy(subcommpath, ".");
        print_ls(subcommpath, lflag, aflag, 1);
    }    
    for(int i=1;i<numwithincom;i++)
    {
        if(strcmp(withincommands[i], "-la") != 0 && strcmp(withincommands[i], "-al") != 0 && strcmp(withincommands[i], "-a") != 0 && strcmp(withincommands[i], "-l") != 0)   
        {
            strcpy(subcommpath, "");
            strcpy(subcommpath, withincommands[i]);
            print_ls(subcommpath, lflag, aflag, countdir);
        }     
    }    
}