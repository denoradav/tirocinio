#include <time.h>
#include <math.h>
#include "function.h"
#include <glpk.h>
//costanti


//variabili
int attempts;
int ko=false;
int nSubSet, nElem , nRand;
int upper, lower;
int isUnion=false;
int *arr,*lenArr;




//prototipi di funzione

void setInit(char *argv1);

void setGen();
void rowGen(int startVal);
void writeOnfile(char* arg2);



int main (int argc, char *argv[]){
    printf("%i \n",argc);
    attempts=0;
    if (argc==3){
        strcpy(arg1, argv[1]);
        strcpy(arg2, argv[2]);
        //strcpy(dest, src);
        //*arg1=*argv[1];
        //*arg2=*argv[2];
    }
    printf("%s \n",arg1);
    printf("%s \n",arg2);
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
    upper = floor (nElem /2);
    lower = floor (nElem/4);
    if (lower<=2) lower=3;
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
///programma lineare
    glp_prob *lp;
    int *ra, *ca;
    double *ar, z, *x;
    char alpha[]="0abcdefghilmnopqrstuvz";
    char letter[] ="a";

    //inizializzo le variabili
    ra = (int*) calloc (nElem*nSubSet+1,sizeof(int));
    ca = (int*) calloc (nElem*nSubSet+1,sizeof(int));

    ar= (double*) calloc (nElem*nSubSet+1,sizeof(double));
    x= (double*) calloc (nSubSet,sizeof(double));

    //inizializzo la variabile lp
    lp = glp_create_prob();
    glp_set_prob_name(lp,fName);
    glp_set_obj_dir(lp,GLP_MIN);
    glp_add_rows(lp, nElem);

    for(i=1;i<=nElem;i++){
        //substring(letter,alpha,i,1);
        //printf("%s\n",letter);
        //glp_set_row_name(lp, i,letter);
        glp_set_row_bnds(lp, i, GLP_LO, 1.0, 1.0); 
    }

    glp_add_cols(lp, nSubSet);
    for (i=1;i<=nSubSet;i++){
        //glp_set_col_name(lp, i, "x1");
        glp_set_col_bnds(lp, i, GLP_DB, 0.0, 1.0);
        glp_set_obj_coef(lp, i, 1.0);
    }
    

    printf("###programma lineare\n");

    for(i=0;i<nElem;i++){


        for(k=0;k<nSubSet;k++){
            index = i*nSubSet+k;
            ra[index+1]=i+1;
            ca[index+1]=k+1;
            ar[index+1]=arr[index];

            printf("%2i,%2i|%i\t",ra[index],ca[index],arr[index]);
        }
        printf("\n");
        
    }
    glp_load_matrix(lp, nElem*nSubSet, ra, ca, ar);
    glp_simplex(lp, NULL);
    z = glp_get_obj_val(lp);
    for (i=1;i<=nSubSet;i++){
       x[i-1]= glp_get_col_prim(lp, i);
       printf("%i)%f\n",i,x[i-1]);
       fprintf(fp,"%f\n",x[i-1]);
    }
   
    //chiudo il file;
    fclose(fp);
 }