#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main ()
{
    char buf[] ="1;3;8;11;12;13;18;19;20;";
    int i = 0;
    char *p;
    int *set,len;

    for (i=0;i<len;i++){
        printf("%i\t",buf[i]);
    }

    printf("\n%i\n",len);
    i=0;
    p = strtok(buf,";");
    while (p != NULL)
    {   
        p = strtok (NULL, ";");
        i++;
    }
    printf("%i\n",i);
    set = (int*) malloc(i*sizeof(int));
    len=i;
    i=0;
    p = strtok(buf,";");
    while (p != NULL)
    {
        set[i++]=atoi(p);
        p = strtok (NULL, ";");
    }

    for (i=0;i<len;i++){
        printf("%i\n",set[i]);
    }

    return 0;
}

