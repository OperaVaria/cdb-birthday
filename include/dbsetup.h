/*

dbsetup.h

Header file for dbsetup.c.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef DBSETUP_H
#define DBSETUP_H

// Function prototypes.
char *add_setup(char *sql_statement);
char *del_setup(char *sql_statement);
char *check_entry_setup(char *sql_statement);
char *check_date_setup(char *sql_statement, char date_spec[]);
char *list_all_setup(char *sql_statement);
void create_table(void);

#endif
