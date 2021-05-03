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


    

    // if no file to grep is provided on the command line,
    // we should grep stdin. So we build a list of 
    // files to grep taking this case into account
    // The list we use is a NULL terminated list of size 
    // larger the the number of arguments in order to avoid
    // malloc.
    char * file_list[argc];
    if(argc == 2) {
        file_list[0]="stdin";
        file_list[1]=NULL;
    }
    else
    {
        for( int i = 2; i < argc; i++ ) {
            file_list[i-2]=argv[i];
        }
        file_list[argc-2]=NULL;
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
        while ((nread = getline(&line, &len, stdin)) != -1) {
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
                        // printf("%c,%c,%d\n",line[i],pattern[char_matched_count-1],i);
                        line_matched=true;
                        break;
                    }
                }
                else
                {
                    char_matched_count=0;
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
