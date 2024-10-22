/*

input.h

Header file for input.c.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef INPUT_H
#define INPUT_H

// Header files.
#include <stdio.h>

// Function prototypes.
int get_input(char *output_arr, size_t arr_size, FILE *input_stream);
int get_int_prompt(const char *prompt);
void get_str_prompt(const char *prompt, char *output_arr, size_t arr_size);

#endif
