#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void wunzip(FILE *stream)
{

    struct ele {
    // running length
    uint32_t rl;
    // current char
    unsigned char c;
    } __attribute__((packed));

    size_t bs = 16;
    size_t nread;
    size_t total_read=0;
    struct ele buf[bs];

    // printf("in wzip\n");

    if (stream == NULL)
    {
        printf("wunzip: cannot open file\n");
        // better error message, but the specs are to print as in previous line
        // printf("cannot open file %s : %s\n",fn,strerror(errno));
        exit(1);
    }



    while ( (ferror(stream) == 0) && (feof(stream) == 0) )
    {
        nread=fread(buf, sizeof(struct ele), bs, stream);
        // printf("in while fread; nread:%ld, size:%ld\n",nread,sizeof(struct ele));
        for(int i=0;i<nread;i++) {
                // printf("rl: %d, char: %c\n",buf[i].rl,buf[i].c);
                for (size_t j = 0; j < buf[i].rl; j++)
                {
                    printf("%c",buf[i].c);
                }
                
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
        printf("wunzip: file1 [file2 ...]\n");
        exit(1);
    }

    int input_file_i = 1;
    while (argv[input_file_i] != NULL)
    {
        fn = argv[input_file_i];
        stream = fopen(fn, "r");
        wunzip(stream);
        input_file_i++;
    }
    
    exit(0);
}
