#include <stdio.h>

int main () 
{
    int i, veces, tabla[10] = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};

    printf("¿Cuántos elementos quieres mostrar por pantalla? Elige un número entre 1 y 10: ");
    scanf("%d", &veces);

    i=0;
    while (i<veces)
    {
        printf("%d ", tabla[i]);
        i++;
    }

    return 0;
}