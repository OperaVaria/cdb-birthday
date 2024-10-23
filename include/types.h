/*

types.h

Header file containing custom types.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef TYPES_H
#define TYPES_H

// Header files.
#include "macros.h"

// Struc to store name and birthday data for a person.
typedef struct Person
{
    char nickname[BUFFER_LENGTH];
    char first_name[BUFFER_LENGTH];
    char last_name[BUFFER_LENGTH];
    char birth_date[DATE_LENGTH];
    char sql_stm[SQL_LENGTH]; // Array for the prepared SQL statement.
} Person;

// Enumerations for input error statuses.
typedef enum InputError
{
    INPUT_SUCCESS = 0,
    INPUT_OVERFLOW = 1,
    INPUT_EMPTY = 2,
    INPUT_INVALID = -1
} InputError;

// Months of the year enumerations.
typedef enum Month
{
    JANUARY = 1,
    FEBRUARY,
    MARCH,
    APRIL,
    MAY,
    JUNE,
    JULY,
    AUGUST,
    SEPTEMBER,
    OCTOBER,
    NOVEMBER,
    DECEMBER
} Month;

#endif
