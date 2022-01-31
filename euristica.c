#include "function.h"
short nElem;
short nSubSet;
short *matrix;
//in y memorizzo quanti elementi contiene ciascun insieme
short *y;

//cordinate
int cord[2]={-1,-1};

//prototipi di funzione
void cToZero(int col);
void init();
void find1();
void rToZero(int row);


int main (int argc, char *argv[]){
    int i,k;

    strcpy(arg1, "10.1");
    //short maxInd;
    if (argc==2){
        strcpy(arg1, argv[1]);
        strcpy(arg2, argv[1]);    
    }

    init();

    printMatrix(matrix,nElem,nSubSet);

    find1();
    //passo 1
    while(cord[1]>-1){
        printf("(%i,%i)\n",cord[0],cord[1]);
        printf("Aggiungo il sottinsieme %i alla soluzione\n",cord[1]);
        cToZero(cord[1]);
        find1();
        printMatrix(matrix,nElem,nSubSet);
    }

    //passo 2
    short *sum;
    sum = (short*) malloc(sizeof(short)*nSubSet);    

    for (i=0;i<nElem-1;i++){
        //printf("i:%i\tk:",i);
        for (k=0;k<nSubSet;k++){
            //printf("%i ",k);
            sum[k];
        }
        nl();
    }






    
    

    return 0;
}


//funzioni
void cToZero(int col){
    int i;
    for(i=0;i<nElem;i++){
        if (matrix[i*nSubSet+col]==1) rToZero(i); 
        matrix[i*nSubSet+col]=0;
    }
}

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
    
    //memorizzo il numero di elementi in nElem
    fgets(line,256,fp);
    nElem = atoi(line);
    
    //memorizzo il numero di sottoinisiemi in nSubset
    fgets(line,256,fp);
    nSubSet = atoi(line);

    //alloco lo spazio per y
    y = (short*) malloc(nSubSet*sizeof(short));

    //leggo la riga con le cardinalità dei sottoinisiemi
    fgets(line,256,fp);
    
    //valorizzo y
    p=strtok(line,";");
    for(i=0;i<nSubSet;i++){
        y[i]=atoi(p);
        p=strtok(NULL,";");
        
    }

    //alloco lo spazio per matrix e la inzializzo a zero 
    matrix = (short*) calloc (nElem*nSubSet,sizeof(short));

    //leggo le righe e valorizzo gli elementi di matrix
    for(i=0;i<nSubSet;i++){
        fgets(line,256,fp);
        p=strtok(line,";");
        for(k=0;k<y[i];k++){
            matrix[atoi(p)*nSubSet+i]=1;
            p=strtok(NULL,";");        
        }
        //nl();
    }


}

//questa funzione restituisce la prima riga che contiene solo un 1
void find1(){

    int i,k;
    int app;
    for(i=0;i<nElem;i++){
        app=0;
        for(k=0;k<nSubSet;k++){
            app+=matrix[i*nSubSet+k];
            //printf("%i\t",app);
            if (matrix[i*nSubSet+k]==1) cord[1]=k;
            if (app>1) break;
        }
        //nl();
        if(app==1) {cord[0]=i;  return;}
    }
    cord[0]=-1; cord[1]=-1;
}

void rToZero(int row){
    int i;
    for (i=0;i<nSubSet;i++){
        matrix[row*nSubSet+i]=0;
    }
}