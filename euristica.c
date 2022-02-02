#include <math.h>
#include "function.h"

short nElem;
short nSubSet;
short *matrix; //in questa variabile memorizziamo la "matrice" dei coefficenti

short *y; //array che contiene il numero di elementi di ogni sottoinsieme
short *res;
short unos=0; //conto gli 1 della matrice
short *delRows,*delCols; //tengo traccia delle righe e delle colonne cancellate 

void prune();
void clearCol();
void clearRow();
void printMatrixEu(short* matrix,short rows,short cols);

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

    //alloco lo spazio per res, uso una calloc in modo da
    //inizializzare a 0, se il sottiniseme i appartiene alla
    //soluzione si porrà res[i]=1
    res = (short*) calloc(nSubSet,sizeof(short));


    //alloco lo spazio per matrix
    //usando la calloc tutti gli elementi sono 0
    matrix = (short*) calloc(nElem*nSubSet,sizeof(short));

    //alloco lo spazio per delRows e delCols
    //usando la calloc tutti gli elementi sono 0
    delRows = (short*) calloc(nElem,sizeof(short));
    delCols = (short*) calloc(nSubSet,sizeof(short));

    //leggo la riga con le cardinalità dei sottoinisiemi
    fgets(line,256,fp);
    
    //valorizzo y
    p=strtok(line,";");
    for(i=0;i<nSubSet;i++){
        y[i]=atoi(p);
        unos+=y[i];
        p=strtok(NULL,";");
        
    }

    //leggo le righe e valorizzo gli elementi di matrix
    for(i=0;i<nSubSet;i++){
        fgets(line,256,fp);
        p=strtok(line,";");
        for(k=0;k<y[i];k++){
            //printf("%i:%i\t",i,k);
            matrix[atoi(p)*nSubSet+i]=1;
            
            //matrix[i*nElem+k]=atoi(p)+1;
            p=strtok(NULL,";");        
        }
        //nl();
    }
}

int main (int argc, char *argv[]){
    int i,k,j; //indici
    int nOfOne,posOfOne;
    int cont = false;
    int dominant = true;
    int sum = 0;
    strcpy(arg1, "10.2");
    
    if (argc==2){
        strcpy(arg1, argv[1]);
        strcpy(arg2, argv[1]);    
    }
    init();
    printMatrixEu(matrix,nElem, nSubSet);
    printf("Unos %i\n",unos);
    do
    {
        cont=false;

        //passo 1 - cerchiamo righe con solo un 1
        for(i=0;i<nElem;i++){
            if (delRows[i]==0){
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
                    printMatrixEu(matrix,nElem, nSubSet);
                    break;
                }
            }
        }    
        //passo 2 - cerchiamo una riga che ne domina un altra
        for (i=0;i<nElem;i++){
            dominant=true;
            sum=0;
            for(k=i+1;k<nElem;k++){
                //printf("confronto riga %i con riga %i\n",i,k);
                for(j=0;j<nSubSet;j++){
                    sum +=matrix[k*nSubSet+j];
                    dominant = dominant && (matrix[i*nSubSet+j]>=matrix[k*nSubSet+j]);
                    if (!dominant) break;
                }
                dominant = dominant && sum>0;
                if (dominant) {
                    printf("la linea %i domina %i, la cancello \n",i,k);
                    clearRow(i);
                    printMatrixEu(matrix,nElem,nSubSet);
                    cont = true;
                    
                    break;
                }
            }
            //if (dominant) break;
        }

        //passo 2b - cerchiamo una riga che ne domina un altra dal basso all'alto
        for (i=nElem-1;i>=0;i--){
            dominant=true;
            sum=0;
            for(k=i-1;k>=0;k--){
                //printf("confronto riga %i con riga %i\n",i,k);
                for(j=0;j<nSubSet;j++){
                    sum +=matrix[k*nSubSet+j];
                    dominant = dominant && (matrix[i*nSubSet+j]>=matrix[k*nSubSet+j]);
                    if (!dominant) break;
                }
                dominant = dominant && sum>0;
                if (dominant) {
                    printf("la linea %i domina %i, la cancello \n",i,k);
                    clearRow(i);
                    printMatrixEu(matrix,nElem,nSubSet);
                    cont = true;
                    
                    break;
                }
            }
            //if (dominant) break;
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
                    clearCol(i);
                    printf("la colonna %i è dominata da %i, la cancello \n",i,k);
                    printMatrixEu(matrix,nElem,nSubSet);
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
                    clearCol(i);
                    printf("la colonna %i è dominata da %i, la cancello \n",i,k);
                    printMatrixEu(matrix,nElem,nSubSet);
                    cont = true;
                    
                    break;
                }
            }
            if (dominant) break;
        }

    } while (cont);
    printf("Unos %i\n",unos);
    printf("\nRisultato:\n");
    for(i=0;i<nSubSet;i++) printf("%i\t",res[i]);
    nl();

    
}

void clearCol(int col){
    int i;
    delCols[col]=1;
    for (i=0;i<nElem;i++)
        if(matrix[i*nSubSet+col]==1){
            unos--;
            matrix[i*nSubSet+col]=0;
        }
        
}

void clearRow(int row){
    int i;
    delRows[row]=1;
    for (i=0;i<nSubSet;i++)
        if(matrix[row*nSubSet+i]==1){
            unos--;
            matrix[row*nSubSet+i]=0;
        }
        
}

void printMatrixEu(short* matrix,short rows,short cols){
    int i,k;
    for (i=0;i<nSubSet;i++)
        if(delCols[i]==0) printf("\t%i",i);
    nl();
    for (i=0;i<rows;i++){
        if (delRows[i]==0){
            printf("%i\t",i);
            for(k=0;k<cols;k++){
                if (delCols[k]==0)
                    printf("%i\t",matrix[i*cols+k]);
            }
            nl();
        }
    }
}

void prune(int line, int col){
    int i;
    delCols[col]=1;
    //matrix[line*nSubSet+col]=0;
    for (i=0;i<nElem;i++){
        if (matrix[i*nSubSet+col]==1) clearRow(i);
    }
}