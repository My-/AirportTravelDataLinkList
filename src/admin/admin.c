/**
*   @by Mindaugas Sarskus
*   @date 28/03/2018
*/

#include "admin.h"
#include <stdio.h>


/*
*   Checks if username and password are correct (excist in "admins.data" file).
*   `adminLogin():bool` helper method
*/
bool adminLoginValidate(char *username, char *password){
    int numChar;
    char readName[6], readPass[6];

    FILE* pFile;
    pFile = fopen(ADMIN_DATA_FILE, "r");

    if (pFile == NULL){ printf("Admin record file cannot be opened\n"); }
    else{

        while (!feof(pFile)) {
            numChar = fscanf(pFile, "%s %s", readName, readPass);

            if( strcmp(readName, username) == 0 ){
                if( strcmp(readPass, password) == 0 ){
                    return true;
                }
            }
            //if (numChar > 0){ printf("\t%s: %s\n", readName, readPass); }
        }
        fclose(pFile);
    }
    return false;
}


/**
*   Checks if username and password are correct (excist in "admins.data" file).
*/
char* adminLogin(){
    char * username = (char*)malloc(sizeof(char)*NAME_LEN);
    char password[10];

    printf("\tEnter username: ");
    scanf("%s", username);
    printf("\tEnter password: ");
    strcpy(password, takePassword());

    while( ! adminLoginValidate(username, password) ){
        printf("\nWorng username or password!\n");
        printf("\tEnter username: ");
        scanf("%s", username);
        printf("\tEnter password: ");
        strcpy(password, takePassword());
    }

    return username;
}

/**
*   Function resposible for getting user password
*/
char* takePassword(){
    // https://stackoverflow.com/questions/1798511/how-to-avoid-pressing-enter-with-getchar
    // http://codingstreet.com/c-code-to-hide-input-password/
    // https://stackoverflow.com/questions/6856635/hide-password-input-on-terminal
    char *pass = (char*)malloc(sizeof(char) * 10);
    // char pass[20];
    // int i = 0;
    // for ( ; i <= 6; i++){
    //     pass[i] = getch();
    //     if( pass[i] == 13 ){ break; }
    //     else{ printf("*"); }
    // }
    // pass[i] = '\0';
    // printf("\n");
    // printf("\n Your password is : %s",pass);
    scanf("%s", pass);
    return pass;
}
