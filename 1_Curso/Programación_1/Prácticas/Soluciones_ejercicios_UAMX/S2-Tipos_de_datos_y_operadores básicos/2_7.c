#include <stdio.h>

int main() 
{
    char c1, c2; 

    printf("Introduce una letra: "); 
    scanf("%c", &c1); 
    printf("Introduce otra letra: "); 
    scanf("\n%c", &c2); 

    printf("La distancia entre %c y %c es %d", c1, c2, c2-c1); 

    return 0; 
}