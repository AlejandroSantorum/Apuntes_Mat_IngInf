#include <stdio.h>

#define LIMITE 10

int main()
{
    int i, suma, numero, negativos;

    for(i=suma=negativos=0; i<LIMITE; i++)
    {
        printf("Introduce un número: ");
        scanf("%d", &numero);

        if (numero==0)
            break;
        else if (numero>0)
            suma+=numero;
        else
            negativos++;
    }

    printf("Se han leído un total de %d números, de los cuales %d eran negativos\n", i, negativos);
    printf("La suma de los d valores positivos leídos es: %d", suma);

    return 0;

}