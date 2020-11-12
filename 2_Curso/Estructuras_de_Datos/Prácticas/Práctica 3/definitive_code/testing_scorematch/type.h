/* TYPE MODULE */
/* TYPE ENUMERATION OF SUPPORTED DATA TYPES */
#ifndef TYPE_H
#define TYPE_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    INT, /*integer*/
    STR, /*string*/
    LLNG, /*long integer*/
    DBL, /*doble*/
} type_t;

/* length in bytes of the value */
size_t value_length(type_t type, void* value);

/* prints the value in the appropriate format */
void print_value(FILE* f, type_t type, void* value);

/*
   compares two values, returns an integer less than, equal to, or
   greater than zero if value1 is found, respectively, to be less
   than, to match, or be greater than value2
*/
int value_cmp(type_t type, void* value1, void* value2);

/*
   parses an "INT" or "STR" string to the appropriate data type
   defined in the type_t enumeratex
*/
type_t type_parse(char* type_name);

/*
   parses a string to the appropriate value
*/
void* value_parse(type_t type, char* literal);

/* This function is explained in type.c */
size_t value_length_index(int len);

/* This function is explained in type.c */
void* key_allocate(int len);

#endif
