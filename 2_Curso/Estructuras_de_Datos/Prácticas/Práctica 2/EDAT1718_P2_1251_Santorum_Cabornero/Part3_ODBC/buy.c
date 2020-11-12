#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

#define TAM 1000
#define TAM_MAX 10000
/*
 * example 1 with a fixed query, results retrieved with SQLGetData
 */

int main(int argc, char **argv) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLINTEGER max_sale_id, discount=0, u_id;
    SQLREAL total = 0.0, price = 0.0;

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

    if(strcmp(argv[1], "del") == 0){
	     for(k = 2; k<argc; k++){
		       sprintf(buf, "delete from sales where sale_id = %d;", atoi(argv[k]));
	     }
	     ret = SQLExecDirect(stmt, (SQLCHAR*) buf, SQL_NTS);
       if(!SQL_SUCCEEDED(ret)){
         fprintf(stderr, "Failed to delete\n");
         odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
         return EXIT_FAILURE;
       }
    }


    else if(strcmp(argv[1], "add") == 0){
	     sprintf(buf, "select max(sale_id) from sales;");
       SQLExecDirect(stmt, (SQLCHAR*) buf, SQL_NTS);
	     if (SQL_SUCCEEDED(SQLFetch(stmt))) {
	        ret = SQLGetData(stmt, 1, SQL_C_SLONG, &max_sale_id, sizeof(SQLINTEGER), NULL);
	        max_sale_id += 1;
       }
	     else{
	        max_sale_id = 1;
      }
       SQLCloseCursor(stmt);


	     sprintf(buf, "select user_id from users where scrname = '%s';", argv[2]);
       SQLExecDirect(stmt, (SQLCHAR*) buf, SQL_NTS);
	     if (SQL_SUCCEEDED(SQLFetch(stmt))) {
	        ret = SQLGetData(stmt, 1, SQL_C_SLONG, &u_id, sizeof(SQLINTEGER), NULL);
		   }
	     else{
		       fprintf(stdout, "This user doesn't exist.\n");
           odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
		       exit(1);
	     }
       SQLCloseCursor(stmt);

	     for(k = 4; k<argc; k++){
		       sprintf(buf, "Insert into Sales (Sale_id, user_id, isbn, purchase_date) VALUES(%d, %d, '%s', '%s');", max_sale_id, u_id, argv[k], argv[3]);
           ret = SQLExecDirect(stmt, (SQLCHAR*) buf, SQL_NTS);
           if(!SQL_SUCCEEDED(ret)){
             fprintf(stderr, "Failed to insert into Sales\n");
             odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
             return EXIT_FAILURE;
           }
           SQLCloseCursor(stmt);

		       sprintf(buf, "select price from books where isbn='%s';", argv[k]);
		       SQLExecDirect(stmt, (SQLCHAR*) buf, SQL_NTS);
		       if (SQL_SUCCEEDED(SQLFetch(stmt))) {
	     		     ret = SQLGetData(stmt, 1, SQL_C_FLOAT, &price, sizeof(SQLREAL), NULL);
	     	   }
		       else{
			         fprintf(stdout, "Something went wrong at fetching the price.\n");
               odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
			         exit(1);
		       }
           SQLCloseCursor(stmt);

		       sprintf(buf, "select coef from discounts where isbn='%s' and initial_date<='%s' and final_date>='%s';", argv[k], argv[3], argv[3]);
		       SQLExecDirect(stmt, (SQLCHAR*) buf, SQL_NTS);
		       if (SQL_SUCCEEDED(SQLFetch(stmt))) {
	            ret = SQLGetData(stmt, 1, SQL_C_SLONG, &discount, sizeof(SQLINTEGER), NULL);
	         }
		       else{
			          discount = 0;
		       }
           SQLCloseCursor(stmt);

		       total += price*(100.0-discount)/100.0;

	     }
       fprintf(stdout, "Invoice: %d\n", max_sale_id);
       fprintf(stdout, "Total: %f euros.\n", total);
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
