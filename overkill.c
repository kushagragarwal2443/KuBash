#include "headers.h"
#include <sys/types.h>
#include <signal.h>

void overkill()
{
    for(int i=0; i < num_jobs; i++)
        kill(job_pid[i], SIGKILL);

}