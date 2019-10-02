#include <stdio.h>
#include <math.h>

int esPrimo(int n)
{
    int i, resultado=1;
    
    for (i=2; i<=sqrt(n); i++)
    {
        if (n%i==0)
        {
            resultado=0;
            break;
        }
    }
    
    return resultado;
}

int main ()
{
    int num;
    
    do
    {
        printf("Intruduce un número entero positivo: ");
        scanf ("%d", &num);
    }while(num<=0);

    if (esPrimo(num))
        printf("El número %d es primo", num);
    else
        printf("El número %d no es primo", num);

    return 0;
}

/* Las variables num y n son dos variables independientes con un rango de acción distinto.
 * Cuando se produce en main la llama a la función esPrimo, el contenido de la variable num se transfiere a la variable n.
 * Al ser variables distintas (que sólo transfieren su contenido en un momento) pueden tener nombres distintos. 
 * Si cambia el nombre de una, este cambio sólo afecta al módulo (función esPrimo o main) donde se encuentra y no es necesario cambiar nada en el otro módulo. */