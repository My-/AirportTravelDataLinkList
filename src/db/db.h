
#ifndef DB
#define DB

#include "../data/data.h"
#include "../list/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string

#define ADMIN_DATA_FILE "./res/admins.data"

struct db {
    struct list *list;
    struct db_type * _it;
};

bool db_login( struct db *this, char *username, char *password );
bool db_addRecord( struct db *this, struct data *data );
bool db_removeRecord(struct db *this, int id );
struct data * db_getRecord( struct db *this, int id );
struct list * db_search( struct db *this, int machValue, FILTER );
bool db_save( struct db *this, char *fileName );
bool db_load( struct db *this, char *fileName );
void db_showAll( struct db *this );
// void db_display( struct db *this, COMPARATOR_DATA ); // use List.showAll( DB.search( filter ) )

extern struct db_type {
    bool (*login)( struct db *this, char *username, char *password );
    bool (*addRecord)( struct db *this, struct data *data );
    bool (*removeRecord)(struct db *this, int id );
    struct data * (*getRecord)( struct db *this, int id );
    struct list * (*search)( struct db *this, int machValue, FILTER );
    bool (*save)( struct db *this, char *fileName );
    bool (*load)( struct db *this, char *fileName );
    void (*showAll)( struct db *this );
    // void (*display)( struct db *this, COMPARATOR_DATA );
} DB;


#endif
