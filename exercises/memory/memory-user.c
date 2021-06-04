#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>

void usage() {
    printf("usage : memory-user \"size in mega bytes\" \"timeout in seconds\"\n");
    exit(EXIT_FAILURE);
}

long parse_string_to_long(char str[]) {
    int base=10;
    char *endptr;
    long val;

    errno = 0;    /* To distinguish success/failure after call */
    val = strtol(str, &endptr, base);

   /* Check for various possible errors */

   if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        perror("strtol");
        usage();
        exit(EXIT_FAILURE);
    }

   if (endptr == str) {
        fprintf(stderr, "No digits were found\n");
        usage();
        exit(EXIT_FAILURE);
    }
    return val;
}
int main(int argc, char** argv) {
    if( argc != 3 ) {
        usage();
    }

    long MB=parse_string_to_long(argv[1]);
    printf("Will allocate %ld MB\n",MB);
    long timeout=parse_string_to_long(argv[2]);
    printf("Will timeout after %ld seconds\n",timeout);

    long array_size=MB*1024*1024/sizeof(long);
    struct timespec start_time,current_time;
    if( clock_gettime(CLOCK_REALTIME,&start_time) != 0 ) {
        printf("Error getting clock\n");
        exit(EXIT_FAILURE);
    }
    long *a=(long *) malloc(array_size*sizeof(long));
    if( a==NULL ) {
        printf("malloc failed.\n");
        exit(EXIT_FAILURE);
    }
    if( clock_gettime(CLOCK_REALTIME,&current_time) != 0 ) {
        printf("Error getting clock\n");
        exit(EXIT_FAILURE);
    }
    int delta=current_time.tv_sec-start_time.tv_sec;
    printf("malloc took %d seconds\n",delta);
    // printf("sizeof int : %zu\n",sizeof(int));
    // printf("sizeof long : %zu\n",sizeof(long));
    printf("array_size: %ld\n",array_size);
    sleep(1);

    if( clock_gettime(CLOCK_REALTIME,&start_time) != 0 ) {
        printf("Error getting clock\n");
        exit(EXIT_FAILURE);
    }

    int last_printed_clock_step=-1;
    while(true) {
    for(long i=0; i<array_size;i++) {
        //printf("%ld i\n",i);
        a[i]=i;
        if( clock_gettime(CLOCK_REALTIME,&current_time) != 0 ) {
            printf("Error getting clock\n");
            exit(EXIT_FAILURE);
        }
        delta=current_time.tv_sec-start_time.tv_sec;
        if( delta > last_printed_clock_step ) {
            printf("%d seconds\n",delta);
            last_printed_clock_step++;
        }
        if((delta)>timeout) {
            printf("timeout!\n");
            exit(EXIT_FAILURE);
        }
    }
    }

}
