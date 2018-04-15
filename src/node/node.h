
#ifndef NODE
#define NODE

#include "../data/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string

// #define COMPARATOR_NODE int(*node_comparator)(struct node*, struct node*)



// Node "class"
struct node {
    struct data * data;         // pointer to nodes data
    struct node * PREV;         // pointer to previous node
    struct node * NEXT;         // pointer to next node
    // int index;                  // index of node in list
    struct node_type * _it;     // pointer to nodes type
};

// int compareBornDate(struct node *n1, struct node *n2);
// int compareId(struct node* n1, struct node* n2);


struct node * node_of( struct data *data );
bool node_hasNext( struct node *this );
bool node_hasPrev( struct node *this );
void node_remove( struct node **this );
void node_insertBefore( struct node *this, struct data *data );
void node_insertAfter( struct node *this, struct data *data );
struct data * node_getData( struct node *this );
struct node * node_setData( struct node *this, struct data *data );
int node_indexOf(struct node *this);
void node_swapData(struct node *n1, struct node *n2);
// int (*node_compareData( struct node*, struct node*))(COMPARATOR_DATA);

struct node_type {
    struct node * (*of)( struct data *data );
    bool (*hasNext)( struct node *this );
    bool (*hasPrev)( struct node *this );
    void (*remove)( struct node **this );
    void (*insertBefore)( struct node *this, struct data *data );
    void (*insertAfter)( struct node *this, struct data *data );
    struct data * (*getData)( struct node *this );
    struct node * (*setData)( struct node *this, struct data *data );
    int (*indexOf)(struct node *this);
    void (*swapData)(struct node *n1, struct node *n2);
    // int (*((*node_compareData)( struct node*, struct node*)))(COMPARATOR_DATA);
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
