#include "function.h"



int main(int argc, char *argv[]){
    int i,k,nElem,nSubSet;
    int index, maxInd, uncoverd;
    char *matrix;
    short int* subSetSize;
    int *res,wCount=0;
    int count=0;

    char *arg2="x";

    init(&nElem,&nSubSet,arg2);
    uncoverd=nElem;
    printf("%i\n",nElem);
    printf("%i\n",nSubSet);

    subSetSize = (short int*) malloc (nSubSet * sizeof(short int));
    readSubSetSize(subSetSize,nSubSet);
    if (nElem<21) printSubSetSize(subSetSize,nSubSet);

    matrix = (char*) malloc(nElem*nSubSet*sizeof(char));
    readMatrix(matrix,nElem,nSubSet);
    if (nElem<21) printMatrix(matrix,nElem,nSubSet);

    maxInd=findMax(subSetSize,nSubSet);

    res = (int*) calloc(nSubSet,sizeof(int));
    res[wCount]=maxInd;
    while(uncoverd>0){
        wCount++;
        
        subSetSize[maxInd]=0;
        for (i=0;i<nElem;i++){
            count++;
            index = i*nSubSet+maxInd;
            if(matrix[index]==1){
                //printf("%i:%i\n",i,matrix[index]);
                matrix[index]=0;
                uncoverd--;
                for(k=0;k<nSubSet;k++){
                    count++;
                    if(matrix[i*nSubSet+k]==1){
                        matrix[i*nSubSet+k]=0;
                        subSetSize[k]--;
                    }
                    
                }
               
            }
            
                
        }
        subSetSize[maxInd]=0;
        maxInd=findMax(subSetSize,nSubSet);
        res[wCount]=maxInd;

        //printSubSetSize(subSetSize,nSubSet);
        //printMatrix(matrix,nElem,nSubSet);
    }
    //printMatrix(matrix,nElem,nSubSet);
    for(i=0;i<nSubSet;i++){
        if(res[i]>0)
            printf("%i\t",res[i]);
        else {
            printf("\n");
            break;
        }
    }
    printf("%i\t%i\n",wCount,count);


    return 0;
}