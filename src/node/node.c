#include "node.h"
#include "../Data/data.c"

// Node "class"
struct node_type Node = {
    .of = node_of,
    .hasNext = node_hasNext,
    .remove = node_remove,
    .insertBefore = node_insertBefore,
    .insertAfter = node_insertAfter,
    .get = node_getData,
    .totalNodes = 0
};

struct node * node_of( struct data *data ){
    struct node * newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->PREV = NULL;
    newNode->NEXT = NULL;

    return newNode;
}

bool node_hasNext( struct node *this ){
    return this->NEXT != NULL;
}

bool node_hasNext( struct node *this ){
    return this->PREV != NULL;
}

void node_remove( struct node *this ){
    this->PREV->NEXT = this->NEXT;
    this->NEXT->PREV = this->PREV;
    Data.delete( this->data );
    free(this);
}

void node_insertBefore( struct node *this, struct data *data ){
    struct node * newNode = malloc(sizeof(struct node));
    newNode->data = data;

    if( this->PREV != NULL ){ newNode->PREV = this->PREV; }
    else{ newNode->PREV = NULL; }

    this->PREV = newNode;
    newNode->NEXT = this;
}

void node_insertAfter( struct node *this, struct data *data ){
    struct node * newNode = malloc(sizeof(struct node));
    newNode->data = data;

    if( this->NEXT != NULL ){ newNode->NEXT = this->NEXT; }
    else{ newNode->NEXT = NULL; }

    this->NEXT = newNode;
    newNode->PREV = this;
}

struct data * node_getData( struct node *this ){
    return this->data;
}
