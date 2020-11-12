#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

#define TAM 1000
#define TAM_MAX 10000

int main(int argc, char **argv) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLINTEGER sale_id, usr_id;
    SQLCHAR isbn[30], datee[30];
    FILE *in=NULL;
    char buf[TAM], query[TAM], checking[TAM_MAX];
    int i, cont=0, lenght;

    if(argc < 1) exit(1);

    /* ----------------------------------------------*/
    /* WE MAKE SURE THAT NOBODY TRIES SQL INJECTION */
    strcpy(checking, argv[0]);
    for(i=1; i<argc; i++){
      strcat(checking, argv[i]);
    }
    lenght = (int)strlen(checking);

    for(i=0; i<lenght; i++){
      if(checking[i]==';'){
        cont++;
        if(cont == 2){
          fprintf(stdout, "SQL Injection awareness system security activated.\n");
          fprintf(stdout, "Please check the given information, it can be malicious.\n");
          return EXIT_FAILURE;
        }
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


    in = (FILE *) fopen(argv[1], "r");
    if(in == NULL) return -1;

    while(feof(in) == 0){
      fgets(buf, 1000, in);
      sscanf(buf, "%d %d %s %s", &sale_id, &usr_id, isbn, datee);

      sprintf(query, "insert into sales (sale_id, user_id, ISBN, Purchase_date) VALUES(%d, %d, '%s', '%s');", sale_id, usr_id, isbn, datee);

      SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

      SQLCloseCursor(stmt);
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
