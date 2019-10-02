#include <stdio.h>

int funcion(int x)
{
    int i, potencia;

    for (i=0, potencia=1; i<x; i++)
        potencia*=x;

    return potencia;
}

int main()
{
    int num, retorno, i, total;

    do
    {
        printf("Introduce un número positivo: ");
        scanf("%d", &num);
        if (num<1)
            printf("Error, debes introducir un número positivo\n");
    }while(num<1);

    for (i=1,total=0; i<=num; i++)
    {
        retorno=funcion(i);
        printf("%d\n", retorno);
        total+=retorno;
    }

    printf("Total: %d", total);

    return 0;                
}


------------------------EL MÍO-----------------------

#include <stdio.h>
#include <math.h>

long int potencia(int a){
	long int pot;

	pot = pow(a, a);

	return pot;
}

int main(){
	int i, n;
	long int resultado = 0;

	do{
		printf("Introduce un numero entero positivo: ");
		scanf("%d", &n);
		if (n <= 0){
			printf("Error. Vuelve a intentarlo.\n");
		}
	} while (n <= 0);

	for (i = 1; i <= n; i++){
		printf("%ld\n", potencia(i));
		resultado = resultado + potencia(i);
	}
	printf("Total: %ld", resultado);

	return 0;
}