#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *fn;

    // That's the spec
    if (argc == 1) 
    {
        printf("wgrep: searchterm [file ...]");
        exit(0);
    }

    int i = 1;
    while (argv[i] != NULL)
    {
        fn = argv[i];
        fp = fopen(fn, "r");

        if (fp == NULL)
        {
            printf("wcat: cannot open file\n");
            // better error message, but the specs are to print as in previous line
            // printf("cannot open file %s : %s\n",fn,strerror(errno));
            exit(1);
        }

        
        while (fgets(buf, bs, fp) != NULL)
        {
            printf("%s", buf);
        }
        //printf("\n");
        i++;

    }
    exit(0);
}