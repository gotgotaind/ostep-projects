#include <unistd.h>
#include <stdio.h>

int main(int argc,char* argv[]) {
	int *i;
	i=NULL;
	int j=*i;
	printf("j : %d\n",j);
}
