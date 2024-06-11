/* 

menu.h

Header file for menu.c.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef MENU_H
#define MENU_H

// External global variable (main.c).
extern bool loop_active = true;

// Function prototypes.
int select_menu(void);
void main_switch(int sel_opt);

#endif
