#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {
    int x=100;
    printf("in main, getpid() is %d, x is %d\n",getpid(),x);
    int rc = fork();
    if( rc < 0 ) {
        printf("fork failed with rc : %d\n",rc);
    }
    else if( rc == 0 ) {
        printf("fork succeeded, I'm a child, my pid is %d, and my parent pid is %d\n",getpid(),getppid());
        while(true) {
            x=x+1;
            printf("child : x is %d\n",x);
            sleep(1);
        }
    }
    else {
        printf("fork succeeded, I'm the parent, my pid is %d, and the child I forked is %d\n",getpid(),rc);
        while(true) {
            x=x-1;
            printf("parent : x is %d ( before wait )\n",x);
            sleep(1);
        }
        wait(NULL);
        printf("parent : x is %d ( after wait )\n",x);
    }
}