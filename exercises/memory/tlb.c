
int PAGESIZE=1024*4;
int jump = PAGESIZE / sizeof(int);

int NUMPAGES=4;

int a[NUMPAGES*PAGESIZE / sizeof(int)];

for(i=0; i<NUMPAGES; i+=jump) {
    a[i]+=1;
}