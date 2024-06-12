/*

dbop.c

Functions connected to setting up database operations.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auxfunc.h"
#include "dbop.h"
#include "dbsetup.h"
#include "macros.h"

// Add to database setup:
char *add_setup(char *sql_statement)
{
    // Prompt for information, create variables.
    char *nickname = fgets_prompt("Nickname? ", 25);
    char *first_name = fgets_prompt("First name? ", 25);
    char *last_name = fgets_prompt("Last name? ", 25);
    char *birth_date = fgets_prompt("Date of birth (yyyy.mm.dd format): ", 11);

    // Create SQL statement.
    snprintf(sql_statement, MAX_LENGTH,
        "INSERT INTO birthdays (nickname, first_name, last_name, birth_date) VALUES ('%s', '%s', '%s', '%s');",
        nickname, first_name, last_name, birth_date);
    
    // Free memory.
    free(nickname); free(first_name); free(last_name); free(birth_date);

    // Print notification.
    printf("\nAdding item...\n");

    // Return SQL statement.
    return sql_statement;
}


// Delete item from database setup:
char *del_setup(char *sql_statement)
{
    // Prompt for information, create variables.
    char *nickname = fgets_prompt("Nickname? ", 25);

    // Create SQL statement.
    snprintf(sql_statement, MAX_LENGTH,
        "DELETE from birthdays WHERE nickname = '%s';", nickname);
    
    // Free memory.
    free(nickname);

    // Print notification.
    printf("\nRemoving item...\n");

    // Return SQL statement.
    return sql_statement;
}


// Check certain date's birthdays setup:
char *check_setup(char *sql_statement, char date_spec[])
{
    // Declare variables.
    time_t timer;
    struct tm *tm_info;
    char form_date[11], month_name[10];

    // Get date.
    timer = time(NULL);
    tm_info = localtime(&timer);

    // Format date.
    strftime(form_date, 10, date_spec, tm_info);

    // Create SQL statement.
    snprintf(sql_statement, MAX_LENGTH,
        "SELECT * FROM birthdays WHERE birth_date LIKE '%%%s%%';", form_date);

    // Print notification based on call type.
    if (date_spec == DAY)
    {
        printf("Listing birthdays for today...\n\n");
    }
    else if (date_spec == MONTH)
    {
        // Get current month name.
        strftime(month_name, 10, "%B", tm_info);

        // Print.
        printf("Listing birthdays for the month %s...\n\n", month_name);
    }
    
    // Return SQL statement.
    return sql_statement;
}


// List all items setup:
char *list_all_setup(char *sql_statement)
{
    // Create SQL statement.
    strcpy(sql_statement, "SELECT * FROM birthdays");

    // Print notification.
    printf("Listing all items...\n\n");

    // Return SQL statement.
    return sql_statement;
}


// Create "birthdays" table if it does not exits:
void create_table(void)
{
    // Statement for SQL table structure creation.
    char table_structure[] = "CREATE TABLE IF NOT EXISTS 'birthdays' "
                                "('nickname'	TEXT NOT NULL UNIQUE, "
                                "'first_name'	TEXT, "
                                "'last_name'	TEXT, "
                                "'birth_date'	TEXT)";

    // Call DB operation function.
    db_op(table_structure, CREATE);
}
