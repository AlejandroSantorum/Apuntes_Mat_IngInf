#include <stdio.h>

int funcion(int x)
{
    int i, sumatorio;

    for (i=1, sumatorio=0; i<=x; i++)
        if (x%2 == 0 && i%2 ==0)
            sumatorio+=i;
        else if (x%2 != 0 && i%2 != 0)
            sumatorio+=i;

    return sumatorio;
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



-----------EL MIO-----------------

#include <stdio.h>

int sumatorio(int a){
	int i, suma = 0;

	if ((a % 2) == 0){
		for (i = 2; i <= a; i = i + 2){
			suma = suma + i;
		}
		return suma;
	}
	else{
		for (i = 1; i <= a; i = i + 2){
			suma = suma + i;
		}
		return suma;
	}
}

int main(){
	int i, n, resultado = 0;

	do{
		printf("Introduce un numero entero positivo: ");
		scanf("%d", &n);
		if (n <= 0){
			printf("Error. Vuelve a intentarlo.\n");
		}
	} while (n <= 0);

	for (i = 1; i <= n; i++){
		printf("%d\n", sumatorio(i));
		resultado = resultado + sumatorio(i);
	}
	printf("Total: %d", resultado);

	return 0;
}