#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* baseName="sets/gSet";

const int false=0;
const int true =1;

char arg1[]="10   ";
char arg2[]="10.1 ";

char* fName=NULL;

void nl(){
    printf("\n");
}
void pi(int val){
    printf("%i\n",val);
}

void ps(char* str){
    printf("%s\n",str);
}

void printMatrix(short* matrix,short rows,short cols){
    int i,k;
    for (i=0;i<rows;i++){
        for(k=0;k<cols;k++){
            printf("%i\t",matrix[i*cols+k]);
        }
        nl();
    }
}

char* setFileName(char* arg2){
    int len = strlen(arg2)+13;
    fName = (char*) malloc (len * sizeof(char));
    strcat(fName,baseName);
    strcat(fName,arg2);
    strcat(fName,".txt");
    //printf("%i\n",len);
    return fName;
}

char* substring(char *destination, const char *source, int beg, int n)
{
    // extracts `n` characters from the source string starting from `beg` index
    // and copy them into the destination string
    while (n > 0)
    {
        *destination = *(source + beg);
 
        destination++;
        source++;
        n--;
    }
 
    // null terminate destination string
    *destination = '\0';
 
    // return the destination string
    return destination;
}