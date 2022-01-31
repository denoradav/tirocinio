<<<<<<< HEAD
#include <math.h>
#include "function.h"

short nElem;
short nSubSet;
short *matrix; //in questa variabile memorizziamo la "matrice" dei coefficenti

short *y; //array che contiene il numero di elementi di ogni sottoinsieme
short *res;

void prune();
void clearLine();
void clearRow();
=======
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
>>>>>>> afae7d229c3e91e5e4fbd438c2361d5f6ff0b487

void init(){
    char line[256];
    char *p;
    int i,k; //indici per i cilci;
    FILE *fp=NULL;
    
    //genero il nome del file da aprire
    fName=setFileName(arg1);
<<<<<<< HEAD
    //apro il file
    fp = fopen(fName,"r");
=======
    
    //apro il file
    fp = fopen(fName,"r");
    
>>>>>>> afae7d229c3e91e5e4fbd438c2361d5f6ff0b487
    //se non si può aprire esco
    if (fp==NULL){
        exit(1);
    }
<<<<<<< HEAD
    //memorizzo il numero di elementi
    fgets(line,256,fp);
    nElem = atoi(line);

    //memorizzo il numero di sottoinisiemi 
    fgets(line,256,fp);
    nSubSet = atoi(line);

    //alloco lo spazio per y    
    y = (short*) malloc(nSubSet*sizeof(short));

    //alloco lo spazio per res, uso una calloc in modo da
    //inizializzare a 0, se il sottiniseme i appartiene alla
    //soluzione si porrà res[i]=1
    res = (short*) calloc(nSubSet,sizeof(short));

    //alloco lo spazio per matrix
    //usando la calloc tutti gli elementi sono 0
    matrix = (short*) calloc(nElem*nSubSet,sizeof(short));

=======
    
    //memorizzo il numero di elementi in nElem
    fgets(line,256,fp);
    nElem = atoi(line);
    
    //memorizzo il numero di sottoinisiemi in nSubset
    fgets(line,256,fp);
    nSubSet = atoi(line);

    //alloco lo spazio per y
    y = (short*) malloc(nSubSet*sizeof(short));

>>>>>>> afae7d229c3e91e5e4fbd438c2361d5f6ff0b487
    //leggo la riga con le cardinalità dei sottoinisiemi
    fgets(line,256,fp);
    
    //valorizzo y
    p=strtok(line,";");
    for(i=0;i<nSubSet;i++){
        y[i]=atoi(p);
        p=strtok(NULL,";");
        
    }

<<<<<<< HEAD
=======
    //alloco lo spazio per matrix e la inzializzo a zero 
    matrix = (short*) calloc (nElem*nSubSet,sizeof(short));

>>>>>>> afae7d229c3e91e5e4fbd438c2361d5f6ff0b487
    //leggo le righe e valorizzo gli elementi di matrix
    for(i=0;i<nSubSet;i++){
        fgets(line,256,fp);
        p=strtok(line,";");
        for(k=0;k<y[i];k++){
<<<<<<< HEAD
            //printf("%i:%i\t",i,k);
            matrix[atoi(p)*nSubSet+i]=1;
            //matrix[i*nElem+k]=atoi(p)+1;
=======
            matrix[atoi(p)*nSubSet+i]=1;
>>>>>>> afae7d229c3e91e5e4fbd438c2361d5f6ff0b487
            p=strtok(NULL,";");        
        }
        //nl();
    }
<<<<<<< HEAD
}

