#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    char *fn;
    FILE *fp;
    int bs = 16000;
    char buf[bs];

    // That's the spec
    if (argc == 1)
        exit(0);

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