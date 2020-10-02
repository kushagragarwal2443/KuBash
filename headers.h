#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include <unistd.h>    

char home[1000];
char last_working_dir[1000];
char history[21][1000];
int hist_number;

int shell_pid;

int job_pid[1000];
char job_name[1000][100];
int num_jobs;

int fg_id;
char fg_name[100];

int kjobkill_flag;
int overkill_flag;