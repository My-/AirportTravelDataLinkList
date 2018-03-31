#ifndef ADMIN
#define ADMIN

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
#include <string.h>     // string

#define ADMIN_DATA_FILE "./res/admins.data"


/**
*   Checks if username and password are correct (excist in "admins.data" file).
*/
void adminLogin();

/*
*   Checks if username and password are correct (excist in "admins.data" file).
*   `adminLogin():bool` helper method
*/
bool adminLoginValidate(char *username, char *password);

char* takePassword();

#endif
