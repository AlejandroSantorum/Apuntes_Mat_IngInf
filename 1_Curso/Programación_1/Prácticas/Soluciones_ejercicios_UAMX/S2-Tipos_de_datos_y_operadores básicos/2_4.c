#include <stdio.h>

int main() 
{
    printf("Una variable de tipo short ocupa %d bytes\n", sizeof(short)); 
    printf("Una variable de tipo unsigned short ocupa %d bytes\n", sizeof(unsigned short));
    printf("Una variable de tipo long ocupa %d bytes\n", sizeof(long)); 
    printf("Una variable de tipo unsigned long ocupa %d bytes\n", sizeof(unsigned long)); 
    printf("Una variable de tipo int ocupa %d bytes\n", sizeof(int)); 
    printf("Una variable de tipo unsigned int ocupa %d bytes\n", sizeof(unsigned int)); 
    printf("Una variable de tipo float ocupa %d bytes\n", sizeof(float)); 
    printf("Una variable de tipo double ocupa %d bytes\n", sizeof(double));
    printf("Una variable de tipo char ocupa %d bytes\n", sizeof(char)); 

    return 0; 
}