int main (int argc, char *argv[]){
    int i,k,j; //indici
    int nOfOne,posOfOne;
    int cont = false;
    int dominant = true;
    int sum = 0;
    strcpy(arg1, "10.1");
    
    if (argc==2){
        strcpy(arg1, argv[1]);
        strcpy(arg2, argv[1]);    
    }
    init();
    printMatrix(matrix,nElem, nSubSet);

    do
    {
        cont=false;

        //passo 1 - cerchiamo righe con solo un 1
        for(i=0;i<nElem;i++){
            nOfOne=0;
            for(k=0;k<nSubSet;k++){
                if (matrix[i*nSubSet+k]==1){
                    nOfOne++;
                    posOfOne=k;
                }
                
                
            }
            if (nOfOne==1) {
                res[posOfOne]=1;
                printf("la linea %i ha un solo 1 in posizione %i\n",i,posOfOne);
                prune(i,posOfOne);
                cont = true;
                printMatrix(matrix,nElem, nSubSet);
                break;
            }
        }

        //passo 2 - cerchiamo una riga che ne domina un altra
        for (i=0;i<nElem;i++){
            dominant=true;
            sum=0;
            for(k=i+1;k<nElem;k++){
                for(j=0;j<nSubSet;j++){
                    sum +=matrix[k*nSubSet+j];
                    dominant = dominant && (matrix[i*nSubSet+j]>=matrix[k*nSubSet+j]);
                    if (!dominant) break;
                }
                dominant = dominant && sum>0;
                if (dominant) {
                    printf("la linea %i domina %i, la cancello \n",i,k);
                    clearLine(i);
                    printMatrix(matrix,nElem,nSubSet);
                    cont = true;
                    
                    break;
                }
            }
            if (dominant) break;
        }

        //passo 2b - cerchiamo una riga che ne domina un altra dal basso all'alto
        for (i=nElem-1;i>=0;i--){
            dominant=true;
            sum=0;
            for(k=i-1;k>=0;k--){
                for(j=0;j<nSubSet;j++){
                    sum +=matrix[k*nSubSet+j];
                    dominant = dominant && (matrix[i*nSubSet+j]>=matrix[k*nSubSet+j]);
                    if (!dominant) break;
                }
                dominant = dominant && sum>0;
                if (dominant) {
                    printf("la linea %i domina %i, la cancello \n",i,k);
                    clearLine(i);
                    printMatrix(matrix,nElem,nSubSet);
                    cont = true;
                    
                    break;
                }
            }
            if (dominant) break;
        }

        //passo 3 - cerchiamo una colonna che è dominata da un altra 
        for (i=0;i<nSubSet;i++){
            dominant=true;
            sum=0;
            for(k=i+1;k<nSubSet;k++){
                for(j=0;j<nElem;j++){
                    sum +=matrix[j*nSubSet+i];
                    dominant = dominant && (matrix[j*nSubSet+i]<=matrix[j*nSubSet+k]);
                    //printf("%i <= %i\t",matrix[j*nSubSet+i],matrix[j*nSubSet+k]); 
                    if (!dominant) break;
                }
                dominant = dominant && sum>0;
                if (dominant) {
                    clearRow(i);
                    printf("la colonna %i è dominata da %i, la cancello \n",i,k);
                    printMatrix(matrix,nElem,nSubSet);
                    cont = true;
                    
                    break;
                }
            }
            if (dominant) break;
        }

        //passo 3b - cerchiamo una colonna che è dominata da un altra da sx a dx
        for (i=nSubSet-1;i>=0;i--){
            dominant=true;
            sum=0;
            for(k=i-1;k>=0;k--){
                for(j=0;j<nElem;j++){
                    sum +=matrix[j*nSubSet+i];
                    dominant = dominant && (matrix[j*nSubSet+i]<=matrix[j*nSubSet+k]);
                    //printf("%i <= %i\t",matrix[j*nSubSet+i],matrix[j*nSubSet+k]); 
                    if (!dominant) break;
                }
                dominant = dominant && sum>0;
                if (dominant) {
                    clearRow(i);
                    printf("la colonna %i è dominata da %i, la cancello \n",i,k);
                    printMatrix(matrix,nElem,nSubSet);
                    cont = true;
                    
                    break;
                }
            }
            if (dominant) break;
        }

    } while (cont);
    printf("\nRisultato:\n");
    for(i=0;i<nSubSet;i++) printf("%i\t",res[i]);
    nl();

    
}

void clearLine(int line){
    int i;
    for (i=0;i<nSubSet;i++)
        matrix[line*nSubSet+i]=0;
}

void clearRow(int row){
    int i;
    for (i=0;i<nElem;i++)
        matrix[i*nSubSet+row]=0;
}

void prune(int line, int col){
    int i;
    //matrix[line*nSubSet+col]=0;
    for (i=0;i<nElem;i++){
        if (matrix[i*nSubSet+col]==1) clearLine(i);
=======


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
>>>>>>> afae7d229c3e91e5e4fbd438c2361d5f6ff0b487
    }
}