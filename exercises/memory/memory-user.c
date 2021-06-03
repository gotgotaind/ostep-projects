#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>

void usage() {
    printf("usage : memory-user \"size in mega bytes\" \"timeout in seconds\"\n");
    exit(EXIT_FAILURE);
}

long parse_string_to_long(char str[]) {
    int base=10;
    char *endptr;
    long val;

    errno = 0;    /* To distinguish success/failure after call */
    val = strtol(str, &endptr, base);

   /* Check for various possible errors */

   if ((errno == ERANGE && (val == LONG_MAX || val == LONG_MIN))
            || (errno != 0 && val == 0)) {
        perror("strtol");
        usage();
        exit(EXIT_FAILURE);
    }

   if (endptr == str) {
        fprintf(stderr, "No digits were found\n");
        usage();
        exit(EXIT_FAILURE);
    }
    return val;
}
int main(int argc, char** argv) {
    if( argc != 3 ) {
        usage();
    }

    long MB=parse_string_to_long(argv[1]);
    printf("Will allocate %ld MB\n",MB);
    long timeout=parse_string_to_long(argv[2]);
    printf("Will timeout after %ld seconds\n",timeout);

}
