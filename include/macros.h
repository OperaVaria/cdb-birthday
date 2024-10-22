/*

macros.h

Header file containing global preprocessor constants and macros.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef MACROS_H
#define MACROS_H

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

// Months of the year.
#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

// Function-like macros.
#define between(x, a, b) (((a) <= (x)) && ((x) <= (b)))

#endif
