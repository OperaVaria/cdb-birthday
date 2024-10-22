/*

input.c

Functions related to user text input.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <stdlib.h>
#include <string.h>
#include "input.h"
#include "macros.h"

/* Custom fgets-like function: retrieves and stores input from
a stream to a character array. Takes the output char array pointer,
the size of the array, and the input stream as arguments. Returns status code. */
int get_input(char *output_arr, size_t arr_size, FILE *input_stream)
{
    // Initialize variables.
    int i = 0, l = --arr_size;
    char ch;

    // Read and store input until newline or endfile character encountered.
    while ((ch = getc(input_stream)) != '\n' && ch != EOF)
    {
        // If arr_size too short: error message, clear input buffer, return 1 (error).
        if (i == l)
        {
            fprintf(stderr, "Warning: input too long, string truncated.\n");
            while ((ch = getchar()) != '\n' && ch != EOF) { }
            return 1;
        }
        /* Else: normal operation
        (add to array, add null terminator to next, increment iterator). */
        else
        {
            output_arr[i] = ch;
            output_arr[i + 1] = '\0';
            i++;
        }
    }

    return 0;
}

/* Prompts the user to enter an integer.
Takes the prompt text as argument, returns input as int,
or returns -1 if error encountered. Uses the custom get_input function. */
int get_int_prompt(const char *prompt)
{
    // Declare variables.
    char buffer[5];
    int get_input_status = 0, input_int = 0;

    // Display prompt.
    printf(prompt);

    // Get input, convert to int.
    get_input_status = get_input(buffer, 5, stdin);
    sscanf(buffer, "%d", &input_int);

    /* If error encountered in get_input function:
    pass -1 as return value (invalid selection). */
    return (get_input_status == 0) ? input_int : -1;
}

/* Prompts the user for a string. Takes the prompt text, the output char array
pointer, and the size of the array as arguments. Uses the custom get_input function. */
void get_str_prompt(const char *prompt, char *output_arr, size_t arr_size)
{
    // Display prompt.
    printf(prompt);

    // Call get_input in a while loop till non overflown input is given:
    while (get_input(output_arr, arr_size, stdin) != 0)
    {
        printf("Please try again: ");
    }
}
