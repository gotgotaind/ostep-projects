#define _GNU_SOURCE
#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <sched.h>

#define errExit(msg)    do { perror(msg); exit(EXIT_FAILURE); \
                        } while (0)

enum { NS_PER_SECOND = 1000000000 };
enum { AVG_CLOCK_GETTIME_NS = 35 };  // got that by testing with an empty loop

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
    struct timespec clock_res;
    if( clock_getres(CLOCK_REALTIME,&clock_res) != 0 ) {
        printf("Error getting clock\n");
        exit(EXIT_FAILURE);
    }
    printf("Clock res is %ld seconds %ld nanoseconds.\n",clock_res.tv_sec,clock_res.tv_nsec);


    cpu_set_t set;
    CPU_SET(0, &set);
    if (sched_setaffinity(0, sizeof(set), &set) == -1)
    errExit("sched_setaffinity");
    
    int PAGESIZE=1024*4;
    int jump = PAGESIZE / sizeof(int);
    int NUMPAGES=1;
    
    int num_tests=1024*1024*32;
    long start_ns,end_ns;
    //int a[2048*PAGESIZE / sizeof(int)];
    int *a;
    int prev_avg=1;

    while(NUMPAGES<1024*1024) {
        
        a=malloc(NUMPAGES*PAGESIZE);
        if( a==NULL ) {
            printf("malloc failed.\n");
            exit(EXIT_FAILURE);
        }

        long total_time=0;   // excluding 2 first runs
        for(int test_i=0;test_i<num_tests;test_i++) {
            start_ns=clk();
            if( test_i==0 ) {
            for(int i=0; i<NUMPAGES*PAGESIZE/sizeof(int); i+=jump) {
                a[i]=1;
            }}
            else
            {
            for(int i=0; i<NUMPAGES*PAGESIZE/sizeof(int); i+=jump) {
                a[i]+=1;
            }                
            }

            end_ns=clk();
            if( test_i > 0 ) {
                total_time=total_time+end_ns-start_ns-AVG_CLOCK_GETTIME_NS;
            }
            // printf("NUMPAGES: %d, test_i: %d, duration(ns): %ld,\n",NUMPAGES,test_i,(end_ns-start_ns));
        }
        free(a);
        float avg=(float)total_time/(num_tests-1)/NUMPAGES;
        // float avg=(float)total_time/(num_tests-1);
        printf("NUMPAGES: %d, average : %f ns\n",NUMPAGES,avg);
        if( NUMPAGES > 32 ) {
            NUMPAGES=NUMPAGES*2;
            num_tests=num_tests/2;
        }
        else
        {
            NUMPAGES=NUMPAGES+1;
        }
        
    }
}