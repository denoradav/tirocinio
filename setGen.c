#include <time.h>
#include <math.h>
#include "function.h"
//costanti


//variabili
int attempts;
int ko=false;
int nSubSet, nElem , nRand;
int upper, lower;
int isUnion=false;
int *arr,*lenArr;

char arg1[]="10";
char arg2[]="10.1";


//prototipi di funzione

void setInit(char *argv1);

void setGen();
void rowGen(int startVal);
void writeOnfile(char* arg2);



int main (int argc, char *argv[]){
    attempts=0;
    if (argc==3){
        *arg1=*argv[1];
        *arg2=*argv[2];
    }
    setInit(arg1);
    ;
    do
    {
        setGen();
        writeOnfile(arg2);
    } while (!ko);
    
   
    
    printf("attempts: %d\n",attempts);
    

}

//FUNZIONI


void setInit(char *argv1){
    // Use l'ora corrente come 
    // seed del genearotre di numeri causali
    srand(time(0));
     //genero un numero casuale di sottoinsiemi 
    nElem = atoi(argv1);
    if (nElem<5) nElem=5;
    upper = nElem -2;
    lower = floor (nElem/4);
    if (lower<=2) lower=3;
    nSubSet = (rand() % (upper - lower + 1)) + lower;
    arr = (int*) malloc(sizeof(int)* nElem * nSubSet);
    
}



void rowGen(int startVal){
    int i,chkVal, nRand;
    
    

    chkVal = 0;
    attempts++;
    //printf("startVal:%i \n",startVal);
    //printf("nSubSets:%i \n",nSubSets);
    //printf("attepts:%i \n", attempts);
    //popolo casualmente i vari sottoinsiemi
    for (i=0;i<nSubSet;i++){
        nRand = rand() % 3;
        arr[i+startVal]=0;
        if (nRand==1) {
            arr[i+startVal]=1;   
            chkVal++;
        }
        //printf("%i\t",arr[i+startVal]);
    }
    //printf("%i\n",chkVal);
    if (chkVal==0) rowGen(startVal);
    
}

void setGen(){
    
    for (int i=0;i<nElem;i++){
        rowGen(i*nSubSet);
    }
}

void writeOnfile(char* arg2){
    int index,i,k,subSetElem;
    FILE *fp=NULL;
    fName = setFileName(arg2);

    //apro il file in scrittura   
    fp = fopen(fName,"w");
    //scrivo il numero di elementi dell'insieme
    fprintf (fp, "%d\n", nElem);
    printf ("# elementi dell'insieme %d\n", nElem);
    fprintf(fp,"%d\n",nSubSet);
    printf("# sottoinsiemi %d\n",nSubSet);
    for(i=0;i<nSubSet;i++){
        subSetElem=0;
        for (k=0;k<nSubSet*nElem;k=k+nSubSet){
            index= i+k;
            if(arr[index]==1) subSetElem++;
        }
        if (subSetElem==0){
            ko=true;
        }

        printf("%i;",subSetElem);
        fprintf(fp,"%i;",subSetElem);
    }
    printf("\n");
    fprintf(fp,"\n");
    for(i=0;i<nSubSet;i++){
        for(k=0;k<nElem;k++){
            index = k*nSubSet+i;
            if(arr[index]==1){
                printf("%i\t",k);
                fprintf(fp,"%i;",k);
            }
            
        }
        printf("\n");
        fprintf(fp,"\n");
    }
    /*for(i=0; i<nElem * nSubSet; i++){
        if(arr[i]==1){
            printf("%i\t",i%nSubSet);
            fprintf(fp,"%i;",i%nSubSet);0
        }
        if ((i+1)%nSubSet==0){
            printf("\n");
            fprintf(fp,"\n");
        }
    }
    */
    /*
    printf("# elementi dei sottoinsiemi:");
    for(i=0;i<nSubSet;i++){
        subSetElem=0;
        for (k=0;k<nSubSet*nElem;k=k+nSubSet){
            index= i+k;
            if(arr[index]==1) subSetElem++;
        }
        printf("%i;",subSetElem);
        fprintf(fp,"%i;",subSetElem);
    }
    printf("\n");
    fprintf(fp,"\n");
    
    for(i=0;i<nSubSet;i++){
        printf("sottoinsieme %i: ",i+1);
        for (k=0;k<nSubSet*nElem;k=k+nSubSet){
            index= i+k;
            if(arr[index]==1) {
                printf("%i;",k/nSubSet+1);
                fprintf(fp,"%i;",k/nSubSet+1);
            }
        }
        printf("\n");
        fprintf(fp,"\n");
    } 
    */  
    //chiudo il file;
    fclose(fp);
 }