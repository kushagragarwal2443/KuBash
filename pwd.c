#include "headers.h"

void pwd()
{
    char dir[10000];
    getcwd(dir, sizeof(dir));
    printf("%s\n", dir);
    
}