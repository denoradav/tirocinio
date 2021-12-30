#include <stdio.h>
#include <string.h>

void splitStr(char *str){
    char *rest; // to point to the rest of the string after token extraction.
    char *token; // to point to the actual token returned.
    char *ptr = str; // make q point to start of hello.

    // loop till strtok_r returns NULL.
    while(token = strtok_r(ptr, ",", &rest)) {
        printf("%s\n", token); // print the token returned.
        ptr = rest; // rest contains the left over part..assign it to ptr...and start tokenizing again.    
    }
}

int main(void) {
    char hello[] = "1,2,3,9"; // make this a char array not a pointer to literal.
    splitStr("1,2,3,9");
    
}