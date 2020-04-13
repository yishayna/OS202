#include "types.h"
#include "stat.h"
#include "user.h"

struct perf {
int ps_priority;
int stime;
int retime;
int rtime;
};
struct perf* performance  ;
int
main(int argc, char *argv[])
{
    int i, status;

    for(i=2; i>-1; i--){
        if(fork() == 0){
            set_cfs_priority(i);
            set_ps_priority(5*i);

            int k = 100000000;
            int dummy = 0;
            while(k--)
            dummy+=k;
            
            proc_info(performance);
            // to check: way formatting the string by %10s (width option) doesn't works.
            printf(1,"PID    PS_PRIORITY    STIME   RETIME   RTIME \n");    
            printf(1,"%d       %d          %d         %d       %d    \n", getpid(),performance->ps_priority, performance->stime,performance->retime,performance->retime);    
            exit(0);

        } 
    }
    for (i = 0; i < 3; i++) {
        wait(&status);// collect zombies
    }
    exit(0);
}