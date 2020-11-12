#include "table.h"

struct _table{
  FILE *f;
  int n_cols;
  type_t *types;
  long first_rec;
  void **values;
};

/*
   Creates a file that stores an empty table. This function doesn't
   keep any information in memory: it simply creates the file, stores
   the header information, and closes it.
*/
void table_create(char* path, int ncols, type_t *types){
  FILE *f=NULL;

  if(path==NULL || ncols <= 0 || types==NULL){
    printf("Fatal error. Table-F1-1.\n");
    exit(1);
  }

  f = (FILE *) fopen(path, "w");
  if(f == NULL){
    printf("Fatal error. Table-F1-2.\n");
    exit(1);
  }

  fwrite(&ncols, sizeof(int), 1, f);
  fwrite(types, sizeof(type_t), ncols, f);

  fclose(f);
}


/*
   Opens a table given its file name. Returns a pointer to a structure
   with all the information necessary to manage the table. Returns
   NULL is the file doesn't exist or if there is any error.
*/
table_t* table_open(char* path){
  table_t *t=NULL;

  if(path == NULL){
    printf("Fatal error. Table-F2-1.\n");
    exit(1);
  }

  t = (table_t *) malloc(sizeof(table_t));
  if(t == NULL){
    printf("Fatal error. Table-F2-2.\n");
    exit(1);
  }

  t->f = (FILE *) fopen(path, "r+");
  if(t->f == NULL){
    printf("Fatal Error. Table-F2-3.\n");
    exit(1);
  }
  
  fread(&(t->n_cols), sizeof(int), 1, t->f);

  t->types = (type_t *) malloc(t->n_cols * sizeof(type_t));
  if(t->types == NULL){
    printf("Fatal error. Table-F2-3.\n");
    fclose(t->f);
    free(t);
    exit(1);
  }
  fread(t->types, sizeof(type_t), t->n_cols, t->f);


  t->values = (void **) malloc(t->n_cols * sizeof(void *));
  if(t->values == NULL){
    printf("Fatal error. Table-F2-4.\n");
    fclose(t->f);
    free(t->types);
    free(t);
    exit(1);
  }
  
  t->values[0] = NULL;
  
  t->first_rec = ftell(t->f);
  
  return t;
}


/*
   Closes a table freeing the alloc'ed resources and closing the file
   in which the table is stored.
*/
void table_close(table_t* t) {
  if(t==NULL){
    printf("Error. Trying to free a NULL table.\n");
    return;
  }
  
  if(t->f != NULL) fclose(t->f);
  
  if(t->types != NULL) free(t->types);

  if(t->values[0] != NULL) free(t->values[0]);
  
  if(t->values != NULL) free(t->values);
  
  if(t != NULL) free(t);

  return;
}


/*
   Returns the number of columns of the table
*/
int table_ncols(table_t* t){
  if(t == NULL){
    printf("Fatal error. Table-F4-1.\n");
    exit(1);
  }
  return t->n_cols;
}


/*
   Returns the array with the data types of the columns of the
   table. Note that typically this kind of function doesn't make a
   copy of the array, rather, it returns a pointer to the actual array
   contained in the table structure. This means that the calling
   program should not, under any circumstance, modify the array that
   this function returns.
 */
type_t* table_types(table_t* t){
  if(t == NULL){
    printf("Fatal error. Table-F5-1.\n");
    exit(1);
  }
  return t->types;
}


/*
   Returns the position in the file of the first record of the table
*/
long table_first_pos(table_t* t){
  if(t == NULL){
    printf("Fatal error. Table-F6-1.\n");
    exit(1);
  }

  return t->first_rec;
}


/*
   Returns the position just past the last byte in the file, where a
   new record should be inserted.
*/
long table_last_pos(table_t* t){
  if(t == NULL){
    printf("Fatal error. Table-F7-1.\n");
    exit(1);
  }
  fseek(t->f, 0L, SEEK_END);
  return ftell(t->f);
}


/*
   Returns the position in the file in which the table is currently
   positioned.
*/
long table_cur_pos(table_t* t){
  if(t == NULL){
    printf("Fatal error. Table-F8-1.\n");
    exit(1);
  }
  return ftell(t->f);
}


/*
   Reads the record starting in the specified position. The record is
   read and stored in memory, but no value is returned. The value
   returned is the position of the following record in the file or -1
   if the position requested is past the end of the file.
*/
long table_read_record(table_t* t, long pos){
  int len, i;
  char *buff=NULL;

  if(t == NULL){
    printf("Fatal error. Table-F9-1.\n");
    exit(1);
  }

  if(table_last_pos(t) <= pos){
    return -1L;
  }

  if(t->values[0] != NULL){
    free(t->values[0]);
  }

  fseek(t->f, pos, SEEK_SET);

  fread(&len, sizeof(int), 1, t->f);
  buff = (char *) malloc((len+1) * sizeof(char));
  if(buff==NULL){
    printf("Fatal error. Table-F9-2.\n");
    exit(1);
  }

  fread(buff, sizeof(char), len, t->f);
  for(i=0; i < t->n_cols; i++){
    t->values[i] = buff;
    buff += value_length(t->types[i], t->values[i]);
  }

  return ftell(t->f);
}


/*
  Returns a pointer to the value of the given column of the record
  currently in memory. The value is cast to a void * (it is always a
  pointer: if the column is an INT, the function will return a pointer
  to it).. Returns NULL if there is no record in memory or if the
  column doesn't exist.
*/
void *table_column_get(table_t* t, int col){
  if(t==NULL || col < 0 || col > t->n_cols){
    printf("Fatal error. Table-F10-1. Abort! Abort!! Abort!!!\n");
    exit(1);
  }
  return ((void *) t->values[col]);
}


/*
   Inserts a record in the last available position of the table. Note
   that all the values are cast to void *, and that there is no
   indication of their actual type or even of how many values we ask
   to store... why?
  */
void table_insert_record(table_t* t, void** values){
  long pos;
  int len = 0, i;

  if(t==NULL || values==NULL){
    printf("Fatal error. Table-F11-1. Abort! Abort!! Abort!!!\n");
    exit(1);
  }

  pos = table_last_pos(t);

  fseek(t->f, pos, SEEK_SET);

  for(i=0; i<t->n_cols; i++){
    len += value_length(t->types[i], values[i]);
  }

  fwrite(&len, sizeof(int), 1, t->f);

  for(i=0; i<t->n_cols; i++){
    fwrite(values[i], sizeof(char), (value_length(t->types[i], values[i])), t->f);
  }
}
