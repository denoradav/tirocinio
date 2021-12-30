#include <stdio.h>
#include <stdlib.h>
#include <string.h>


const int false=0;
const int true =1;

const char* baseName="sets/gSet";
char* fName=NULL;


char* setFileName(char* arg2){
    int len = strlen(arg2)+13;
    fName = (char*) malloc (len * sizeof(char));
    strcat(fName,baseName);
    strcat(fName,arg2);
    strcat(fName,".txt");
    printf("%i\n",len);
    return fName;
}