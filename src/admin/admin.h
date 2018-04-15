/**
*   @by Mindaugas Sarskus
*   @date 28/03/2018
*/


#ifndef ADMIN
#define ADMIN

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
#include <string.h>     // string

#define ADMIN_DATA_FILE "./res/admins.data"
#define NAME_LEN 6

/**
*   Checks if username and password are correct (excist in "admins.data" file).
*/
char* adminLogin();

/*
*   Checks if username and password are correct (excist in "admins.data" file).
*   `adminLogin():bool` helper method
*/
bool adminLoginValidate(char *username, char *password);

/**
*   Function resposible for getting user password
*/
char* takePassword();

#endif
