/*

auxfunc.c

Auxilary functions.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxfunc.h"
#include "macros.h"

/* Custom fgets-like function: retrieves and stores input from
a stream to a character array. */
char *get_input(char *output_str, int arr_length, FILE *input_stream)
{
    // Declare variables.
    char ch;
    int i = 0;
    int l = --arr_length;

    // Read and store input until newline or endfile character encountered.
    while ((ch = getc(input_stream)) != '\n' && ch != EOF)
    {
        // If arr_length too short: error message, clear input buffer.
        if (l == i)
        {
            fprintf(stderr, "Warning: input too long. String truncated.\n");
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            break;
        }
        // Else: normal operation (add to array, increment iterator).
        else
        {
            output_str[i] = ch;
            i++;
        }
    }

    // Add null terminator to end of string.
    output_str[i] = '\0';

    return output_str;
}

// Validate if user input date is of the correct format (yyyy.mm.dd).
bool validate_date_form(char input_string[])
{
    if (strlen(input_string) != 10)  return false; 
    if (!isdigit(input_string[0]))  return false; 
    if (!isdigit(input_string[1]))  return false;
    if (!isdigit(input_string[2]))  return false; 
    if (!isdigit(input_string[3]))  return false;
    if (input_string[4] != '.')     return false; 
    if (!isdigit(input_string[5]))  return false; 
    if (!isdigit(input_string[6]))  return false;
    if (input_string[7] != '.')     return false; 
    if (!isdigit(input_string[8]))  return false; 
    if (!isdigit(input_string[9]))  return false;
    return true;
}
