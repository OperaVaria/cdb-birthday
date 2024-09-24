/*

CDbBirthday v1.3.0
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
#include "dbsetup.h"
#include "menu.h"
// On Windows: include windows.h.
#ifdef _WIN32
    #include <windows.h>
#endif

// Global boolean to keep the main loop active
bool loop_active = true;

// Main function:
int main(void)
{   
    // On Windows: set console to Unicode.
    #ifdef _WIN32
        SetConsoleCP(65001);
        SetConsoleOutputCP(65001);
    #endif

    // Initial text.
    printf("CDbBirthday v1.3.0\n");
    printf("By OperaVaria\n\n");

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
