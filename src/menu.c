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
#include "types.h"

// Main option menu:
int select_menu(void)
{   
    // Declare variables.
    char buffer[5];
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
    // Create Person struct instance.
    Person p1;

    // Call functions based on selected menu option.
    switch (sel_opt)
    {
    case 1:
        // Add.
        add_setup(&p1);
        db_op(p1.sql_stm, INSERT);
        break;

    case 2:
        // Delete.
        del_setup(&p1);
        db_op(p1.sql_stm, DELETE);
        break;

    case 3:
        // Check single entry.
        check_entry_setup(&p1);
        db_op(p1.sql_stm, SELECT);
        break;

    case 4:
        // Check current month.
        check_date_setup(&p1, MONTH);
        db_op(p1.sql_stm, SELECT);
        break;

    case 5:
        // Check current day.
        check_date_setup(&p1, DAY);
        db_op(p1.sql_stm, SELECT);
        break;

    case 6:
        // List all.
        list_all_setup(&p1);
        db_op(p1.sql_stm, SELECT);
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
        // Faux prompt.
        char ent_buff[5];
        printf("Press ENTER to continue.");
        get_input(ent_buff, 5, stdin);

        // Return message.
        printf("\nReturning to main menu...\n");
    }

}
