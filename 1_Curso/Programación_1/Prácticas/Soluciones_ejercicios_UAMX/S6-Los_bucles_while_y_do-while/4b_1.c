#include <stdio.h>

#define SALTOS 25

int main ()
{
    int i, num, clave;

    printf ("Teclea la clave: ");
    scanf ("%d", &clave);

    i=0;

    while(i<SALTOS)
    {
        printf("\n");
        i++;
    }

    printf ("Adivina un numero entre 1 y 99: ");
    scanf ("%d", &num);

    while (num != clave)
    {
        printf ("Ese no es el numero. Prueba otra vez: ");
        scanf ("%d", &num);
    }

    printf ("Numero correcto.\n");

    return 0;
}