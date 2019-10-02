
#include <stdio.h>

#define DIM 30

int main () 
{
    int i, j;
    char caracterm, caracterM, cadena[DIM];

    printf("Introduce una cadena de caracteres en minúsculas: ");
    scanf("%s", cadena);

    do
    {
        printf("Introduce un carácter en minúsculas: ");
        scanf("\n%c", &caracterm);

        if (caracterm < 'a' || caracterm > 'z')
            printf("Error, el carácter tiene que estar comprendido entre a y z\n");
    }while(caracterm < 'a' || caracterm > 'z');

    do
    {
        printf("Introduce un carácter en mayúsculas: ");
        scanf("\n%c", &caracterM);

        if (caracterM < 'A' || caracterM > 'Z')
            printf("Error, el carácter tiene que estar comprendido entre A y Z\n");
    }while(caracterM < 'A' || caracterM >'Z');

    i=0;
    while(cadena[i]!=0)
    {
        if (cadena[i] == caracterm)
            cadena[i]=caracterM;

        i++;
    }

    printf("%s\n", cadena);

    j=i-1;
    while (j>=0)
    {
        printf("%c", cadena[j]);
        j--;
    }
    
    return 0;
}