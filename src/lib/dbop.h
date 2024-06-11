/*

dbop.h

Header file for dbop.c.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef DBOP_H
#define DBOP_H

// External global variable (main.c).
extern int callb_called = 0;

// Function prototypes.
void db_op(char *sql_statement, int call_type);

#endif
