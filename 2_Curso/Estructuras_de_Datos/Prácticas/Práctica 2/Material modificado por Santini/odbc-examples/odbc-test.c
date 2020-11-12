#include <stdlib.h>
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

/* test database connection */

int main(void) {
    SQLHENV env;
    SQLHDBC dbc;
    SQLRETURN ret; /* ODBC API return status */
    SQLCHAR outstr[1024];
    SQLSMALLINT outstrlen;

    /* Allocate an environment handle */
    SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
    /* We want ODBC 3 support */
    SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0);
    /* Allocate a connection handle */
    SQLAllocHandle(SQL_HANDLE_DBC, env, &dbc);
    /* Connect to the DSN mydsn */
    ret = SQLDriverConnect(dbc, NULL, (SQLCHAR*) "DRIVER=PostgreSQL;DATABASE=test01;SERVER=localhost;PORT=5432;UID=postgres;PWD=;", SQL_NTS,
                           outstr, sizeof(outstr), &outstrlen,
                           SQL_DRIVER_NOPROMPT);

    if (SQL_SUCCEEDED(ret)) {
        printf("Connected\n");
        printf("Returned connection string was:\n\t%s\n", outstr);
        if (ret == SQL_SUCCESS_WITH_INFO) {
            printf("Driver reported the following diagnostics\n");
            odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
        }
        SQLDisconnect(dbc);		/* disconnect from driver */
    } else {
        fprintf(stderr, "Failed to connect\n");
        odbc_extract_error("SQLDriverConnect", dbc, SQL_HANDLE_DBC);
    }
    /* disconnect from database and free up allocated handles */
    SQLDisconnect(dbc);
    SQLFreeHandle(SQL_HANDLE_DBC, dbc);
    SQLFreeHandle(SQL_HANDLE_ENV, env);

    return EXIT_SUCCESS;
}
