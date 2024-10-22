/*

menu.c

Functions connected to CLI menu operations.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <stdbool.h>
#include "dbop.h"
#include "dbsetup.h"
#include "input.h"
#include "macros.h"
#include "menu.h"
#include "types.h"

// Main option menu:
int select_menu(void)
{
    // Menu text.
    printf("CDbBirthday Main Menu\n");
    printf("\nSelect option:\n");
    printf("1) Add a birthday entry.\n");
    printf("2) Delete a birthday entry.\n");
    printf("3) Check if birthday entry exist.\n");
    printf("4) Check birthdays for current month.\n");
    printf("5) Check birthdays for today.\n");
    printf("6) List all birthday entries.\n");
    printf("7) Exit.\n\n");

    // Prompt for selection.
    int user_opt = get_int_prompt("Enter your choice (1-7): ");

    // Print newline if option between 1-7 selected.
    if (between(user_opt, 1, 7)) {printf("\n");}

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
        printf("Exiting...\n");
        loop_active = false;
        break;

    default:
        // Invalid selection.
        printf("Invalid option, try again!\n");
        break;
    }

    // Press return faux prompt.
    if (sel_opt != 7)
    {
        char ent_buff[5];
        get_str_prompt("Press ENTER to return.", ent_buff, 5);
    }

    // Clear screen.
    clrscr();
}
