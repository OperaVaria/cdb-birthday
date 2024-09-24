/*

menu.c

Functions connected to CLI menu operations.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "auxfunc.h"
#include "dbop.h"
#include "dbsetup.h"
#include "macros.h"
#include "menu.h"

// Main option menu:
int select_menu(void)
{   
    // Declare input buffer array.
    char buffer[5];

    // Initialize default user option value.
    int user_opt = 0;    

    // Menu text.
    printf("\nSelect option:\n");
    printf("1) Add a birthday entry.\n");
    printf("2) Delete a birthday entry.\n");
    printf("3) Check if birthday entry exist.\n");
    printf("4) Check birthdays for current month.\n");
    printf("5) Check birthdays for today.\n");
    printf("6) List all birthday entries.\n");
    printf("7) Exit.\n\n");

    // Get user input.
    printf("Enter your choice (1-7): ");
    char *raw_input = get_input(buffer, 5, stdin);
    sscanf(raw_input, "%d", &user_opt);

    // Print newline.
    printf("\n");

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
        // Add.
        sql_statement = add_setup(sql_statement);
        db_op(sql_statement, INSERT);
        break;

    case 2:
        // Delete.
        sql_statement = del_setup(sql_statement);
        db_op(sql_statement, DELETE);
        break;

    case 3:
        // Check single entry.
        sql_statement = check_entry_setup(sql_statement);
        db_op(sql_statement, SELECT);
        break;

    case 4:
        // Check current month.
        sql_statement = check_date_setup(sql_statement, MONTH);
        db_op(sql_statement, SELECT);
        break;

    case 5:
        // Check current day.
        sql_statement = check_date_setup(sql_statement, DAY);
        db_op(sql_statement, SELECT);
        break;

    case 6:
        // List all.
        sql_statement = list_all_setup(sql_statement);
        db_op(sql_statement, SELECT);
        break;

    case 7:
        // Exit.
        printf("Exiting...\n\n");
        loop_active = false;
        break;

    default:
        // Invalid selection.
        printf("Invalid option, try again!\n");
        break;
    }

    // Press return prompt.
    if (between(sel_opt, 1, 6))
    {
        // Faux fgets prompt.
        char *ent_buff = fgets_prompt("Press ENTER to continue.", 5);

        // Free memory.
        free(ent_buff);

        // Return message.
        printf("\nReturning to main menu...\n");
    }

    // Free memory.
    free(sql_statement);
}