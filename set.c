#include "function.h"

short nElem;
short nSubset;

short nOfX,nOfY;

/*
le variabili che iniziano con x sono relative agli elementi dei sottoinsiemi
    y       -> contiene il numero di elementi di ogni sottoinsieme
    xList   -> contiene un la lista degli elementi di ciascun sottoinsieme
    xPos    -> contiene la posizione dove in inizia in yList la lista degli elementi di un sottoinsieme
*/

short *y,*yList,*yPos;
/*
le variabili che iniziano con x sono relative agli elementi dell'insieme
    x       -> contiene il numero di sottoinisemi in cui appare un elemento dell'insieme
    xList   -> contiene un la lista dei sottoinsiemi a cui appartengono gli elementi dell'insieme
    xPos    -> contiene la posizione dove in inizia in xList la lista dei sottoinsiemi di un elemento
*/
short *x,*xList,*xPos;





void fromXtoY(){
    int i,k,w;
    nOfX=nOfY;
    printf("%i\n",nOfX);
    //alloco spazio in memoria per x e xPos
    x =(short*) calloc(nElem , sizeof(short));
    xPos = (short*) malloc(nElem * sizeof(short));

    //alloco spazio in memoria per xList
    xList = (short*) malloc (nOfX*sizeof(short));

    //for (i=0;i<nOfX;i++) x[i]=0; 
    for(i=0;i<nOfX;i++){
        x[yList[i]]++;        
    }
    nOfX=0;
    for (i=0;i<nElem;i++){
        xPos[i]=nOfX;
        nOfX+=x[i];
    }

    for (i=0;i<nSubset;i++){
        for(k=yPos[i];k<yPos[i]+y[i];k++){
            w=yList[k];
            xList[xPos[w]]=i;
            xPos[w]++;
        }
    }

    nl();

    nOfX=0;
    for (i=0;i<nElem;i++){
        xPos[i]=nOfX;
        nOfX+=x[i];
    }
}

void init(){
    int i,k;
    char line[256];
    char *p;
    FILE *fp=NULL;
    fName=setFileName(arg1);
    printf("%s \n",fName);
    

    fp = fopen(fName,"r");
    if (fp==NULL){
        exit(1);
    }
    //leggo la linea che contiene il numero di elementi e la salvo in nElem
    fgets(line,256,fp);
    nElem = atoi(line);

    //alloco lo spazio per x e xPos
    x =(short*) malloc(nElem * sizeof(short)); 
    xPos = (short*) malloc(nElem * sizeof(short));

    //leggo la linea che contiene il numero di sottoinsieme e la salvo in nSubSet
    fgets(line,256,fp);
    nSubset = atoi(line);

    //alloco lo spazio per y e yPos
    y = (short*) malloc(nSubset * sizeof(short));
    yPos = (short*) malloc(nSubset * sizeof(short));

    //leggo la linea che contiene il numero di elementi di ogni sottoinsieme 
    //e la salvo in y
    fgets(line,256,fp);
    p=strtok(line,";");
    nOfY=0;
    for(i=0;i<nSubset;i++){
        y[i]=atoi(p);
        yPos[i]=nOfY;
        nOfY+=y[i];  
        p=strtok(NULL,";");
    }

    //alloco lo spazio necessario ad yList
    yList = (short*) malloc (nOfY*sizeof(short));
    
    for(i=0;i<nSubset;i++){
        fgets(line,256,fp);
        p=strtok(line,";");
        for(k=yPos[i];k<yPos[i]+y[i];k++){
            yList[k]=atoi(p);
            p=strtok(NULL,";");        
        }
    }

    fclose(fp);

    fromXtoY();
}

void printElem(short index, short *xy, short *list, short *pos){
    int i;
    for (i=pos[index];i<pos[index]+xy[index];i++)
        printf("%i\t",list[i]);
    printf("\n");
}

void printY(){
    int i;
    for (i=0;i<nSubset;i++){
        printf("%i\t",y[i]);
    }
    nl();
}

void printYPos(){
    int i;
    for (i=0;i<nSubset;i++){
        printf("%i\t",yPos[i]);
    }
    nl();
}
void printX(){
    int i;
    for (i=0;i<nElem;i++){
        printf("%i\t",x[i]);
    }
    nl();
}

void printXPos(){
    int i;
    for (i=0;i<nElem;i++){
        printf("%i\t",xPos[i]);
    }
    nl();
}

short findMax(short *list,short nSubSet){
    int i,maxInd=0;
    for (i=0;i<nSubSet;i++){
        if (list[maxInd]<list[i])
            maxInd=i;
    }
    return maxInd;
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
    
    for(i=0;i<nSubset;i++) printElem(i,y,yList,yPos);
   
    uncovered=nElem;

    printf("%i:%i\n",nElem,uncovered);
    maxInd=findMax(y,nSubset);
    printY(nOfY);
    printf("%i\n",maxInd);

    while(uncovered>0){
        for (i=yPos[maxInd];i<y[maxInd]+yPos[maxInd];i++){
            uncovered--;
            printf("%i:\t",yList[i]);
            if (x[yList[i]]>1){
                for (k=xPos[yList[i]];k<xPos[yList[i]]+x[yList[i]];k++){
                    printf("%i:%i\t",k,xList[k]);
                    if (xList[k]!=maxInd) y[xList[k]]--;                   
                }
            } 
            nl();
        }
        nl();
        
        y[maxInd]=0;
        maxInd=findMax(y,nSubset);
        printY(nOfY);
        printf("%i\n",maxInd);
    }


    return 0;
}