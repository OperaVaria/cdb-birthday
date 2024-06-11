/*

CDbBirthday v1.1.0
By OperaVaria, 2024

A simple, lightweight command line application, written in C, to store
birthday information in an SQLite database.

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public
License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied
warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not,
see <https://www.gnu.org/licenses/>

*/

// Header files:
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "./sqlite3.h"

// Preprocessor macros:

// SQL call type constants.
#define CREATE 1
#define INSERT 2
#define DELETE 3
#define SELECT 4

// SQL statement max length.
#define MAX_LENGTH 256

// Date specifier constants.
#define MONTH ".%m."
#define DAY ".%m.%d"

// Function-like macros.
#define between(x, a, b)  (((a) <= (x)) && ((x) <= (b)))

// Global variables:
int callb_called = 0; // SQL callback function call counter.
bool loop_active = true; // Boolean to keep main loop active.

// Function prototypes:
int select_menu(void);
void main_switch(int sel_opt);
char *add_setup(char *sql_statement);
char *del_setup(char *sql_statement);
char *check_setup(char *sql_statement, char date_spec[]);
char *list_all_setup(char *sql_statement);
void create_table(void);
void db_op(char *sql_statement, int call_type);
char *fgets_prompt (char prompt[], int string_size);
static int sql_callback(void *data, int argc, char **argv, char **azColName);

// Main function:
int main(void)
{
    // Initial text.
    printf("CDbBirthday v1.1.0\n");
    printf("By OperaVaria\n");

    /* Check if db file and correct table exists.
    If not, create it. */
    create_table();

    // Application loop.
    while (loop_active)
    {
        // Run select menu.
        int sel_opt = select_menu();

        // Pass selected option to main switch.
        main_switch(sel_opt);
    }

    return 0;
}

// Main option menu:
int select_menu(void)
{
    // Default user option value.
    int user_opt = 0;

    // Menu text.
    printf("\nSelect option:\n");
    printf("1) Add a birthday entry.\n");
    printf("2) Delete a birthday entry.\n");
    printf("3) Check birthdays for current month.\n");
    printf("4) Check birthdays for today.\n");
    printf("5) List all birthday entries.\n");
    printf("6) Exit.\n\n");

    // Input prompt.
    printf("Enter your choice (1-6): ");

    // Get user input.
    scanf("%d", &user_opt);
    scanf("%*[^\n]");

    // Return selected option.
    return user_opt;
}

// Main switch:
void main_switch(int sel_opt)
{
    // Declare SQL statement string, allocate memory.
    char *sql_statement;
    sql_statement = malloc(sizeof(char) * MAX_LENGTH);
    if (sql_statement == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Call functions based on selected menu option.
    switch (sel_opt)
    {
    case 1:
        sql_statement = add_setup(sql_statement);
        db_op(sql_statement, INSERT);
        break;

    case 2:
        sql_statement = del_setup(sql_statement);
        db_op(sql_statement, DELETE);
        break;

    case 3:
        sql_statement = check_setup(sql_statement, MONTH);
        db_op(sql_statement, SELECT);
        break;

    case 4:
        sql_statement = check_setup(sql_statement, DAY);
        db_op(sql_statement, SELECT);
        break;

    case 5:
        sql_statement = list_all_setup(sql_statement);
        db_op(sql_statement, SELECT);        
        break;

    case 6:
        printf("Exiting...\n\n");
        loop_active = false;
        break;

    default:
        printf("\nInvalid option, try again!\n");        
        break;
    }

    // Print messages after operations:

    if (between(sel_opt, 1, 2))
    {
        printf("Completed.\n");
    }

    if (between(sel_opt, 1, 5))
    {
        printf("Returning to main menu...\n");
    }

    // Free memory.
    free(sql_statement);
}

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
    // Initialize variables.
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

// Database operation function:
void db_op(char *sql_statement, int call_type)
{
    // Initialize variables.
    sqlite3 *db;
    char *sql_err_msg = 0;
    const char *callb_data = "Item";
    int rc;

    // Open database.
    rc = sqlite3_open("birthdays.db", &db);

    // Opening error handling.
    if (rc)
    {
        fprintf(stderr, "Cannot open database. Error message = %s\n\n", sqlite3_errmsg(db));
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

    // Message if no result.
    if (call_type == SELECT && callb_called == 0)
    {
        printf("No items found!\n\n");
    }

    // Reset callback call counter.
    callb_called = 0;

    // Close database.
    sqlite3_close(db);
}

// String retrieval prompt with fgets.
char *fgets_prompt (char prompt[], int string_size) {

    // Initialize pointer.
    char* buffer;

    // Allocate memory.
    buffer = malloc(sizeof(char) * string_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Display prompt.
    printf(prompt);  

    // Store input.
    fgets(buffer, string_size, stdin);

    // Remove newline.
    buffer[strcspn(buffer, "\n")] = 0;
    
    // Clear stdin buffer.
    int c;
    while ((c = getchar()) != '\n' && c != EOF) { }

    // Return stored input string.
    return buffer;
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
