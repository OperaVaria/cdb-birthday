/*

macros.h

Header file containing global preprocessor constants and macros.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef MACROS_H
#define MACROS_H

// Header files.
#include <stdio.h>

/* CONSTANTS */

// SQL call type constants.
#define CREATE 1
#define INSERT 2
#define DELETE 3
#define SELECT 4

// Array lengths.
#define BUFFER_LENGTH 64
#define DATE_LENGTH 11
#define SQL_LENGTH 512

// Date specifier constants.
#define MONTH ".%m."
#define DAY ".%m.%d"

/* FUNCTION-LIKE MACROS */

// Is x value between two numbers.
#define between(x, a, b) (((a) <= (x)) && ((x) <= (b)))

// Screen clearing, uses ANSI escape codes.
#define clrscr() printf("\e[1;1H\e[2J")

#endif
