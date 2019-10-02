#include <stdio.h>
#define DIM 20
 
int main ()
{
    int longitud;
    char cadena [DIM];
    char * p;

    printf ("Introduzca una cadena: ");
    scanf ("%s", cadena);

    for (longitud=0, p=cadena; *p; p++)
        longitud++;
 
    printf ("%s tiene %d caractere\n", cadena, longitud);

    return 0;
}