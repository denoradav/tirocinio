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

char* setFileName(char* arg2){
    int len = strlen(arg2)+13;
    fName = (char*) malloc (len * sizeof(char));
    strcat(fName,baseName);
    strcat(fName,arg2);
    strcat(fName,".txt");
    //printf("%i\n",len);
    return fName;
}