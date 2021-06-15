#define _GNU_SOURCE
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

enum { NS_PER_SECOND = 1000000000 };

long clk() {
    struct timespec current_time;
    if( clock_gettime(CLOCK_REALTIME,&current_time) != 0 ) {
        printf("Error getting clock\n");
        exit(EXIT_FAILURE);
    }
    return current_time.tv_sec*NS_PER_SECOND + current_time.tv_nsec;
}


int main(int argc,char* argv[] ) {

    //printf("sizeoflong: %zu\n",sizeof(long));
    //exit(0);

    cpu_set_t set;
    CPU_SET(0, &set);
    if (sched_setaffinity(0, sizeof(set), &set) == -1)
    errExit("sched_setaffinity");
    
    int PAGESIZE=1024*4;
    int jump = PAGESIZE / sizeof(int);
    int NUMPAGES=4;
    
    int num_tests=8;
    long start_ns,end_ns;
    //int a[2048*PAGESIZE / sizeof(int)];
    int *a;
    int prev_avg=1;

    for(;NUMPAGES<1024*1024;NUMPAGES=NUMPAGES*2) {
        
        a=malloc(NUMPAGES*PAGESIZE);
        if( a==NULL ) {
            printf("malloc failed.\n");
            exit(EXIT_FAILURE);
        }

        int total_time=0;   // excluding 2 first runs
        for(int test_i=0;test_i<num_tests;test_i++) {
            start_ns=clk();
            for(int i=0; i<NUMPAGES*PAGESIZE/sizeof(int); i+=jump) {
                a[i]+=1;
            }
            end_ns=clk();
            total_time=total_time+end_ns-start_ns;
            // printf("NUMPAGES: %d, test_i: %d, duration(ns): %ld\n",NUMPAGES,test_i,(end_ns-start_ns));
        }
        free(a);
        int avg=total_time/(num_tests-2);
        printf("NUMPAGES: %d, Deviation : %f\n",NUMPAGES,((float) avg)/prev_avg/2);
        prev_avg=avg;
    }
}