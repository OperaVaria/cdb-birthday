/*

auxfunc.c

Auxilary functions.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "auxfunc.h"
#include "macros.h"

// String retrieval prompt with fgets.
char *fgets_prompt (char prompt[], int string_size) {

    // Declare pointer.
    char* buffer;

    // Allocate memory.
    buffer = malloc(sizeof(char) * string_size);
    if (buffer == NULL)
    {
        fprintf(stderr, "Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    // Display prompt.
    printf("%s", prompt);  

    // Store input.
    fgets(buffer, string_size, stdin);

    // Clear stdin buffer if more characters than the variable size entered.
    if (buffer[strlen(buffer) - 1] != '\n')
    {
        int c = 0;
        while ((c = getchar()) != '\n' && c != EOF) { }
    }
    // Otherwise truncate newline from string.
    else
    {
        buffer[strcspn(buffer, "\n")] = 0;
    }
    
    // Return stored input string.
    return buffer;
}