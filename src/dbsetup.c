/*

dbop.c

Functions connected to setting up database operations.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
// #include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "auxfunc.h"
#include "dbop.h"
#include "dbsetup.h"
#include "macros.h"
#include "types.h"

// Add to database setup:
void add_setup(Person *struct_ptr)
{
    // Prompt for name information, fill struct arrays.
    printf("Nickname? ");
    get_input(struct_ptr->nickname, BUFFER_LENGTH, stdin);
    printf("First name? ");
    get_input(struct_ptr->first_name, BUFFER_LENGTH, stdin);
    printf("Last name? ");
    get_input(struct_ptr->last_name, BUFFER_LENGTH, stdin);
    printf("Date of birth (yyyy.mm.dd format): ");
    get_input(struct_ptr->birth_date, DATE_LENGTH, stdin);

    // Validate proper date format.
    while (!(validate_date_form(struct_ptr->birth_date)))
    {
        printf("Incorrect format, please use yyyy.mm.dd: ");
        get_input(struct_ptr->birth_date, DATE_LENGTH, stdin);
    }

    // Create SQL statement.
    snprintf(struct_ptr->sql_stm, SQL_LENGTH,
             "INSERT INTO birthdays (nickname, first_name, last_name, birth_date) VALUES ('%s', '%s', '%s', '%s');",
             struct_ptr->nickname, struct_ptr->first_name, struct_ptr->last_name, struct_ptr->birth_date);

    // Print notification.
    printf("\nAdding item...\n");
}

// Delete item from database setup:
void del_setup(Person *struct_ptr)
{
    // Prompt for information, create variables.
    printf("Nickname? ");
    get_input(struct_ptr->nickname, BUFFER_LENGTH, stdin);

    // Create SQL statement.
    snprintf(struct_ptr->sql_stm, SQL_LENGTH,
             "DELETE from birthdays WHERE nickname = '%s';", struct_ptr->nickname);

    // Print notification.
    printf("\nRemoving item...\n");
}

// Check if single entry exist.
void check_entry_setup(Person *struct_ptr)
{
    // Prompt for information, create variables.
    printf("Nickname? ");
    get_input(struct_ptr->nickname, BUFFER_LENGTH, stdin);

    // Create SQL statement.
    snprintf(struct_ptr->sql_stm, SQL_LENGTH,
             "SELECT * from birthdays WHERE nickname = '%s';", struct_ptr->nickname);

    // Print notification.
    printf("\nChecking item...\n\n");
}

// Check a certain date setup:
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

    // Create SQL statement.
    snprintf(struct_ptr->sql_stm, SQL_LENGTH,
             "SELECT * FROM birthdays WHERE birth_date LIKE '%%%s%%';", form_date);

    // Print notification based on call type.
    if (strcmp(date_spec, DAY) == 0) // DAY
    {
        printf("Listing birthdays for today...\n\n");
    }
    else // MONTH
    {
        // Get current month name.
        strftime(month_name, 10, "%B", tm_info);

        // Print.
        printf("Listing birthdays for the month %s...\n\n", month_name);
    }
}

// List all items setup:
void list_all_setup(Person *struct_ptr)
{
    // Create SQL statement.
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
