/*

menu.h

Header file for menu.c.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef MENU_H
#define MENU_H

// Include global variable (from main.c).
extern bool loop_active;

// Function prototypes.
int select_menu(void);
void main_switch(int sel_opt);

#endif
