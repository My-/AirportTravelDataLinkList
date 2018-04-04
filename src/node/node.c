#include "node.h"

// Node "class"
struct node_type Node = {
    .of = node_of,
    .hasNext = node_hasNext,
    .hasPrev = node_hasPrev,
    .remove = node_remove,
    .insertBefore = node_insertBefore,
    .insertAfter = node_insertAfter,
    .getData = node_getData,
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

bool node_hasPrev( struct node *this ){
    return this->PREV != NULL;
}

void node_remove( struct node *this ){
    this->PREV->NEXT = this->NEXT;
    this->NEXT->PREV = this->PREV;
    Data.delete( this->data );
    free(this);
}

void node_insertBefore( struct node *this, struct data *data ){
    struct node * newNode = Node.of(data);
    if( this->PREV ){
        newNode->PREV = this->PREV;
        if( this->PREV ){ this->PREV->NEXT = newNode; }        
    }
    this->PREV = newNode;
    newNode->NEXT = this;
}

void node_insertAfter( struct node *this, struct data *data ){
    struct node * newNode = Node.of(data);
    if( this->NEXT ){
        newNode->NEXT = this->NEXT;
        if( this->PREV ){ this->PREV->NEXT = newNode; }
    }
    this->NEXT = newNode;
    newNode->PREV = this;
}

struct data * node_getData( struct node *this ){
    return this->data;
}
