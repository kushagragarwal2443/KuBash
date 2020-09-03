#include "prompt.h"
#include "headers.h"

char hostname[1000];
char username[1000];
char dir[1000];

void prompt() 
{
    gethostname(hostname, sizeof(hostname));
    getlogin_r(username, sizeof(username));
    getcwd(dir, sizeof(dir));

    if(strcmp(dir, home)==0)
        strcpy(dir, "~");

    // Complete the rest 2 conditions while coding for cd

    printf("%s@%s:%s ", username, hostname, dir); 
 
}