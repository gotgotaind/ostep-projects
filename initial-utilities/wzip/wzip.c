#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void wzip(FILE *stream)
{
    int bs = 16000;
    char buf[bs];

    if (stream == NULL)
    {
        printf("wgrep: cannot open file\n");
        // better error message, but the specs are to print as in previous line
        // printf("cannot open file %s : %s\n",fn,strerror(errno));
        exit(1);
    }

    while (fgets(buf, bs, stream) != NULL)
    {
        printf("%s", buf);
    }
}

int main(int argc, char *argv[])
{
    FILE *stream;
    char *fn;

    // That's the spec
    if (argc == 1)
    {
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }

    int input_file_i = 2;
    while (argv[input_file_i] != NULL)
    {
        fn = argv[input_file_i];
        stream = fopen(fn, "r");
        wzip(stream);
        input_file_i++;
    }
    
    exit(0);
}
