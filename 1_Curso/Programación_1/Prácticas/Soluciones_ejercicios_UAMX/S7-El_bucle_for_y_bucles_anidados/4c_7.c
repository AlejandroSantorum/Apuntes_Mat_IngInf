#include <stdio.h> 

int main()
{
    int i, j, a, r, n, potencia, serie=0;

    printf("Introduce el primer término de la serie: ");
    scanf("%d", &a);

    printf("Introduce la razón de la serie: ");
    scanf("%d", &r);

    printf("Introduce el número de términos que deseas sumar: ");
    scanf("%d", &n);

    for(i=0; i<n; i++)
    {
        for(j=0, potencia=1; j<i; j++)
            potencia*=r;
        serie+=a*potencia;
    }

    printf("El valor de la serie de primer término %d, con razón %d y %d términos es: %d", a, r, n, serie);

    return 0;
}