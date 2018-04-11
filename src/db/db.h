
#ifndef DB
#define DB

#include "../data/data.h"
#include "../list/list.h"
#include "../filter/filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string

#define ADMIN_DATA_FILE "./res/admins.data"
#define DB_FILE "./res/passengers.txt"

struct db {
    struct list *list;
    struct db_type * _it;
};

struct db * db_empty();
bool db_login( struct db *this, char *username, char *password );
bool db_addRecord( struct db *this, struct data *data );
bool db_removeRecord(struct db *this, int id );
struct data * db_getRecord( struct db *this, int id );
// struct list * db_search( struct db *this, struct data *matchData, DATA_COMPARATOR );
struct list * db_search( struct db *this, struct data *matchData, DATA_PREDICATE, DATA_COMPARATOR );
bool db_save( struct db *this, char *fileName );
bool db_load( struct db *this, char *fileName );
void db_showAll( struct db *this );
// void db_display( struct db *this, COMPARATOR_DATA ); // use List.showAll( DB.search( filter ) )


// void adminLogin();

extern struct db_type {
    struct db * (*empty)();
    bool (*login)( struct db *this, char *username, char *password );
    bool (*addRecord)( struct db *this, struct data *data );
    bool (*removeRecord)(struct db *this, int id );
    struct data * (*getRecord)( struct db *this, int id );
    // struct list * (*search)( struct db *this, struct data *matchData, DATA_COMPARATOR );
    struct list * (*search)( struct db *this, struct data *matchData, DATA_PREDICATE, DATA_COMPARATOR );
    bool (*save)( struct db *this, char *fileName );
    bool (*load)( struct db *this, char *fileName );
    void (*showAll)( struct db *this );
    // void (*display)( struct db *this, COMPARATOR_DATA );
} DataBase;


#endif
