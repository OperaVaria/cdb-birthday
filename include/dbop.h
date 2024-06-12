/*

dbop.h

Header file for dbop.c.

Part of the CDbBirthday project by OperaVaria.

*/

// Guard.
#ifndef DBOP_H
#define DBOP_H

// Include global variable (from main.c).
extern int callb_called;

// Function prototypes.
void db_op(char *sql_statement, int call_type);

#endif
