/*

CDbBirthday v1.0.0
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
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sqlite3.h>

// Function prototypes:
int select_menu(void);
void main_switch(int selected_opt);
char *add_setup(char *sql_statement);
char *del_setup(char *sql_statement);
char *check_setup(char *sql_statement);
char *list_all_setup(char *sql_statement);
void create_table(void);
void db_op(char *sql_statement, int call_type);
void clear_input_buffer(void);
static int sql_callback(void *data, int argc, char **argv, char **azColName);

// Global variables:
int callb_called = 0; // SQL callback function call counter.

// Identifier constants for SQL calls:
const int CREATE = 1; // CREATE SQL call.
const int INSERT = 2; // INSERT SQL call.
const int DELETE = 3; // DELETE SQL call.
const int SELECT = 4; // SELECT SQL call.

// Main function:
int main(void)
{

    // Initial text.
    printf("CDbBirthday v1.0.0\n");
    printf("By OperaVaria\n");

    // Application loop.
    while (true)
    {
        /* Check if db file and correct table exists.
           If not, create it. */
        create_table();

        // Run select menu.
        int selected_opt = select_menu();

        // Pass selected option to main switch.
        main_switch(selected_opt);
    }

    return 0;
}

// Main option menu:
int select_menu(void)
{
    // Default user option value.
    int user_option = 0;

    // Menu text.
    printf("\nSelect action:\n");
    printf("1. Add birthday to DB\n");
    printf("2. Remove birthday from DB\n");
    printf("3. Check today's birthdays\n");
    printf("4. List all entries\n");
    printf("5. Exit\n");
    printf("1,2,3,4 or 5? ");

    // Get user input.
    scanf("%d", &user_option);

    // Validate input with retry loop, clear input buffer.
    while (user_option != 1 && user_option != 2 && user_option != 3 && user_option != 4 && user_option != 5)
    {
        printf("Invalid choice, try again (1-5): ");
        scanf("%d", &user_option);
        clear_input_buffer();
    }

    // Return selected option.
    return user_option;
}

// Main switch:
void main_switch(int selected_opt)
{
    // Declare SQL statement string.
    char *sql_statement;
    sql_statement = malloc(sizeof(char) * 512);

    // Clear input buffer.
    clear_input_buffer();

    // Call functions based on selected menu option.
    switch (selected_opt)
    {
    case 1:
        sql_statement = add_setup(sql_statement);
        db_op(sql_statement, INSERT);
        printf("Completed.\n");
        printf("Returning to main menu...\n");
        break;

    case 2:
        sql_statement = del_setup(sql_statement);
        db_op(sql_statement, DELETE);
        printf("Completed.\n");
        printf("Returning to main menu...\n");
        break;

    case 3:
        sql_statement = check_setup(sql_statement);
        db_op(sql_statement, SELECT);
        printf("Returning to main menu...\n");
        break;

    case 4:
        sql_statement = list_all_setup(sql_statement);
        db_op(sql_statement, SELECT);
        printf("Returning to main menu...\n");
        break;

    case 5:
        printf("\nExiting...\n\n");
        exit(0);
        break;
    }

    // Free memory.
    free(sql_statement);
}

// Add to database setup:
char *add_setup(char *sql_statement)
{
    // Initialize string variables.
    char nickname[25], first_name[25], last_name[25], birth_date[25], sql_buffer[512];

    // Prompt for information, store with fgets, strip new line.
    printf("Nickname? ");
    fgets(nickname, 25, stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    printf("First name? ");
    fgets(first_name, 25, stdin);
    first_name[strcspn(first_name, "\n")] = 0;

    printf("Last name? ");
    fgets(last_name, 25, stdin);
    last_name[strcspn(last_name, "\n")] = 0;

    printf("Date of birth (yyyy.mm.dd format): ");
    fgets(birth_date, 25, stdin);
    birth_date[strcspn(birth_date, "\n")] = 0;

    // Create SQL statement.
    snprintf(sql_buffer, sizeof(sql_buffer),
        "INSERT INTO birthdays (nickname, first_name, last_name, birth_date) VALUES ('%s', '%s', '%s', '%s'); ",
        nickname, first_name, last_name, birth_date);
    strcpy(sql_statement, sql_buffer);

    // Print notification.
    printf("\nAdding item...\n");

    // Return SQL statement.
    return sql_statement;
}

// Delete item from database setup:
char *del_setup(char *sql_statement)
{
    // Initialize string variables.
    char nickname[25], sql_buffer[512];

    // Prompt for information, store with fgets, strip new line.
    printf("Nickname? ");
    fgets(nickname, sizeof(nickname), stdin);
    nickname[strcspn(nickname, "\n")] = 0;

    // Create SQL statement.
    snprintf(sql_buffer, sizeof(sql_buffer),
        "DELETE from birthdays WHERE nickname = '%s'; ", nickname);
    strcpy(sql_statement, sql_buffer);

    // Print notification.
    printf("\nRemoving item...\n");

    // Return SQL statement.
    return sql_statement;
}

// Check today's birthdays setup:
char *check_setup(char *sql_statement)
{
    // Declare variables.
    time_t timer;
    struct tm *tm_info;
    char form_date[10], sql_buffer[512];

    // Get date.
    timer = time(NULL);
    tm_info = localtime(&timer);

    // Format date.
    strftime(form_date, 10, ".%m.%d", tm_info);

    // Create SQL statement.
    snprintf(sql_buffer, sizeof(sql_buffer),
        "SELECT * FROM birthdays WHERE birth_date LIKE '%%%s'; ", form_date);
    strcpy(sql_statement, sql_buffer);

    // Print notification.
    printf("\nListing birthdays today...\n\n");

    // Return SQL statement.
    return sql_statement;
}

// List all items setup:
char *list_all_setup(char *sql_statement)
{
    // Create SQL statement.
    strcpy(sql_statement, "SELECT * FROM birthdays");

    // Print notification.
    printf("\nListing all items...\n\n");

    // Return SQL statement.
    return sql_statement;
}

// Create "birthdays" table if it does not exits:
void create_table(void)
{
    // Statement for SQL table structure creation.
    char table_structure[150] = "CREATE TABLE IF NOT EXISTS 'birthdays' "
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
        fprintf(stderr, "Cannot open database. Error message: %s\n\n", sqlite3_errmsg(db));
        return;
    }

    // Execute SQL statement.
    rc = sqlite3_exec(db, sql_statement, sql_callback, (void *)callb_data, &sql_err_msg);

    // Execution error handling.
    if (rc != SQLITE_OK)
    {
        fprintf(stderr, "SQL error. Error message: %s\n", sql_err_msg);
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

// Clear input buffer with getchar loop:
void clear_input_buffer(void)
{
    while ((getchar()) != '\n');
}

// SQLite callback function for formatted SELECT output:
static int sql_callback(void *callb_data, int argc, char **argv, char **col_name)
{
    // Declare for loop counter.
    int i;

    // Advance callback call counter.
    callb_called++;

    // Print item number.
    fprintf(stderr, "%s #%d: \n", (const char *)callb_data, callb_called);

    // Print item rows.
    for (i = 0; i < argc; i++)
    {
        printf("%s: %s\n", col_name[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    // Return value must be 0 for SQLite.
    return 0;
}
