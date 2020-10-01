#include "headers.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

void jobs()
{
    for(int i=0; i< num_jobs; i++)
    {
        int pid = job_pid[i];
        char stringpid[1000];
        char buffer[1000];
        char job_status[100];
        sprintf(stringpid, "%d", pid);

        // Get file path
        char file[1000];
        strcpy(file, "");
        strcat(file, "/proc/");
        strcat(file, stringpid);
        strcat(file, "/stat");

        int fd = open(file, O_RDONLY);

        if(fd<0)
        {
            printf("Error jobs: incorrect pid\n");
        }
        else
        {
            read(fd, buffer, 1000);

            char *important[1000];
            important[0] = strtok(buffer, "\r\t "); 
            int imp = 0;
            while (important[imp] != NULL) 
            {  
                imp++;
                important[imp] = strtok(NULL, "\r\t "); 
            }

            char stat[2];
            strcpy(stat, important[2]);

            
            if(strcmp(stat, "T")==0)
            {
                strcpy(job_status, "Stopped");
            }
            else
            {
                strcpy(job_status, "Running");
            }
            
            printf("[%d] %s %s [%d]\n", i+1, job_status, job_name[i], pid+1);
            
        }
    }
}