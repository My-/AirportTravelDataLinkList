
#ifndef DB
#define DB

#include "../data/data.h"
#include "../list/list.h"
#include "../filter/filter.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
#include <inttypes.h>   // http://en.cppreference.com/w/c/string/byte/strtoimax

#define ADMIN_DATA_FILE "./res/admins.data"
#define DB_FILE "./res/passengers.txt"

struct db {
    struct list *list;
    struct db_type * _it;
};

// create empty DataBase
struct db * db_empty();
// login to DataBase
bool db_login( struct db *this, char *username, char *password );
// add record to DataBase
bool db_addRecord( struct db *this, struct data *data );
// delate record with given ID from DataBase
bool db_removeRecord(struct db *this, int id );
// get data from DataBase with ID
struct data * db_getRecord( struct db *this, int id );
// get list of all macing record in data base
struct list * db_search( struct db *this, struct data *matchData, DATA_PREDICATE, DATA_COMPARATOR );
// save DataBase to file
bool db_save( struct db *this, char *fileName );
// load from file
bool db_load( struct db *this, char *fileName );
// show all record in data base to shrean
void db_showAll( struct db *this );


extern struct db_type {
    struct db * (*empty)();
    bool (*login)( struct db *this, char *username, char *password );
    bool (*addRecord)( struct db *this, struct data *data );
    bool (*removeRecord)(struct db *this, int id );
    struct data * (*getRecord)( struct db *this, int id );
    struct list * (*search)( struct db *this, struct data *matchData, DATA_PREDICATE, DATA_COMPARATOR );
    bool (*save)( struct db *this, char *fileName );
    bool (*load)( struct db *this, char *fileName );
    void (*showAll)( struct db *this );
} DataBase;


#endif
