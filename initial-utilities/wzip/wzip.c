#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

void print_rl_and_char(uint32_t * rl, unsigned char * cc) {
    size_t fw=1;
    // printf("HERE\n");
    // write the running length
    fw=fwrite(rl, sizeof(*rl), 1,stdout);
    // printf("%d",*rl);
    if( fw != 1 ) {
        printf("wzip: failed to fwrite rl\n");
        exit(1);
    }

    // write the char
    fw=fwrite(cc, sizeof(*cc), 1,stdout);
    // printf("%c\n",*cc);
    if( fw != 1 ) {
        printf("wzip: failed to fwrite cc\n");
        exit(1);
    }
}

void wzip(bool *first_char, uint32_t *rl, unsigned char *cc, bool last_file,FILE *stream)
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



    while ( (ferror(stream) == 0) && (feof(stream) == 0) )
    {
        nread=fread(buf, sizeof(unsigned char), bs, stream);
        // printf("in while fread\n");
        for(int i=0;i<nread;i++) {
            if( *first_char ) {
                *rl=0;
                *cc=buf[i];
                *first_char=false;
            }


            if( *cc == buf[i] ) {
                *rl=*rl+1;
                // if we reached the end of stream and it's the last character we've read
                // print the char and its running length
                // if( (feof(stream) != 0) && (i==(nread-1)) && last_file) {
                // printf("Last file : %s\n",last_file ? "true" : "false");
                // printf("feof : %s\n", (feof(stream) != 0) ? "true" : "false");
                // printf("i : %d,nread-1 : %zu\n",i,(nread-1));
                
            }
            else
            {
                // printf("Last file : %s\n",last_file ? "true" : "false");
                // printf("feof : %s\n", (feof(stream) != 0) ? "true" : "false");
                // printf("i : %d,nread-1 : %zu\n",i,(nread-1));
                print_rl_and_char(rl,cc);
                *cc = buf[i];
                *rl=1;
            }
            
            
            // printf("%c",buf[i]);
        
        if( (feof(stream) != 0) && (i==(nread-1)) && last_file) {
                
                print_rl_and_char(rl,cc);
        }
        total_read=total_read+nread;
        }
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

    // running length
    uint32_t rl=0;
    // current char
    unsigned char cc;
    // there is a special case for the first char we read
    bool first_char=true;
    // and there is a special case also if it's the last file
    // we're reading.
    bool last_file;

    int input_file_i = 1;
    while (argv[input_file_i] != NULL)
    {
        fn = argv[input_file_i];
        stream = fopen(fn, "r");
        last_file=(input_file_i==(argc-1));

        wzip(&first_char,&rl,&cc,last_file,stream);
        input_file_i++;
    }
    
    exit(0);
}
