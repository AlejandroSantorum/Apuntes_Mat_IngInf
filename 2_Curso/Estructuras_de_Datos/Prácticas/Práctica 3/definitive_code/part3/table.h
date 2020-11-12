/*
  Data Structures 2017-18

  Lab assignment N. 3

  This file defines the interface that you have to implement with the
  basic functions to manage a data base table.
*/
#ifndef TABLE_H
#define TABLE_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "type.h"

typedef struct _table table_t;

/*
   Creates a file that stores an empty table. This function doesn't
   keep any information in memory: it simply creates the file, stores
   the header information, and closes it.
*/
void table_create(char* path, int ncols, type_t* types);

/*
   Opens a table given its file name. Returns a pointer to a structure
   with all the information necessary to manage the table. Returns
   NULL is the file doesn't exist or if there is any error.
*/
table_t* table_open(char* path);

/*
   Closes a table freeing the alloc'ed resources and closing the file
   in which the table is stored.
*/
void table_close(table_t* table);

/*
   Returns the number of columns of the table
*/
int table_ncols(table_t* table);

/*
   Returns the array with the data types of the columns of the
   table. Note that typically this kind of function doesn't make a
   copy of the array, rather, it returns a pointer to the actual array
   contained in the table structure. This means that the calling
   program should not, under any circumstance, modify the array that
   this function returns.
 */
type_t*table_types(table_t* table);

/*
   Returns the position in the file of the first record of the table
*/
long table_first_pos(table_t* table);

/*
   Returns the position in the file in which the table is currently
   positioned.
*/
long table_cur_pos(table_t* table);

/*
   Returns the position just past the last byte in the file, where a
   new record should be inserted.
*/
long table_last_pos(table_t* table);

/*
   Reads the record starting in the specified position. The record is
   read and stored in memory, but no value is returned. The value
   returned is the position of the following record in the file or -1
   if the position requested is past the end of the file.
*/
long table_read_record(table_t* table, long pos);

/*
  Returns a pointer to the value of the given column of the record
  currently in memory. The value is cast to a void * (it is always a
  pointer: if the column is an INT, the function will return a pointer
  to it).. Returns NULL if there is no record in memory or if the
  column doesn't exist.
*/
void *table_column_get(table_t* table, int col);


/*
   Inserts a record in the last available position of the table. Note
   that all the values are cast to void *, and that there is no
   indication of their actual type or even of how many values we ask
   to store... why?
  */
void table_insert_record(table_t* table, void** values);

#endif
