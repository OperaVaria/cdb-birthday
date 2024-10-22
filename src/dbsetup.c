/*

dbop.c

Functions connected to setting up database operations.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "date.h"
#include "dbop.h"
#include "dbsetup.h"
#include "input.h"
#include "macros.h"
#include "types.h"
#include "sqlite3.h"

/* Add to database setup.
Prompts user for data, fills Person struct, prepares escaped SQL statement. */
void add_setup(Person *struct_ptr)
{
    // Prompt for name information, fill struct arrays.
    get_str_prompt("Nickname? ", struct_ptr->nickname, BUFFER_LENGTH);
    get_str_prompt("First name? ", struct_ptr->first_name, BUFFER_LENGTH);
    get_str_prompt("Last name? ", struct_ptr->last_name, BUFFER_LENGTH);
    get_str_prompt("Date of birth (YYYY.MM.DD format): ", struct_ptr->birth_date, BUFFER_LENGTH);

    // Validate proper date format.
    while (!(validate_date(struct_ptr->birth_date)))
    {        
        get_str_prompt("Please try again: ", struct_ptr->birth_date, BUFFER_LENGTH);
    }

    // Create escaped SQL statement.
    sqlite3_snprintf(SQL_LENGTH, struct_ptr->sql_stm, 
             "INSERT INTO birthdays (nickname, first_name, last_name, birth_date) VALUES (%Q, %Q, %Q, %Q);",
             struct_ptr->nickname, struct_ptr->first_name, struct_ptr->last_name, struct_ptr->birth_date);

    // Print notification.
    printf("\nAdding item...\n");
}

/* Delete item from database setup.
Prompts user for data, fills Person struct, prepares escaped SQL statement. */
void del_setup(Person *struct_ptr)
{
    // Prompt for information, create variables.
    get_str_prompt("Nickname? ", struct_ptr->nickname, BUFFER_LENGTH);

    // Create escaped SQL statement.
    sqlite3_snprintf(SQL_LENGTH, struct_ptr->sql_stm,
             "DELETE from birthdays WHERE nickname = %Q;", struct_ptr->nickname);

    // Print notification.
    printf("\nRemoving item...\n");
}

/* Check if single entry exist.
Prompts user for data, fills Person struct, prepares escaped SQL statement. */
void check_entry_setup(Person *struct_ptr)
{
    // Prompt for information, create variables.
    get_str_prompt("Nickname? ", struct_ptr->nickname, BUFFER_LENGTH);

    // Create escaped SQL statement.
    sqlite3_snprintf(SQL_LENGTH, struct_ptr->sql_stm,
             "SELECT * from birthdays WHERE nickname = %Q;", struct_ptr->nickname);

    // Print notification.
    printf("\nChecking item...\n\n");
}

/* Prepares an SQL statement to check a birthday on the current day
or in the current month. Takes a Person struct and a date specifier string as
arguments. */
void check_date_setup(Person *struct_ptr, char date_spec[])
{
    // Declare variables.
    time_t timer;
    struct tm *tm_info;
    char form_date[DATE_LENGTH], month_name[10];

    // Get date.
    timer = time(NULL);
    tm_info = localtime(&timer);

    // Format date.
    strftime(form_date, 10, date_spec, tm_info);

    // Create escaped SQL statement.
    sqlite3_snprintf(SQL_LENGTH, struct_ptr->sql_stm,
             "SELECT * FROM birthdays WHERE birth_date LIKE '%%%q%%';", form_date);

    // Print notification based on call type (day or month).
    if (strcmp(date_spec, DAY) == 0)
    {
        printf("Listing birthdays for today...\n\n");
    }
    else
    {
        // Get current month name.
        strftime(month_name, 10, "%B", tm_info);

        // Print.
        printf("Listing birthdays for the month %s...\n\n", month_name);
    }
}

// Prepares SQL statement to list all birthday entries.
void list_all_setup(Person *struct_ptr)
{
    // Create escaped SQL statement.
    strcpy(struct_ptr->sql_stm, "SELECT * FROM birthdays");

    // Print notification.
    printf("Listing all items...\n\n");
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

    // Print notification.
    printf("Checking Database...\n");

    // Call DB operation function.
    db_op(table_structure, CREATE);
}
