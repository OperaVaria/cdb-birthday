/*

dbop.c

Functions connected to database operations.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <ctype.h>
#include <stdio.h>
#include "dbop.h"
#include "macros.h"
#include "sqlite3.h"

// Static callback function prototype.
static int sql_callback(void *data, int argc, char **argv, char **azColName);

// Callback function call counter.
int callb_called = 0;

// Database operation function:
void db_op(char *sql_statement, int call_type)
{
    // Declare and define variables.
    sqlite3 *db;
    char *sql_err_msg = 0;
    const char *callb_data = "Item";
    int changes, rc;

    // Open database.
    rc = sqlite3_open("birthdays.db", &db);

    // Opening error handling.
    if (rc)
    {
        fprintf(stderr, "Cannot open database. Error message = %s\n\n", sqlite3_errmsg(db));
        sqlite3_free(sql_err_msg);
        return;
    }

    // Execute SQL statement.
    rc = sqlite3_exec(db, sql_statement, sql_callback, (void *)callb_data, &sql_err_msg);

    // Execution error handling.
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error. Error message = %s\n", sql_err_msg);
        sqlite3_free(sql_err_msg);
    }

    // Messages for no result:

    if (call_type == SELECT)
    {
        if (callb_called == 0)
        {
            printf("No item(s) found!\n");
        }
        else
        {
            printf("Process completed.\n");
        }
    }
    else if (call_type == DELETE)
    {
        // Get the number of rows modified in last call.
        changes = sqlite3_changes(db);

        if (changes == 0)
        {
            printf("Entry does not exist.\n");
        }
        else
        {
            printf("Item removed.\n");
        }
    }
    else
    {
        printf("Process completed.\n");
    }

    // Reset callback call counter.
    callb_called = 0;

    // Close database.
    sqlite3_close(db);
}

// SQLite callback function for formatted SELECT output:
static int sql_callback(void *callb_data, int argc, char **argv, char **col_name)
{
    // Advance callback call counter.
    callb_called++;

    // Print item number.
    printf("%s #%d: \n", (const char *)callb_data, callb_called);

    // Print item rows.
    for (int i = 0; i < argc; i++)
    {
        printf("%s: %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    // Return value must be 0 for SQLite.
    return 0;
}