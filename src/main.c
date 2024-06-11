/*

CDbBirthday v1.2.0
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
#include "lib/menu.h"
#include "lib/dbsetup.h"

// Global variables:
int callb_called = 0; // SQL callback function call counter.
bool loop_active = true; // Boolean to keep main loop active.

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
