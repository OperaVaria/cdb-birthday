/* 

macros.h

Header file containing global preprocessor constants,
and macros.

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

// SQL statement max length.
#define MAX_LENGTH 256

// Date specifier constants.
#define MONTH ".%m."
#define DAY ".%m.%d"

// Function-like macros.
#define between(x, a, b)  (((a) <= (x)) && ((x) <= (b)))

#endif
