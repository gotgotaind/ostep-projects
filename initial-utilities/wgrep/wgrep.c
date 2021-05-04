#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void grep(char *pattern, FILE *stream)
{
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;
    size_t pattern_length = strlen(pattern);

    if (stream == NULL)
    {
        printf("wgrep: cannot open file\n");
        // better error message, but the specs are to print as in previous line
        // printf("cannot open file %s : %s\n",fn,strerror(errno));
        exit(1);
    }

    int line_nb = 0;
    while ((nread = getline(&line, &len, stream)) != -1)
    {
        // printf("Retrieved line of length %zd:\n", nread);
        // fwrite(line, nread, 1, stdout);
        int char_matched_count = 0;
        bool line_matched = false;

        for (int i = 0; i < (nread); i++)
        {
            // fputc(line[i],stdout);
            // printf("%d,%c",i,line[i]);
            if (line[i] == pattern[char_matched_count])
            {
                char_matched_count++;
                if (char_matched_count == pattern_length)
                {
                    // printf("%c,%c,%d\n",line[i],pattern[char_matched_count-1],i);
                    line_matched = true;
                    break;
                }
            }
            else
            {
                char_matched_count = 0;
            }
        }
        // printf("%d\n",line_nb);
        if (line_matched)
        {
            // printf("%d:%s", line_nb + 1, line);
            printf("%s", line);
        }
        line_nb++;
    }
}

int main(int argc, char *argv[])
{
    FILE *stream;
    char *fn;

    // That's the spec
    if (argc == 1)
    {
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }

    char *pattern = argv[1];

    if( argc == 2 ) {
        grep(pattern,stdin);
    }
    else {
        int input_file_i = 2;
        while (argv[input_file_i] != NULL)
        {
            fn = argv[input_file_i];
            stream = fopen(fn, "r");
            grep(pattern,stream);
            input_file_i++;
        }
    }
    exit(0);
}
