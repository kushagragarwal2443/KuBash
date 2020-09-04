#include "headers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void pinfo(char *command)
{
    char *withincommands[1000];
    pid_t pid;
    
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
        printf("pinfo: too many arguments\n");
    }

    // If only 1 subommand then use pid for a.out
    else if(numwithincom == 1)
    {
        pid = getpid();
    }

    else
    {
        // atoi Converts string to integer
        pid = atoi(withincommands[1]);
    }

    printf("pid -- %d\n", pid);

    int fd;
    char file[1000];
    char exe[1000];
    char executable_path[1000];
    char buffer[1000];

    // Fill with \0s as initialisation
    for(int i = 0; i<1000; i++)
    {
        executable_path[i]='\0';
    }
    
    // To aid in string concatenation
    char stringpid[1000];
    sprintf(stringpid, "%d", pid);

    // Get file path
    strcpy(file, "");
    strcat(file, "/proc/");
    strcat(file, stringpid);
    strcat(file, "/stat");

    // Get exe path which will later get us the executable path
    strcpy(exe, "");
    strcat(exe, "/proc/");
    strcat(exe, stringpid);
    strcat(exe, "/exe");

    fd = open(file, O_RDONLY);

    if(fd<0)
    {
        printf("pinfo: incorrect pid\n");
    }
    else
    {
        read(fd, buffer, 1000);

        // 2nd and 23rd words in the file are of interest
        // We therefore tokenize using strtok
        char *important[1000];
        important[0] = strtok(buffer, "\r\t "); 
        int imp = 0;
        while (important[imp] != NULL) 
        {  
            imp++;
            important[imp] = strtok(NULL, "\r\t "); 
        }

        printf("Process Status -- %s\n", important[2]);
        printf("Memory -- %s\n", important[22]);

        // Getting executable path
        readlink(exe, executable_path, 1000);
        strcat(executable_path, "\0");

        // printf("Executable: %s\n", executable_path);
        // We need to print the executable relative to our home directory
        char *pos;
        char path[1000];
        for(int i = 0; i<1000; i++)
        {
            path[i]='\0';
        }
        pos = strstr(executable_path, home);
        if(pos!=NULL)
        {
            strcpy(path, "~");
            strcat(path, pos+strlen(home));
        }
        else
        {
            strcpy(path, executable_path);
        }
        printf("Executable Path -- %s\n", path);
        
    }
}