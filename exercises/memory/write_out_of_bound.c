#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char* argv[]) {
	int *i;
	i=(int *) malloc(100*sizeof(int));
	i[0]=440;
	i[100]=0;
	// int j=*i;
	free(i+50);
	printf("i[0] : %d\n",i[0]);
	
	return 0;
}
