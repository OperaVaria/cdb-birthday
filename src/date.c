/*

date.c

Functions related to date validation.

Part of the CDbBirthday project by OperaVaria.

*/

// Header files.
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include "date.h"
#include "macros.h"

// Static function prototypes.
static bool validate_date_form(const char *date_string);
static bool validate_date_values(const char *date_string);
static bool is_leap_year(int year);

/* Main date validation function. Calls subfunctions to determine if
a date is of a valid format and has correct values.
Takes a date string as argument, returns validation boolean. */
bool validate_date(const char *date_string)
{
    // Call functions. If any false: early false return.
    if (!validate_date_form(date_string)) {return false;}
    if (!validate_date_values(date_string)) {return false;}

    // Else (all true): return true.
    return true;
}

/* Checks correct length and character types in date string.
Takes a date string as argument, returns validation boolean. */
static bool validate_date_form(const char *date_string)
{
    // Check string length.
    if (strlen(date_string) != 10)
    {
        fprintf(stderr, "Error: Date input must be exactly 10 characters (YYYY.MM.DD).\n");
        return false;
    }

    // Check if each character is of the correct type (digit or separator).
    if (
        // Year
        !isdigit(date_string[0]) || !isdigit(date_string[1]) ||
        !isdigit(date_string[2]) || !isdigit(date_string[3]) ||
        // Separator
        date_string[4] != '.' ||
        // Month
        !isdigit(date_string[5]) || !isdigit(date_string[6]) ||
        // Separator
        date_string[7] != '.' ||
        // Day
        !isdigit(date_string[8]) || !isdigit(date_string[9])
       )
    {
        fprintf(stderr, "Error: Date must be in 'YYYY.MM.DD' format.\n");
        return false;
    }

    return true;
}

/* Checks if a date string in the YYYY.MM.DD format is a valid
date in the Gregorian calendar. Takes a date string as argument,
returns validation boolean.*/
static bool validate_date_values(const char *date_string)
{
    // Declare variables.
    int year, month, day, days_in_month;

    // Parse the date string.
    sscanf(date_string, "%d.%d.%d", &year, &month, &day);

    // Validate month.
    if (!(between(month, 1, 12)))
    {
        fprintf(stderr, "Error: Month number must be between 01 and 12.\n");
        return false;
    }

    // Calculate days in month.
    switch (month)
    {
    case APRIL: case JUNE: case SEPTEMBER: case NOVEMBER:
        days_in_month = 30;
        break;
    case FEBRUARY: // With leap year check.
        days_in_month = is_leap_year(year) ? 29 : 28;
        break;
    default: // January, March, May, July, August, October, December
        days_in_month = 31;
    }

    // Validate day.
    if (!(between(day, 1, days_in_month)))
    {
        fprintf(stderr, "Error: Invalid day for the given month and year.\n");
        return false;
    }

    return true;
}

/* Helper function to determine if a year is a leap year
(divisible by 4 but not by 100, or divisible by 400).
Takes year as int, returns boolean. */
static bool is_leap_year(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
