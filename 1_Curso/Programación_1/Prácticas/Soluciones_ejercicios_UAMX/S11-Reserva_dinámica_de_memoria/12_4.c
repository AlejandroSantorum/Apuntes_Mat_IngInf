#include <stdio.h>
#include <stdlib.h>
 
int main()
{
    int filas, columnas, ** matriz, i, j;

    printf("Introduce el número de filas de la matriz: ");
    scanf("%d", &filas);

    printf("Introduce el número de columnas de la matriz: ");
    scanf("%d", &columnas);
 
    matriz = (int **) malloc (filas * sizeof(int *));
    if (matriz == NULL)
    {
        printf("ERROR");
        return 1;
    }

    for (i=0; i<filas; i++)
    {
        matriz[i] = (int *) malloc (columnas * sizeof(int));
        /* Si no se ha podido reservar memoria en algún momento del bucle */
        if (matriz[i] == NULL)
        {
            /* Hay que liberar la memoria reservada hasta el momento en las iteraciones previas del bucle */
            for (j=0; j<i; j++)
                free(matriz[i]); /* Se libera la memoria de cada fila */
            
            free(matriz); /* Se libera la memoria del doble puntero a la matriz */
            return 1;
        }
    }

    for (i=0;i<filas;i++)
    {
        printf("Introduce los valores de la fila: %d\n", i+1);
        for(j=0;j<columnas; j++)
        {
            printf("Introduce los valores de la columna %d: ", j+1);
            scanf("%d", &matriz[i][j]);
        }
    }

    for (i=0 ; i<filas; i++)
        free(matriz[i]);
    
    free(matriz);
 
    return 0;

}
