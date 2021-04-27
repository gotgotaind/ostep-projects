#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char * argv[] ) {
    char * fn = argv[1];
    FILE *fp = fopen(fn, "r");
    int bs=16000;

    if (fp == NULL) {
        printf("cannot open file %s : %s\n",fn,strerror(errno));
        exit(1);
    }

    char buf[bs];
    while ( fgets(buf,bs,fp) != NULL ) {
        printf("%s",buf);
    }
    printf("\n");


}