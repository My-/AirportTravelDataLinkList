
#ifndef NODE
#define NODE

#include "../data/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean

// Node "class"
struct node {
    struct data * data;         // pointer to nodes data
    struct node * PREV;         // pointer to previous node
    struct node * NEXT;         // pointer to next node
    struct node_type * _it;     // pointer to nodes type
};

// creates new Node
struct node * node_of( struct data *data );
// checks for availability
bool node_hasNext( struct node *this );
bool node_hasPrev( struct node *this );
// remove Node(calls remove data inside)
void node_remove( struct node **this );
// add new node
void node_insertBefore( struct node *this, struct data *data );
void node_insertAfter( struct node *this, struct data *data );
// gets node data
struct data * node_getData( struct node *this );
struct node * node_setData( struct node *this, struct data *data );
// gets ingex of given node. O(n).
int node_indexOf(struct node *this);
// swaps data of two given nodes
void node_swapData(struct node *n1, struct node *n2);

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
    int totalNodes; // total nodes globaly (in all lists, not only in the current)
} Node;

#endif
