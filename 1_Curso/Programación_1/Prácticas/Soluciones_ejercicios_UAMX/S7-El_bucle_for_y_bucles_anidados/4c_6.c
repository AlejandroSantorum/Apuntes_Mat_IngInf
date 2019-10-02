#include <stdio.h>

#define LIMITE 9

int main()
{
    int i, j;
    
    for (i=1; i<=LIMITE; i++)
    {
        printf("\nLa tabla del %d es:\n", i);
        
        for (j=1; j<=10; j++)
            printf("%d por %d es %d\n", i, j, i*j);

    }

    return 0;
}