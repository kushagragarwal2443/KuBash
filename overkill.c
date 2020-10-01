#include "headers.h"
#include <sys/types.h>
#include <signal.h>

void overkill()
{
    overkill_flag = 1;
    
    for(int i=0; i < num_jobs; i++)
        kill(job_pid[i], 9);

}