
#ifndef NODE
#define NODE

#include "../data/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string

// Node "class"
struct node {
    struct data * data;         // pointer to nodes data
    struct node * PREV;         // pointer to previous node
    struct node * NEXT;         // pointer to next node
    int index;                  // index of node in list
    struct node_type * _it;     // pointer to nodes type
};

struct node * node_of( struct data *data );
bool node_hasNext( struct node *this );
bool node_hasPrev( struct node *this );
void node_remove( struct node *this );
void node_insertBefore( struct node *this, struct data *data );
void node_insertAfter( struct node *this, struct data *data );
struct data * node_getData( struct node *this );
struct node * node_setData( struct node *this, struct data *data );
int node_indexOf(struct node *this);

struct node_type {
    struct node * (*of)( struct data *data );
    bool (*hasNext)( struct node *this );
    bool (*hasPrev)( struct node *this );
    void (*remove)( struct node *this );
    void (*insertBefore)( struct node *this, struct data *data );
    void (*insertAfter)( struct node *this, struct data *data );
    struct data * (*getData)( struct node *this );
    struct node * (*setData)( struct node *this, struct data *data );
    int (*indexOf)(struct node *this);
    int totalNodes;
} Node;




// Stream "class"
// struct stream {
//     struct list * list;
//     struct stream_type * _it;
// };
//
// struct stream_type {
//     struct stream * (*of)( struct list *list );
//     struct stream * (*filter)( struct stream *this, struct filter *filter );
//
// } Stream;

#endif
