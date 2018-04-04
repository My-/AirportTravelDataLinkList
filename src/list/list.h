

#ifndef LINK_LIST
#define LINK_LIST

#include "../data/data.h"
#include "../node/node.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string

// List "class"
struct list {
    struct node * FIRST_NODE;
    struct node * PREV_NODE;
    struct node * CURRENT_NODE;
    struct node * LAST_NODE;
    int size;
    struct list_type * _it;
};

struct list * list_empty();
struct list * list_of( struct data *data );
struct data * list_get(struct list *this );
struct data * list_next(struct list *this );
struct data * list_prev(struct list *this );
bool list_addEnd( struct list *this, struct data *data );
bool list_addFront( struct list *this, struct data *data );
bool list_insertBefore( struct list *this, struct data *data );
bool list_insertAfter( struct list *this, struct data *data );
int list_size(struct list * this);

extern struct list_type {
    struct list * (*empty)();
    struct list * (*of)( struct data *data );
    struct data * (*get)(struct list *this );
    struct data * (*next)(struct list *this );
    struct data * (*prev)(struct list *this );
    bool (*addEnd)( struct list *this, struct data *data );
    bool (*addFront)( struct list *this, struct data *data );
    bool (*insertBefore)( struct list *this, struct data *data );
    bool (*insertAfter)( struct list *this, struct data *data );
    int (*size)(struct list * this);
} List;


#endif
