#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char * argv[]) {
    printf("in main, getpid() is %d\n",getpid());
    int rc = fork();
    if( rc < 0 ) {
        printf("fork failed with rc : %d\n",rc);
    }
    else if( rc == 0 ) {
        printf("fork succeeded, I'm a child, my pid is %d, and my parent pid is %d\n",getpid(),getppid());
    }
    else {
        printf("fork succeeded, I'm the parent, my pid is %d, and the child I forked is %d\n",getpid(),rc);
    }
}