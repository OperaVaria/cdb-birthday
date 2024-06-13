/*

auxfunc.h

Header file for auxfunc.c.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef AUXFUNC_H
#define AUXFUNC_H

// Header files.
#include <stdbool.h>

// Function prototypes.
char *fgets_prompt(char prompt[], int string_size);
bool validate_date_form(char input_string[]);

#endif
