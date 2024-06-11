/*

menu.c

Functions connected to CLI menu operations.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "macros.h"
#include "menu.h"

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