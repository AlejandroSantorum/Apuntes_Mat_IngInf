
/* Fíjate en que en esta solución la dimensión de la tabla debe ser 11 y no 10, como se hace habitualmente, pues se guarda el 0 que marca el final, como ocurre en las cadenas */

#include <stdio.h>

#define DIM 11

int main() 
{
    int i;
    int tabla [DIM];

    i = 0;
    do 
    {
        printf("Introduzca un número (0 para terminar): ");
        scanf("%d", &tabla[i]);
        i++;
    } while ((i<10) && (tabla[i-1] != 0));

    if (i == 1) 
        printf("No se ha introducido ningún número.\n");
    else
    {
        if (i == 10)
        {
            printf("Número máximo de números alcanzado. Continuando...\n");
            i--;
        }
        else
            i-=2;
            
        printf("Los números tecleados son: ");

        while (i >= 0) 
        {
            printf("%d ", tabla[i]);
            i--;
        }
    }
    
    return 0;
}