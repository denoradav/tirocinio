#include <math.h>
#include "function.h"

short nElem;
short nSubSet;
short *matrix; //in questa variabile memorizziamo la "matrice" dei coefficenti
double *lp; //in lp memorizziamo i valori ottenuti dalla risoluzione del 
            //problema lineare


/*
le variabili che iniziano con y sono relative agli elementi dei sottoinsiemi
    y       -> contiene il numero di elementi di ogni sottoinsieme
    yList   -> contiene un la lista degli elementi di ciascun sottoinsieme
    yPos    -> contiene la posizione dove in inizia in yList la lista degli elementi di un sottoinsieme
*/

short *y;
//,*yList,*yPos;

/*
le variabili che iniziano con x sono relative agli elementi dell'insieme
    x       -> contiene il numero di sottoinisemi in cui appare un elemento dell'insieme
    xList   -> contiene un la lista dei sottoinsiemi a cui appartengono gli elementi dell'insieme
    xPos    -> contiene la posizione dove in inizia in xList la lista dei sottoinsiemi di un elemento
*/
//short *x,*xList,*xPos;



void init(){
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
    //memorizzo il numero di elementi
    fgets(line,256,fp);
    nElem = atoi(line);
    
    //memorizzo il numero di sottoinisiemi 
    fgets(line,256,fp);
    nSubSet = atoi(line);

    //alloco lo spazio per y
    y = (short*) malloc(nSubSet*sizeof(short));

    //alloco lo spazio per lp
    lp = (double*) malloc(nSubSet*sizeof(double));

    //alloco lo spazio per matrix
    //usando la calloc tutti gli elementi sono 0
    matrix = (short*) calloc(nElem*nSubSet,sizeof(short));

    
    //leggo la riga con le cardinalità dei sottoinisiemi
    fgets(line,256,fp);
    
    //valorizzo y
    p=strtok(line,";");
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
            //matrix[atoi(p)*nSubSet+i]=1;
            matrix[i*nElem+k]=atoi(p)+1;
            p=strtok(NULL,";");        
        }
        //nl();
    }

    //valorizzo lp
    for(i=0;i<nSubSet;i++){
        fgets(line,256,fp);
        lp[i]=atof(line);
    }

    

    

    
}

double rand01(){
    return (double)rand() / (double)RAND_MAX ;
}


int main (int argc, char *argv[]){
    int i,k,index;
    double upper;
    short *unchosen;
    short uncovered;
    strcpy(arg1, "10.1");
    //short maxInd;
    if (argc==2){
        strcpy(arg1, argv[1]);
        strcpy(arg2, argv[1]);    
    }
    init();
    printMatrix(matrix,nSubSet, nElem);

    //inizializzo unchosen e inserisco in ogni cella il numero del suo indice  
    unchosen=(short*) malloc(nElem*sizeof(short)+1);
    for (i=1;i<=nElem;i++) unchosen[i]=i;

    for (i=0;i<nSubSet;i++){
        printf("%f\n",lp[i]);
    }

    for (i=1;i<=nElem;i++){
        printf("%i\t",unchosen[i]);
    }
    nl();

    upper=log(nElem)+4;

    uncovered=nElem;
    
    for(i=1;i<upper;i++){
        for (k=0;k<nSubSet;k++){
            if(lp[k]>=rand01()){
                printf("Scelgo il sottoinsieme S%i\n",k);
                index = k*nElem;
                printf("%i\t",index);
                while (matrix[index]>0){
                    //printf("%i\t",matrix[index]);
                    if (unchosen[matrix[index]]>0){
                        uncovered--;
                        //printf("unc|%i\t",uncovered);
                        unchosen[matrix[index]]=0;
                    }
                    index++;
                }
            }
            nl();
            if(uncovered<=0) break;
            for (i=1;i<=nElem;i++){
                printf("%i\t",unchosen[i]);
            }
            nl();
        }
        if(uncovered<=0) break;
    }
    nl();
   

    return 0;
}