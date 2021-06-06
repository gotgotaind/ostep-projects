#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]) {
	int *i;
	i=(int *) malloc(sizeof(int));
	*i=440;
	// int j=*i;
	printf("i : %d\n",*i);
	return 0;
}
