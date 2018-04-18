

#ifndef MENU
#define MENU

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
#include <time.h>
#include "../db/db.h"

void appendToFile(char* filename, char *str);

void menu_main(struct db* db);
void menu_addRecord(struct db* db);
void menu_showAll(struct db* db);
void menu_showOne(struct db* db);
void menu_updateRecord(struct db* db);
void menu_deleteRecord(struct db* db);
void menu_statistics(struct db* db);
void menu_report(struct db* db);
void menu_listOrdered(struct db* db);

char *currentTime();

extern struct menu {
    void (*main)(struct db*);
    void (*addRecord)(struct db*);
    void (*showAll)(struct db*);
    void (*showOne)(struct db*);
    void (*updateRecord)(struct db*);
    void (*deleteRecord)(struct db*);
    void (*statistics)(struct db*);
    void (*report)(struct db*);
    void (*listOrdered)(struct db*);
} Menu;


#endif
