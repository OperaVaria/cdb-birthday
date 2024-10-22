/*

dbop.c

Functions connected to database operations.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "dbop.h"
#include "macros.h"
#include "sqlite3.h"

// Static function prototypes.
static int sql_callback(void *data, int argc, char **argv, char **col_name);
static void format_col_name(char *col_name);

// Callback function call counter.
int callb_called = 0;

/* SQLite3 database operation function. Takes a prepared
SQL statement and a call type identifier as arguments.
Executes the command with error handling and notifications.*/
void db_op(char *sql_statement, int call_type)
{
    // Declare and define variables.
    sqlite3 *db;
    char *sql_err_msg = 0;
    const char *callb_data = "Birthday";
    int changes;
    bool error = false;

    // Open database with error handling.
    if (sqlite3_open("birthdays.db", &db) != SQLITE_OK)
    {
        fprintf(stderr, "Cannot open database. Error message: %s\n\n",
                sqlite3_errmsg(db));
        error = true;
    }

    // Execute SQL statement with error handling.
    if (sqlite3_exec(db, sql_statement, sql_callback,
                     (void *)callb_data, &sql_err_msg) != SQLITE_OK)
    {
        fprintf(stderr, "SQL error. Error message: %s\n", sql_err_msg);
        sqlite3_free(sql_err_msg);
        error = true;
    }

    /* MESSAGES */

    // No result.
    if (call_type == SELECT && callb_called == 0)
    {
        printf("No item(s) found!\n");
    }

    // Delete actions.
    if (call_type == DELETE)
    {
        // Get the number of rows modified in last call.
        changes = sqlite3_changes(db);

        // Not found
        if (changes == 0)
        {
            printf("Entry does not exist.\n");
        }

        // Successfully removed.
        else
        {
            printf("Item removed.\n");
        }
    }

    // Success notification.
    if (error)
    {
        printf("Process failed.\n");
    }
    else
    {
        printf("Process completed.\n");
    }

    /* CLOSING */

    // Reset callback call counter.
    callb_called = 0;

    // Close database.
    sqlite3_close(db);
}

// SQLite callback function to create a formatted SELECT output.
static int sql_callback(void *callb_data, int argc, char **argv, char **col_name)
{
    // Advance callback call counter.
    callb_called++;

    // Print birthday item number.
    printf("%s #%d:\n", (const char *)callb_data, callb_called);

    // Print item rows with normalized column names.
    for (int i = 0; i < argc; i++)
    {
        format_col_name(col_name[i]);
        printf("%s = %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }

    // Newline after print loop.
    printf("\n");

    // Return value must be 0 for SQLite.
    return 0;
}

/* Helper function for the SQL callback function. Formats the column names,
that are internally in camel case, to regular capitalized text. */
static void format_col_name(char *col_name)
{
    // Capitalize first letter.
    col_name[0] = toupper(col_name[0]);

    /* Look for the underscore character, if found, replace it
    with a space and capitalize the next character. */
    for (int i = 0; i < strlen(col_name); i++)
    {
        if (col_name[i] == '_')
        {
            col_name[i] = ' ';
            col_name[i + 1] = toupper(col_name[i + 1]);
        }
    }
}
