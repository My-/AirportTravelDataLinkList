
#ifndef LIST
#define LIST

#include "../Data/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string

// Node
struct node {
    struct data * data;
    struct node * PREV;
    struct node * NEXT;
    struct node_type * _it;
};

bool node_hasNext( struct node *this );
bool node_remove( struct node *this );

struct node_type {
    bool (*hasNext)( struct node *this );
    bool (*remove)( struct node *this );
    bool (*add)( struct node *this, struct data *data);
} Node;


// List
struct list {
    struct node * FIRST_NODE;
    struct node * PREV_NODE;
    struct node * CURRENT_NODE;
    struct node * LAST_NODE;
    struct list_type * _it;
};

struct list_type {
    struct list *(*of)( );
    struct node *(*get)(struct list *this);
    struct node *(*next)(struct list *this);
    bool (*hasNext)(struct list *this);
    bool (*add)( struct list *this, struct data *data );
    bool (*insert)(struct list *this, struct data *data );

    int (*size)(struct list * this);
} List;


// Stream
struct stream {
    struct list * list;
    struct stream_type * _it;
};

struct stream_type {
    void (*of)( struct list * list );

} Stream;

#endif
