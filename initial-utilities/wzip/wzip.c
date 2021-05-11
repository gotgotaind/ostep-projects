#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void wzip(FILE *stream)
{
    size_t bs = 16;
    size_t nread;
    size_t total_read=0;
    unsigned char buf[bs];

    // printf("in wzip\n");

    if (stream == NULL)
    {
        printf("wzip: cannot open file\n");
        // better error message, but the specs are to print as in previous line
        // printf("cannot open file %s : %s\n",fn,strerror(errno));
        exit(1);
    }

    uint32_t rl=0;
    unsigned char cc;
    int first_char=1;

    while ( (ferror(stream) == 0) && (feof(stream) == 0) )
    {
        nread=fread(buf, sizeof(unsigned char), bs, stream);
        // printf("in while fread\n");
        for(int i=0;i<nread;i++) {
            if( first_char == 1 ) {
                rl=1;
                cc=buf[i];
                first_char=0;
            }
            else
            {
                if( (cc != buf[i]) || (feof(stream) != 0) ) {
                    size_t fw=fwrite(&rl, sizeof(rl), 1,stdout);
                    printf("%d",rl);
                    if( fw != 1 ) {
                        printf("wzip: failed to fwrite rl\n");
                    }
                    fw=fwrite(&cc, sizeof(cc), 1,stdout);
                    if( fw != 1 ) {
                        printf("wzip: failed to fwrite cc\n");
                    }
                    cc = buf[i];
                    rl=1;
                }
                else
                {
                    rl++;
                }
            }
            // printf("%c",buf[i]);
        }
        
        total_read=total_read+nread;
    }

    if( ferror(stream) != 0 ) {
        printf("wzip: error during fread\n");
        exit(1);
    }
    if( feof(stream) == 0 ) {
        printf("wzip: fread stopped reading the file while feof was not reach and ferror was not raised.\n");
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
    // aaaabbbcc
}
