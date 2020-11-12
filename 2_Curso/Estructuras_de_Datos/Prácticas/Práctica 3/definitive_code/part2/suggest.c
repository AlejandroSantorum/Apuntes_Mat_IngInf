#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"
#include "table.h"
#include "type.h"

#define TAM_MAX 1000
#define TAM 200
#define NCOLS 4

/* Function that creates an array of strings empty */
char** create_authors_record(){
  char **arec=NULL;

  arec = (char **) malloc(0 * sizeof(char*));

  return arec;
}

/* Each time that a different author is suggested we realloc some memory and copy it in the array */
/* We develop this process in order to avoid to print twice the same author's books */
char** insert_author(char **arec, char *name, int n){
  if(arec==NULL||name==NULL){
    printf("Fatal Error in function insert_author.\n");
    return NULL;
  }

  arec = (char **) realloc(arec, n+1 * sizeof(char *));
  if(arec == NULL){
    printf("Fatal Error in the realloc.\n");
    return NULL;
  }

  arec[n] = strdup(name);

  return arec;
}

/* We free all the memory */
void destroy_authors_record(char **arec, int n){
  int i;

  if(arec != NULL){
    for(i=0; i<n; i++){
      if(arec[i] != NULL) free(arec[i]);
    }
    free(arec);
  }
}

/* Function that checks if an author is already in the array of strings */
/* If it is, it means it has been already printed so we cannot do it again */
int check_author(char **arec, char *name, int n){
  int i;

  if(arec==NULL||name==NULL){
    printf("Fatal Error in function check_author.\n");
    return -1;
  }

  for(i=0; i<n; i++){
    if(strcmp(arec[i], name)==0){
      return 1; /* The author is already in the array, so we can't print his books again */
    }
  }
  return 0; /* The author isn't saved yet */
}



/* Now, the main program starts */
int main(int argc, char **argv){
  SQLHENV env;
  SQLHDBC dbc;
  SQLHSTMT stmt;
  SQLRETURN ret; /* ODBC API return status */
  SQLCHAR name[TAM], title[TAM];
  char checking[TAM_MAX], buff[TAM];
  int i, length, flag=0;

  if(argc != 2){ /* Error */
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
  table_t *tb=NULL;
  long pos;
  void **values=NULL;
  char **authors_array=NULL;
  int check, n_authors=0;

  values = (void **) malloc(NCOLS * sizeof(void *));
  if(values==NULL){ /* Error */
    printf("Fatal Error at allocating values' memory.\n");
    exit(1);
  }

  tb = table_open("scores.txt");
  if(tb==NULL){ /* Error */
    free(values);
    printf("Fatal Error at opening the table.\n");
    exit(1);
  }

  authors_array = create_authors_record(); /* We prepare the array of strings to avoid printing twice the same author's books*/
  if(authors_array==NULL){ /* Error */
    free(values);
    table_close(tb);
    printf("Fatal Error creating authors' record.\n");
    exit(1);
  }

  /* CONNECT */
  ret = odbc_connect(&env, &dbc);
  if (!SQL_SUCCEEDED(ret)){ /* Error */
    free(values);
    table_close(tb);
    destroy_authors_record(authors_array, n_authors);
    fprintf(stderr, "Failed to connect\n");
    odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
    return EXIT_FAILURE;
  }

  /* Allocate a statement handle */
  SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

  pos = table_first_pos(tb);
  while(1){
    pos = table_read_record(tb, pos);
    if(pos == -1){
      break;
    }

    for(i=0; i < table_ncols(tb); i++) {
        values[i] = table_column_get(tb, i);
    }

    if(*((int*) values[2]) == atoi(argv[1])){
      flag = 1; /* Found the same score! */
      sprintf(buff, "select author from books where isbn = '%s';", (char *) values[0]); /* Getting author's name */
      SQLExecDirect(stmt, (SQLCHAR*) buff, SQL_NTS);
      if(SQL_SUCCEEDED(SQLFetch(stmt))){
         ret = SQLGetData(stmt, 1, SQL_C_CHAR, name, sizeof(name), NULL);
      }
      else{ /* Error */
        free(values);
        table_close(tb);
        destroy_authors_record(authors_array, n_authors);
        fprintf(stdout, "Fatal Error at fetching the author's name.\n");
        odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
        exit(1);
      }
      SQLCloseCursor(stmt);

      check = check_author(authors_array, (char *) name, n_authors); /* Checking if the author has already been printed */
      if(check==-1){ /* Error */
        free(values);
        table_close(tb);
        destroy_authors_record(authors_array, n_authors);
        exit(1);
      }
      else if(check==1) continue; /* Yeah, the author has already been printed so we jump to the another one */

      authors_array = insert_author(authors_array, (char *) name, n_authors); /* If we are here it means this author has to be printed */
      if(authors_array==NULL){ /* Error */
        free(values);
        table_close(tb);
        destroy_authors_record(authors_array, n_authors);
        exit(1);
      }
      n_authors++;

      sprintf(buff, "select title from books where author = '%s';", name); /* Getting the title */
      SQLExecDirect(stmt, (SQLCHAR*) buff, SQL_NTS);

      while(SQL_SUCCEEDED(SQLFetch(stmt))){ /* Getting each title and printing it */
        ret = SQLGetData(stmt, 1, SQL_C_CHAR, title, sizeof(title), NULL);
        printf("%s\t%s\n", name, title);
      }
      SQLCloseCursor(stmt);
    }
  }
  /* FREE UP HANDLE STATEMENT */
  SQLFreeHandle(SQL_HANDLE_STMT, stmt);
  /* DISCONNECT */
  ret = odbc_disconnect(env, dbc);
  if (!SQL_SUCCEEDED(ret)) {
      return EXIT_FAILURE;
  }

  table_close(tb);
  free(values);
  destroy_authors_record(authors_array, n_authors);

  if(flag == 0){
    printf("Sorry. There is no books with this score.\n");
    printf("You can try it again.\n");
  }

  printf("Everything went OK.\n");

  return EXIT_SUCCESS;
}
