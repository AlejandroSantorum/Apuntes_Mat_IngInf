#include <stdio.h>

#define DIM 10

int main() 
{
    int i, num;
    double tabla [DIM];

    do
    {
        printf("¿Cuántos números quieres leer? (entre 2 y 10): ");
        scanf("%d", &num);

        if (num<2 || num>10)
            printf("Error, debes introducir un número entre 2 y 10\n");
    }while(num<2 || num>10);

    i=0;
    while(i<num)
    {
        printf("Introduce el número %d de %d: ", i+1, num);
        scanf("%lf", &tabla[i]);
        i++;
    }

    i=num-2;
    while(i>=0)
    {
        if(tabla[i]<tabla[num-1])
            printf("El número %.2lf es menor que el número %.2lf\n", tabla[i], tabla[num-1]);
        i--;
    }

    return 0;   
}