#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

/*
 * example 1 with a fixed query, results retrieved with SQLGetData
 */

int main(int argc, char **argv) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLSMALLINT columns; /* number of columns in result-set */
    SQLUSMALLINT i;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    char buf[1000];
    sprintf(buf, "select * from users where user='%s'", argv[1]);

    /* simple query */
    SQLExecDirect(stmt, (SQLCHAR*) "select * from sales order by user_id limit 100;", SQL_NTS);
    /* How many columns are there */
    SQLNumResultCols(stmt, &columns);

    /* print the name of each column */
    for (i = 1; i <= columns; i++) {
        SQLCHAR buf[512];
        SQLDescribeCol(stmt, i, buf, sizeof(buf), NULL, NULL, NULL, NULL, NULL);
        printf("%s\t", buf);
    }
    printf("\n");

    int k = 0;
    SQLINTEGER sid, uid, ssid;
    SQLCHAR isbn[512], date[512];

    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(SQLFetch(stmt))) {
      ret = SQLGetData(stmt, 1, SQL_C_SLONG, &sid, sizeof(SQLINTEGER), NULL);
      ret = SQLGetData(stmt, 2, SQL_C_SLONG, &uid, sizeof(SQLINTEGER), NULL);
      ret = SQLGetData(stmt, 3, SQL_C_CHAR, isbn, sizeof(isbn), NULL);
      ret = SQLGetData(stmt, 4, SQL_C_CHAR, date, sizeof(date), NULL);
      ret = SQLGetData(stmt, 5, SQL_C_SLONG, &ssid, sizeof(SQLINTEGER), NULL);
      printf("%d\t%d\t%s\t%s\t%d\n", sid, uid, isbn, date, ssid);
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

