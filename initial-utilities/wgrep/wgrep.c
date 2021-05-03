#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    FILE *stream;
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    char *fn;

    // printf(argv[0]);

    // That's the spec
    if (argc == 1) 
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(0);
    }

    char * pattern = argv[1];
    size_t pattern_length=strlen(pattern);

    // file the list of file to parse
    // in case no file name is provided, must just be stdin
    if(argc == 2) {
        char * file_list[1];
        file_list[0]="stdin";
    }
    else
    {
        char * file_list[argc-2];
        for( int i = 2; i < argc; i++ ) {
            file_list[i-2]=argv[i];
        }
    }

    int input_file_i = 0;
    while (file_list[input_file_i] != NULL)
    {
        fn = file_list[input_file_i];
        stream = fopen(fn, "r");

        if (stream == NULL)
        {
            printf("wgrep: cannot open file\n");
            // better error message, but the specs are to print as in previous line
            // printf("cannot open file %s : %s\n",fn,strerror(errno));
            exit(1);
        }

        int line_nb=0;
        while ((nread = getline(&line, &len, stream)) != -1) {
            // printf("Retrieved line of length %zd:\n", nread);
            // fwrite(line, nread, 1, stdout);
            int char_matched_count=0;
            bool line_matched=false;
            
            for( int i = 0; i < ( nread ) ; i++ ) {
                // fputc(line[i],stdout);
                // printf("%d,%c",i,line[i]);
                if( line[i] == pattern[char_matched_count] ) {
                    char_matched_count++;
                    if( char_matched_count == pattern_length ) {
                        line_matched=true;
                        break;
                    }
                }
            }
            // printf("%d\n",line_nb);
            if( line_matched ) {
                printf("%d:%s",line_nb+1,line);
            }
            line_nb++;

        }

        input_file_i++;

    }
    exit(0);
}
