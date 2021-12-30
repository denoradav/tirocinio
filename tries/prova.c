#include <stdio.h>
#include <stdlib.h>

int findMax(short int *subSetSize,short int nSubSet){
    int i,maxInd=0;
    for (i=0;i<nSubSet;i++){
        if (subSetSize[maxInd]<subSetSize[i])
            maxInd=i;
    }
    //printf("%i\n",maxInd);
    return maxInd;
}

short int nElem,nSubSet;
short int *size; //dimensioni dei sottoisiemi
char *sets,*subSet;
char list[]="010001110100001";
int maxInd;



int main(){

    nElem=5;
    nSubSet=3;
    size = (short int*) malloc (nSubSet * sizeof(short int));
    sets = (char*) malloc(6 * sizeof(char));
    subSet = (char*) malloc(6 * sizeof(char));
    size[0]=2;
    size[1]=2;
    size[2]=3;
    maxInd = findMax(size,nSubSet);
   
    printf("maxInd: %i\n",maxInd);
   
   
   
   
   
    return 0;
}


