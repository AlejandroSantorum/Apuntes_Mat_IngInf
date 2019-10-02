#include <stdio.h>

double areaTriangulo()
{
    int base, altura;
    double area;

    printf("Introduce la base del triángulo: ");
    scanf("%d", &base);

    printf("Introduce la altura del triángulo: ");
    scanf("%d", &altura);

    area=base*altura/2.0;

    return area;
}

int main()
{
    double ar;

    ar=areaTriangulo();

    printf("El área del triángulo es %.2lf", ar);

    return 0;
}