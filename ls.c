#include "headers.h"
#include <pwd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <grp.h>
#include <time.h>

int countdig(long int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;     
        ++count;
    }
    return count;
}

void print_ls(char *position, int lflag, int aflag, int countdir)
{


    /***************** FORMING PATH TO DIRECTORY INPUT *************************/

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





    /*****************PRINTING STARTS NOW*****************************/

    struct dirent *de;
    DIR *ourdirectory;
    ourdirectory= opendir(curdir);
    struct stat file;

    if (ourdirectory == NULL || dirnotexist==1)
    {
        printf("ls: Cannot access %s: No such file or directory\n", position);
        return;
    }

        
    if(countdir!=1)
    {
        printf("%s/: \n", position);
    }

    if(aflag == 1 && lflag == 0)
    {
        while ((de = readdir(ourdirectory)) != NULL)
        {
            printf("%s  ", de->d_name);
        }
        printf("\n");
    }

    else if(aflag == 0 && lflag == 0)
    {
        while ((de = readdir(ourdirectory)) != NULL)
        {
            if(de->d_name[0]!='.')
            {
                printf("%s  ", de->d_name);
            }
        }
        printf("\n");
    }

    else if(lflag==1)
    {        
        while ((de = readdir(ourdirectory)) != NULL)
        {
            char time[20];
            if(aflag==0)
            {
                if(de->d_name[0]!='.')
                {
                    //stat
                    stat(de->d_name,&file);

                    //file uid and file gid
                    struct passwd *pw = getpwuid(file.st_uid);
                    struct group  *gr = getgrgid(file.st_gid);

                    //load time in time array
                    strftime(time, 20, "%b %d %R", localtime(&(file.st_ctime)));

                    //****************Printing starts here************************************

                    //check if directory
                    printf((S_ISDIR(file.st_mode))?"d":"-");

                    //check user permissions
                    printf((file.st_mode & S_IRUSR)?"r":"-");
                    printf((file.st_mode & S_IWUSR)?"w":"-");
                    printf((file.st_mode & S_IXUSR)?"x":"-");

                    //check group permissions
                    printf((file.st_mode & S_IRGRP)?"r":"-");
                    printf((file.st_mode & S_IWGRP)?"w":"-");
                    printf((file.st_mode & S_IXGRP)?"x":"-");

                    //check other permissions
                    printf((file.st_mode & S_IROTH)?"r":"-");
                    printf((file.st_mode & S_IWOTH)?"w":"-");
                    printf((file.st_mode & S_IXOTH)?"x":"-");

                    //nlink
                    printf(" %ld",file.st_nlink);

                    //print permissions
                    printf(" %s",pw->pw_name);
                    printf(" %s",gr->gr_name);

                    //formatting for size (right aligned)
                    for(long int dig=0; dig<6-countdig(file.st_size); dig++)
                    {
                        printf(" ");
                    }
                    printf(" %ld",file.st_size);

                    //print time
                    printf(" %s",time);

                    //file name
                    printf(" %s\n",de->d_name);
                }
            }
            else
            {
                //stat
                    stat(de->d_name,&file);

                    //file uid and file gid
                    struct passwd *pw = getpwuid(file.st_uid);
                    struct group  *gr = getgrgid(file.st_gid);

                    //load time in time array
                    strftime(time, 20, "%b %d %R", localtime(&(file.st_ctime)));

                    //****************Printing starts here************************************

                    //check if directory
                    printf((S_ISDIR(file.st_mode))?"d":"-");
                    
                    //check user permissions
                    printf((file.st_mode & S_IRUSR)?"r":"-");
                    printf((file.st_mode & S_IWUSR)?"w":"-");
                    printf((file.st_mode & S_IXUSR)?"x":"-");

                    //check group permissions
                    printf((file.st_mode & S_IRGRP)?"r":"-");
                    printf((file.st_mode & S_IWGRP)?"w":"-");
                    printf((file.st_mode & S_IXGRP)?"x":"-");

                    //check other permissions
                    printf((file.st_mode & S_IROTH)?"r":"-");
                    printf((file.st_mode & S_IWOTH)?"w":"-");
                    printf((file.st_mode & S_IXOTH)?"x":"-");

                    //nlink
                    printf(" %ld",file.st_nlink);

                    //print permissions
                    printf(" %s",pw->pw_name);
                    printf(" %s",gr->gr_name);

                    //formatting for size (right aligned)
                    for(long int dig=0; dig<6-countdig(file.st_size); dig++)
                    {
                        printf(" ");
                    }
                    printf(" %ld",file.st_size);

                    //print time
                    printf(" %s",time);

                    //file name
                    printf(" %s\n",de->d_name);
                
            }            

        }
    }


    if(countdir!=1)
    {
        printf("\n");
    }

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