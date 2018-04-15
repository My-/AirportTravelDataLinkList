/**
*   @by: Mindaugas Sharskus
*   @date: 16/04/2018
*/

#ifndef LINK_LIST
#define LINK_LIST

#include "../data/data.h"
#include "../node/node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean


// List "class"
struct list {
    struct node * FIRST_NODE;
    // struct node * PREV_NODE;
    struct node * CURRENT_NODE; // pointer to the node whitch is used for selecting node we work on
    struct node * LAST_NODE;
    int size;   // list size(node count in list)
    struct list_type * _it;
};
// crate list
struct list * list_empty();
struct list * list_of( struct data *data );
// get data from list
struct data * list_get( struct list *this, int index );
struct data * list_getFirst( struct list *this );
struct data * list_getLast( struct list *this );
struct data * list_getNext( struct list *this );
struct data * list_getPrev( struct list *this );
// add data to list
bool list_addEnd( struct list *this, struct data *data );
bool list_addFront( struct list *this, struct data *data );
bool list_insertBefore( struct list *this, struct data *data );
bool list_insertAfter( struct list *this, struct data *data );
bool list_insertUnique( struct list *this, struct data *data, DATA_COMPARATOR );
// sort list
void list_sort( struct list *this, DATA_COMPARATOR );
// get size of the list
int list_size( struct list *this );
// show all list data to screan
void list_showAll( struct list *this );
// check if list has no data
bool list_isEmpty( struct list *this );
// search list based on predicate (<, =, >) and comparator. returns new list
struct list * list_search( struct list *this, struct data *matchData, DATA_PREDICATE, DATA_COMPARATOR );
// saves list to file with given name
void list_saveToFile( struct list *this, char *fileName, DATA_STRINGIFY );
// removes all records which maches given machesData on given comparator
bool list_removeRecords( struct list *this, struct data *matchData, DATA_COMPARATOR);


extern struct list_type {
    struct list * (*empty)(void);
    struct list * (*of)( struct data *data );
    struct data * (*get)( struct list *this, int index );
    struct data * (*getFirst)( struct list *this );
    struct data * (*getLast)( struct list *this );
    struct data * (*getNext)( struct list *this );
    struct data * (*getPrev)( struct list *this );
    bool (*addEnd)( struct list *this, struct data *data );
    bool (*addFront)( struct list *this, struct data *data );
    bool (*insertBefore)( struct list *this, struct data *data );
    bool (*insertAfter)( struct list *this, struct data *data );
    bool (*insertUnique)( struct list *this, struct data *data, DATA_COMPARATOR );
    void (*sort)( struct list *this, DATA_COMPARATOR );
    int (*size)(struct list * this);
    void (*showAll)( struct list *this );
    bool (*isEmpty)( struct list *this );
    struct list * (*search)( struct list *this, struct data *matchData, DATA_PREDICATE, DATA_COMPARATOR );
    void (*saveToFile)( struct list *this, char *fileName, DATA_STRINGIFY );
    bool (*removeRecords)( struct list *this, struct data *matchData, DATA_COMPARATOR);
} List;


#endif
