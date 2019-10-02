#include <stdio.h>

int main() 
{
    char c; 
    int n; 

    printf("Introduce un carácter: "); 
    scanf("%c", &c); 
    printf("Introduce un número entero: "); 
    scanf("%d", &n); 

    printf("El valor ASCII del carácter %c es %d\n", c, c); 
    printf("Si sumo %d al carácter %c se obtiene el carácter %c que tiene el valor ASCII %d", n, c, c+n, c+n); 

    return 0; 
}