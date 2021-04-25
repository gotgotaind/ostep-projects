#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char * argv[] ) {
    char * fn = argv[1];
    FILE *fp = fopen(fn, "r");
    if (fp == NULL) {
        perror("cannot open file");
        exit(1);
    }

}