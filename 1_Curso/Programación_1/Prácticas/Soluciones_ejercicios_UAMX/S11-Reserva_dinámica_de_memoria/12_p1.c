#include <stdio.h>
#include <stdlib.h>

void comparaCadenas(char *cadena1, char *cadena2)
{
    int i, j, flag;

    for(i=0; cadena1[i]!=0; i++)
    {
        for(j=flag=0; cadena2[j]!=0; j++)
            if (cadena1[i]==cadena2[j])
                flag=1;

        if (flag)
            printf("El carácter %c aparece en la cadena %s\n", cadena1[i], cadena2);
        else
            printf("El carácter %c NO aparece en la cadena %s\n", cadena1[i], cadena2);
    }
}

int main()
{
    char * c1, * c2;
    int tam;

    printf("Introduce el tamaño máximo de las cadenas de caracteres: ");
    scanf("%d", &tam);

    c1 = (char *)malloc(tam*sizeof(char));
    if (c1 == NULL)
    {
        printf("Error, no se puede reservar memoria para la primera cadena");
        return 1;
    }

    c2 = (char *)malloc(tam*sizeof(char));
    if (c2 == NULL)
    {
        printf("Error, no se puede reservar memoria para la segunda cadena");
        free(c1); /* Antes de terminar el programa con return 1 hay que liberar la memoria reservada hasta el momento */
        return 1;
    }

    printf("Introduce una cadena: ");
    scanf("%s", c1);

    printf("Introduce otra cadena: ");
    scanf("%s", c2);

    comparaCadenas(c1, c2);

    free(c1);
    free(c2);

    return 0;
}