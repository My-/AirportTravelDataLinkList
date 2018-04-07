

#ifndef LINK_LIST
#define LINK_LIST

#include "../data/data.h"
#include "../node/node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string

// #define COMPARATOR_NODE int(*comparator)(struct node*, struct node*)
// #define COMPARATOR_DATA int(*comparator)(struct data*, struct data*)

// int compareBornDate(struct node *n1, struct node *n2);
// int compareId(struct node* n1, struct node* n2);
// void swapData(struct node *n1, struct node *n2);


// List "class"
struct list {
    struct node * FIRST_NODE;
    // struct node * PREV_NODE;
    struct node * CURRENT_NODE;
    struct node * LAST_NODE;
    int size;
    struct list_type * _it;
};

struct list * list_empty();
struct list * list_of( struct data *data );
struct data * list_get( struct list *this, int index );
struct data * list_getFirst( struct list *this );
struct data * list_getLast( struct list *this );
struct data * list_getNext( struct list *this );
struct data * list_getPrev( struct list *this );
bool list_addEnd( struct list *this, struct data *data );
bool list_addFront( struct list *this, struct data *data );
bool list_insertBefore( struct list *this, struct data *data );
bool list_insertAfter( struct list *this, struct data *data );
bool list_insertUnique( struct list *this, struct data *data, DATA_COMPARATOR );
void list_sort( struct list *this, DATA_COMPARATOR );
int list_size( struct list *this );
void list_showAll( struct list *this );

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
} List;


#endif
