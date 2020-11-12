#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "table.h"
#include "type.h"
#include "index.h"

#define TAM_MAX 1000
#define TAM 100
#define NCOLS 4

int main(int argc, char **argv){
  SQLHENV env;
  SQLHDBC dbc;
  SQLHSTMT stmt;
  SQLRETURN ret; /* ODBC API return status */
  SQLCHAR isbn[TAM];
  SQLINTEGER book_id;
  char checking[TAM_MAX], buff[TAM];
  int i, length;
  table_t *tb=NULL;
  index_t *idx=NULL;
  void **values=NULL;
  long pos;

  if(argc != 3){ /* Error */
    printf("Incorrect input parameters.\nPlease check them.\n");
    return EXIT_FAILURE;
  }

  /* ----------------------------------------------*/
  /* WE MAKE SURE THAT NOBODY TRIES SQL INJECTION */
  strcpy(checking, argv[0]);
  for(i=1; i<argc; i++){
    strcat(checking, argv[i]);
  }
  length = (int)strlen(checking);

  for(i=0; i<length; i++){
    if(checking[i]==';'){
      fprintf(stdout, "SQL Injection awareness system security activated.\n");
      fprintf(stdout, "Please check the given information, it can be malicious.\n");
      return EXIT_FAILURE;
    }
    else if(checking[i]=='%'){
      fprintf(stdout, "SQL Injection awareness system security activated.\n");
      fprintf(stdout, "Please check the given information, it can be malicious.\n");
      return EXIT_FAILURE;
    }
    else if(checking[i]=='-'){
      if(checking[i+1]=='-'){
        fprintf(stdout, "SQL Injection awareness system security activated.\n");
        fprintf(stdout, "Please check the given information, it can be malicious.\n");
        return EXIT_FAILURE;
      }
    }
    else if(checking[i]=='/'){
      if(checking[i+1]=='*'){
        fprintf(stdout, "SQL Injection awareness system security activated.\n");
        fprintf(stdout, "Please check the given information, it can be malicious.\n");
        return EXIT_FAILURE;
      }
    }
  }
  /* Everything went OK and the program can continue to develop */
  /* --------------------------------------------------------------------------------*/


  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)) {
    fprintf(stderr, "Failed to connect\n");
    odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
    return EXIT_FAILURE;
  }

  /* Allocate a statement handle */
  SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

  /* First query: getting the isbn of the title given */
  sprintf(buff, "select isbn from books where title = '%s';", argv[1]);
  SQLExecDirect(stmt, (SQLCHAR*) buff, SQL_NTS);
  if (SQL_SUCCEEDED(SQLFetch(stmt))) {
     ret = SQLGetData(stmt, 1, SQL_C_CHAR, isbn, sizeof(isbn), NULL);
  }
  else{ /* Error */
    fprintf(stdout, "This title doesn't exist in the database.\n");
    fprintf(stdout, "Please check the title name you have introduced.\n");
    odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
    exit(1);
  }
  SQLCloseCursor(stmt);

  /* Second query: getting the book_id of the title given */
  sprintf(buff, "select book_id from books where isbn = '%s';", isbn);
  SQLExecDirect(stmt, (SQLCHAR*) buff, SQL_NTS);
  if (SQL_SUCCEEDED(SQLFetch(stmt))) {
     ret = SQLGetData(stmt, 1, SQL_C_SLONG, &book_id, sizeof(SQLINTEGER), NULL);
  }
  else{ /* Error */
    fprintf(stdout, "Fatal Error at fetching the book_id.\n");
    odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
    exit(1);
  }
  SQLCloseCursor(stmt);

  /* FREE UP HANDLE STATEMENT */
  SQLFreeHandle(SQL_HANDLE_STMT, stmt);
  /* DISCONNECT */
  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return EXIT_FAILURE;
  }

  /* Now we just have to "play" with our table and type implementations */

  values = (void **) malloc(NCOLS * sizeof(void *));
  if(values==NULL){ /* Error */
    printf("Fatal Error at allocating values' memory.\n");
    exit(1);
  }

  values[0] = (char *) malloc((strlen((char*)isbn)+1) * sizeof(char));
  if(values[0]==NULL){ /* Error */
    free(values);
    printf("Fatal Error at allocating values[0].\n");
    exit(1);
  }
  values[1] = (char *) malloc((strlen(argv[1])+1) * sizeof(char));
  if(values[1]==NULL){ /* Error */
    free(values[0]);
    free(values);
    printf("Fatal Error at allocating values[1].\n");
    exit(1);
  }
  values[2] = (int *) malloc(sizeof(int));
  if(values[2]==NULL){ /* Error */
    free(values[0]);
    free(values[1]);
    free(values);
    printf("Fatal Error at allocating values[2].\n");
    exit(1);
  }
  values[3] = (int *) malloc(sizeof(int));
  if(values[3]==NULL){ /* Error */
    free(values[0]);
    free(values[1]);
    free(values[2]);
    free(values);
    printf("Fatal Error at allocating values[3].\n");
    exit(1);
  }

  strcpy((char*) values[0], (char *) isbn);
  strcpy((char*) values[1], argv[1]);
  *((int *) values[2]) = atoi(argv[2]);
  *((int *) values[3]) = book_id;

  tb = table_open("table.txt"); /* It must be already opened by using create_files.c */
  if(tb==NULL){ /* Error */
    printf("Fatal Error at opening the table.\n");
    exit(1);
  }

  idx = index_open("index.txt"); /* It must be already opened by using create_files.c */
  if(idx==NULL){ /* Error */
    printf("Fatal Error at opening the index.\n");
    exit(1);
  }

  pos = table_last_pos(tb);
  table_insert_record(tb, values); /* Introducing into the table */
  index_put(idx, (void *) argv[2], pos); /* Introducing into the index */
  index_save(idx); /* Saving the index after changes */

  free(values[3]);
  free(values[2]);
  free(values[1]);
  free(values[0]);
  free(values);

  table_close(tb);
  index_close(idx);
  printf("Everything went OK.\n");
  printf("Score inserted in the table & in the index successfully.\n");

  return EXIT_SUCCESS;
}
