#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void wzip(FILE *stream)
{
    size_t bs = 16;
    size_t nread;
    size_t total_read=0;
    unsigned char buf[bs];

    printf("in wzip\n");

    if (stream == NULL)
    {
        printf("wzip: cannot open file\n");
        // better error message, but the specs are to print as in previous line
        // printf("cannot open file %s : %s\n",fn,strerror(errno));
        exit(1);
    }

    

    while ( ( nread=fread(buf, sizeof(unsigned char), bs, stream) ) == bs)
    {
        // printf("in while fread\n");
        for(int i=0;i<bs;i++) {
            printf("%c",buf[i]);
        }
        
        total_read=total_read+nread;
    }

    if( ferror(stream) != 0 ) {
        printf("ferror\n");
    }
    if( feof(stream) != 0 ) {
        printf("feof\n");
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

    int input_file_i = 1;
    while (argv[input_file_i] != NULL)
    {
        fn = argv[input_file_i];
        stream = fopen(fn, "r");
        wzip(stream);
        input_file_i++;
    }
    
    exit(0);
}
