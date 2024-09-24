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

typedef struct Person {
    char nickname[BUFFER_LENGTH];
    char first_name[BUFFER_LENGTH];
    char last_name[BUFFER_LENGTH];
    char birth_date[DATE_LENGTH];
    char sql_stm[SQL_LENGTH]; // Array for the prepared SQL statement.
} Person;

#endif
