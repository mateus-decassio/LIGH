/*

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
char *source = "ESSE É UM EXEMPLO DE UMA STRING MAIOR";
char *destination;

destination = (char*) malloc (4*sizeof(char));



strncpy(destination, source+8, 4);

printf("destination = %c", destination[5]);
}



*/

#include <stdio.h>
#include <string.h>

int main() {
    char src[] = "----AAAAAAAAAAA";
    char dest[5] = { 0 }; // 4 chars + terminator *

    strncpy(dest, src+4, 4);
    
    printf("dest: %s\n", dest);

}