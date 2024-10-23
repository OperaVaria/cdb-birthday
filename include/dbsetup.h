/*

dbsetup.h

Header file for dbsetup.c.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef DBSETUP_H
#define DBSETUP_H

// Header files.
#include "types.h"

// Function prototypes.
void add_setup(Person *struct_ptr);
void del_setup(Person *struct_ptr);
void check_entry_setup(Person *struct_ptr);
void check_date_setup(Person *struct_ptr, const char *date_spec);
void list_all_setup(Person *struct_ptr);
void create_table(void);

#endif
