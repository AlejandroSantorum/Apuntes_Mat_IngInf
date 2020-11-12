#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"

/* New function created in our own */
/* It is useful if you implement idexes with STR type */
/* It recieves an int as a parameter that is the length of a key read from the file */
/* If it is equal to zero, it means the key is an INT, so it returns sizeof(int) */
/* If it is differentt to zero, it means the key is a STR, so it return its length */
size_t value_length_index(int len){
  if(len == 0)
    return sizeof(int);
  else
    return len;
}

/* New function created in our own */
/* It is useful if you implement idexes with STR type */
/* It recieves an int a parameter that is the length of a key read from the file */
/* If it is equal to zero, it means the key is an INT, so we allocate memory for the future key of type INT */
/* If it is differentt to zero, it means the key is a STR, so we allocate memory for the future key of type STR */
void* key_allocate(int len){
  void *a=NULL;

  if(len == 0){
    a = (void *)malloc(sizeof(int));
    if(a==NULL) return NULL;
    return a;
  }
  else{
    a = (void *) malloc(len * sizeof(char));
    if(a==NULL) return NULL;
    return a;
  }
}


size_t value_length(type_t type, void* value) {
    switch(type) {
        case INT:
            return sizeof(int);
        case STR:
            return (strlen((char*) value) + 1) * sizeof(char);
        case LLNG:
            return sizeof(long long int);
        case DBL:
            return sizeof(double);
        default:
            return 0;
    }
}

void print_value(FILE* f, type_t type, void* value) {
    switch(type) {
        case INT:
            fprintf(f, "%d", *((int*) value));
            break;
        case STR:
            fprintf(f, "%s", (char*) value);
            break;
        case  LLNG:
            fprintf(f, "%lli", *((long long *) value));
            break;
        case DBL:
            fprintf(f, "%lf", *((double *) value));
            break;
    }
}


int value_cmp(type_t type, void* value1, void* value2) {
    switch(type) {
        case INT:
            return *((int*) value1) - *((int*) value2);
        case STR:
            return strcmp((char*) value1, (char*) value2);
        case LLNG:
            return *((long long*) value1) - *((long long*) value2);
        case DBL:
            return *((double*) value1) - *((double*) value2);
        default:
            return 0;
    }
}

type_t type_parse(char* type_name) {
    if (strcmp(type_name, "INT") == 0) {
        return INT;
    } else if (strcmp(type_name, "STR") == 0) {
        return STR;
    } else if (strcmp(type_name, "LLNG") == 0) {
        return LLNG;
    } else if (strcmp(type_name, "DBL") == 0) {
        return DBL;
    }else {
        return -1;
    }
}

void* value_parse(type_t type, char* literal) {
    void* value;

    switch(type) {
        case INT:
            value = malloc(sizeof(int));
            *((int*) value) = atoi(literal);
            break;
        case STR:
            value = malloc((strlen(literal) + 1) * sizeof(char));
            strcpy(value, literal);
            break;
        case LLNG:
            value = malloc(sizeof(long long));
            *((long long*) value) = atoll(literal);
            break;
        case DBL:
            value = malloc(sizeof(double));
            *((double*) value) = strtod(literal, NULL);
            break;
        default:
            value = NULL;
            break;
    }

    return value;
}
