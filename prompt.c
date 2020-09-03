#include "prompt.h"
#include "headers.h"

char hostname[1000];
char username[1000];
char dir[1000];
char path[1000];

void prompt() 
{
    gethostname(hostname, sizeof(hostname));
    getlogin_r(username, sizeof(username));
    getcwd(dir, sizeof(dir));

    char *pos;
    pos = strstr(dir, home);
    if(pos!=NULL)
    {
        strcpy(path, "~");
        strcat(path, pos+strlen(home));
    }
    else
    {
        strcpy(path, dir);
    }
    
    printf("%s@%s:%s ", username, hostname, path); 
 
}