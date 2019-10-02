#include <stdio.h>
 
int main()
{
    short s = -5;
    unsigned short us = 7;
    long l = -45000;
    unsigned long ul = 678912356;
    int i = 123531;
    unsigned int ui = 32455343;
    float f = 2312.34223;
    double d = 12.324234;
    char c = 'J';

    printf("short: %hd y unsigned short: %hu\n", s, us);
    printf("long: %ld y unsigned long: %lu\n", l, ul);
    printf("int: %d y unsigned int: %u\n", i, ui);
    printf("float: %f, notación científica: %e y más corto: %g\n", f, f, f);
    printf("double: %lf, notación científica: %le y más corto: %lg\n", d, d, d);
    printf("char: %c", c);
 
    return 0;

}