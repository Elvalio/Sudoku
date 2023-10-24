#include <stdio.h>
#include <stdlib.h>

int main () {

    char lettre = 'C';

    // scanf("%c", &lettre);

    if (lettre >= 'A' && lettre <= 'I')
    {
        printf ("Lettre comprise entre A et I");
    }
    else 
    {
        printf("tg");
    }

    return EXIT_SUCCESS;
}