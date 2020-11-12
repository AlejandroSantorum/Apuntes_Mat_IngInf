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
    char buf[TAM], checking[TAM_MAX];
    int k, i, lenght, cont=0;

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

    for(k=4; k<argc; k++){
	     sprintf(buf, "Insert into Discounts (ISBN, Initial_date, Final_date, Coef) VALUES('%s', '%s', '%s', %d);", argv[k], argv[2], argv[3], atoi(argv[1]));
       ret = SQLExecDirect(stmt, (SQLCHAR*) buf, SQL_NTS);
	     if(!SQL_SUCCEEDED(ret)){
         fprintf(stderr, "Failed to insert\n");
         odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
         return EXIT_FAILURE;
       }
       SQLCloseCursor(stmt);
    }


    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
