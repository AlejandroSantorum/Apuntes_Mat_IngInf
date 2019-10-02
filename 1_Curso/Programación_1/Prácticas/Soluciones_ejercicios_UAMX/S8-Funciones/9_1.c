#include <stdio.h>

void areaTriangulo()
{
    int base, altura;
    double area;

    printf("Introduce la base del triángulo: ");
    scanf("%d", &base);

    printf("Introduce la altura del triángulo: ");
    scanf("%d", &altura);

    area=base*altura/2.0;

    printf("El área del triángulo de base %d y altura %d es %.2lf", base, altura, area);
}

int main()
{
    areaTriangulo();
    
    return 0;
}