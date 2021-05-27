#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

int main(int argc, char * argv[]) {
    int x=100;
    printf("in main, getpid() is %d, x is %d\n",getpid(),x);
    FILE *stream = fopen("file.txt", "r");
    int fd=fileno(stream);
    printf("parent : fd = %d\n",fd);
    if (stream == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    int rc = fork();
    if( rc < 0 ) {
        printf("fork failed with rc : %d\n",rc);
    }
    else if( rc == 0 ) {
        printf("child : fd = %d\n",fd);
        FILE *streamc=fdopen(fd,"r");
        if (streamc == NULL) {
            perror("fopen");
            exit(EXIT_FAILURE);
        }
        printf("fork succeeded, I'm a child, my pid is %d, and my parent pid is %d\n",getpid(),getppid());
        // printf("child : x is %d\n",x);
        // x=200;
        // printf("child : x is now %d\n",x);
        char *linec = NULL;
        size_t lenc = 0;
        ssize_t nreadc;
        sleep(2);
        while(true) {
            if ((nreadc = getline(&linec, &lenc, streamc)) != -1) {
                printf("child : Retrieved line of length %zd:\n", nreadc);
                fwrite(linec, nreadc, 1, stdout);
            }
            else {
                printf("child : nread is %ld\n",nreadc);
                perror("child : getline");
            }
            sleep(2);
        }
    }
    else {
        printf("fork succeeded, I'm the parent, my pid is %d, and the child I forked is %d\n",getpid(),rc);
        // printf("parent : x is %d ( before wait )\n",x);
        char *line = NULL;
        size_t len = 0;
        ssize_t nread;
        sleep(1);
        while(true) {

            if ((nread = getline(&line, &len, stream)) != -1) {
                printf("parent : Retrieved line of length %zd:\n", nread);
                fwrite(line, nread, 1, stdout);
            }
            sleep(2);
        }
        
        wait(NULL);
        if ((nread = getline(&line, &len, stream)) != -1) {
            printf("parent : Retrieved line of length %zd:\n", nread);
            fwrite(line, nread, 1, stdout);
        }
        free(line);
        // printf("parent : x is %d ( after wait )\n",x);
    }
}