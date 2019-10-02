#include "list.h"
#include "functions.h"
#include <stdio.h>
#include <stdlib.h>

List * read_data_from_file(char *filename){
    FILE *in;
    List *l;
    destroy_elementlist_function_type f1;
    copy_elementlist_function_type f2;
    print_elementlist_function_type f3;
    cmp_elementlist_function_type f4;
    int aux;
    
    f1 = destroy_intp_function;
    f2 = copy_intp_function;
    f3 = print_intp_function;
    f4 = cmp_intp_function;
    
    l = list_ini(f1, f2, f3, f4);
    if(l==NULL){
        return NULL;
    }
    
    in = (FILE*) fopen(filename, "r");
    if (in == NULL){
	list_free(l);
	return NULL;
    }
    
    while(feof(in)==0){
        fscanf(in,"%d",&aux);
        if(aux%2==0){
            if(list_insertFirst(l, &aux)==NULL){
                list_free(l);
                fclose(in);
                return NULL;
            }
        }
        else if(aux%2==1){
            if(list_insertLast(l, &aux)==NULL){
                list_free(l);
                fclose(in);
                return NULL;
            }
        }
        fprintf(stdout, "Imprimiendo lista con %d elementos:\n", list_size(l));
        list_print(stdout, l);
    }
    fclose(in);
    
    return l;
}

Status extract_data_from_list(List *l){
    int tam, i, *aux1, *aux2;
    List *lOrdered=NULL;
    destroy_elementlist_function_type f1;
    copy_elementlist_function_type f2;
    print_elementlist_function_type f3;
    cmp_elementlist_function_type f4;
    
    if(l==NULL){
        return ERROR;
    }
    
    f1 = destroy_intp_function;
    f2 = copy_intp_function;
    f3 = print_intp_function;
    f4 = cmp_intp_function;
    
    lOrdered = list_ini(f1, f2, f3, f4);
    if(lOrdered==NULL){
        return ERROR;
    }
    
    tam = list_size(l);
    
    for(i=0; i<(tam/2); i++){
        aux1 = (int*)list_extractFirst(l);
        
        fprintf(stdout, "Elemento extraído por el principio: [%d]\n", *aux1);
        fprintf(stdout, "Imprimiendo lista inicial con %d elementos:\n", list_size(l));
        list_print(stdout, l);
        list_insertInOrder(lOrdered, aux1);
        fprintf(stdout, "Imprimiendo lista ordenada con %d elementos:\n", list_size(lOrdered));
        list_print(stdout, lOrdered);
        free(aux1);
        
        aux2 = (int*)list_extractLast(l);
        
        fprintf(stdout, "Elemento extraído por el final: [%d]\n", *aux2);
        fprintf(stdout, "Imprimiendo lista inicial con %d elementos:\n", list_size(l));
        list_print(stdout, l);
        list_insertInOrder(lOrdered, aux2);
        fprintf(stdout, "Imprimiendo lista ordenada con %d elementos:\n", list_size(lOrdered));
        list_print(stdout, lOrdered);
        free(aux2);
    }
    
    if(list_isEmpty(l)==FALSE){
        aux1 = (int *)list_extractFirst(l);
        fprintf(stdout, "Elemento suelto debido a un número impar de datos: [%d]\n", *aux1);
        fprintf(stdout, "Imprimiendo lista inicial con %d elementos:\n", list_size(l));
        list_print(stdout, l);
        list_insertInOrder(lOrdered, aux1);
        fprintf(stdout, "Imprimiendo lista ordenada con %d elementos:\n", list_size(lOrdered));
        list_print(stdout, lOrdered);
        free(aux1);
    }
    
    list_free(lOrdered);
    return OK; 
}


int main(int argc, char** argv){
    List *l=NULL;
    Status check;
    
    if (argc < 2){
	fprintf(stdout, "Parámetros de entrada insuficientes: %d\n", argc);
	fprintf(stdout, "Introduzca nombre del programa y nombre del fichero de texto con los números a introducir.\n"); 
	return -1;
    }
    
    l = read_data_from_file(argv[1]);
    if(l==NULL){
        return EXIT_FAILURE;
    }
    
    
    check = extract_data_from_list(l);
    if(check==ERROR){
        return EXIT_FAILURE;
    }
    
    list_free(l);
    
    return EXIT_SUCCESS;
}