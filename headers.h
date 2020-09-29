#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>    

char home[1000];
char last_working_dir[1000];
char history[21][1000];
int hist_number;