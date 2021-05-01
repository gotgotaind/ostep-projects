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
    char * pattern;

    // That's the spec
    if (argc == 1) 
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(0);
    }

    pattern = argv[1];

    int input_file_i = 2;
    while (argv[input_file_i] != NULL)
    {
        fn = argv[input_file_i];
        stream = fopen(fn, "r");

        if (stream == NULL)
        {
            printf("wgrep: cannot open file\n");
            // better error message, but the specs are to print as in previous line
            // printf("cannot open file %s : %s\n",fn,strerror(errno));
            exit(1);
        }

        
        while ((nread = getline(&line, &len, stream)) != -1) {
            // printf("Retrieved line of length %zd:\n", nread);
            // fwrite(line, nread, 1, stdout);

            
            for( int i = 0; i < ( nread ) ; i++ ) {
                putchar(line[i]);
                // fputc(line[i],stdout);
                // printf("%d,%c",i,line[i]);
            }

        }

        input_file_i++;

    }
    exit(0);
}
