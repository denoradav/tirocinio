#include <glpk.h>
#include "function.h"

short nElem;
short nSubSet;
short *matrix; //in questa variabile memorizziamo la "matrice" dei coefficenti
short nOfX,nOfY;

/*
le variabili che iniziano con y sono relative agli elementi dei sottoinsiemi
    y       -> contiene il numero di elementi di ogni sottoinsieme
    yList   -> contiene un la lista degli elementi di ciascun sottoinsieme
    yPos    -> contiene la posizione dove in inizia in yList la lista degli elementi di un sottoinsieme
*/

short *y,*yList,*yPos;

/*
le variabili che iniziano con x sono relative agli elementi dell'insieme
    x       -> contiene il numero di sottoinisemi in cui appare un elemento dell'insieme
    xList   -> contiene un la lista dei sottoinsiemi a cui appartengono gli elementi dell'insieme
    xPos    -> contiene la posizione dove in inizia in xList la lista dei sottoinsiemi di un elemento
*/
short *x,*xList,*xPos;



int init(){
    char line[256];
    char *p;
    int i,k; //indici per i cilci;
    FILE *fp=NULL;
    
    //genero il nome del file da aprire
    fName=setFileName(arg1);
    //apro il file
    fp = fopen(fName,"r");
    //se non si può aprire esco
    if (fp==NULL){
        exit(1);
    }

    fgets(line,256,fp);
    nElem = atoi(line);

    fgets(line,256,fp);
    nSubSet = atoi(line);

    //alloco lo spazio per y
    y = (short*) malloc(nSubSet*sizeof(short));

    //alloco lo spazio per matrix
    matrix = (short*) calloc(nElem*nSubSet,sizeof(short));

    
    //leggo la riga con le cardinalità dei sottoinisiemi
    fgets(line,256,fp);
    p=strtok(line,";");
    
    nOfY=0;
    for(i=0;i<nSubSet;i++){
        y[i]=atoi(p);
        p=strtok(NULL,";");
        
    }


    //leggo le righe e valorizzo gli elementi di matrix
    for(i=0;i<nSubSet;i++){
        fgets(line,256,fp);
        p=strtok(line,";");
        for(k=0;k<y[i];k++){
            //printf("%i:%i\t",i,k);
            matrix[atoi(p)*nSubSet+i]=1;
            p=strtok(NULL,";");        
        }
        //nl();
    }

    

    

    
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

int main (int argc, char *argv[]){
    int i,k;
    short uncovered=nElem;
    strcpy(arg1, "10.1");
    short maxInd;
    if (argc==2){
        strcpy(arg1, argv[1]);
        strcpy(arg2, argv[1]);    
    }
    init();
    printMatrix(matrix,nElem,nSubSet);
}