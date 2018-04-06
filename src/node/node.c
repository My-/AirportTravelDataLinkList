#include "node.h"


/** Private class methods **/

// void updateIndexes(struct node *node){
//     if( node->PREV ){ node->index = node->PREV->index +1; }
//     while( Node.hasNext(node) ){
//         node = node->NEXT;
//         node->index = node->PREV->index +1;
//     }
// }

// Node "class"
struct node_type Node = {
    .of = node_of,
    .hasNext = node_hasNext,
    .hasPrev = node_hasPrev,
    .remove = node_remove,
    .insertBefore = node_insertBefore,
    .insertAfter = node_insertAfter,
    .getData = node_getData,
    .setData = node_setData,
    .indexOf = node_indexOf,
    .totalNodes = 0
};


/** Public class methods **/

struct node * node_of( struct data *data ){
    struct node * newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->PREV = NULL;
    newNode->NEXT = NULL;
    // newNode->index = 0;

    return newNode;
}

bool node_hasNext( struct node *this ){
    return this->NEXT != NULL;
}

bool node_hasPrev( struct node *this ){
    return this->PREV != NULL;
}

void node_remove( struct node *this ){  // TODO: fix it
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
    // updateIndexes(newNode);
}

void node_insertAfter( struct node *this, struct data *data ){
    struct node * newNode = Node.of(data);
    if( this->NEXT ){
        newNode->NEXT = this->NEXT;
        if( this->PREV ){ this->PREV->NEXT = newNode; }
    }
    this->NEXT = newNode;
    newNode->PREV = this;
    // updateIndexes(newNode);
}

struct data * node_getData( struct node *this ){
    return this->data;
}

struct node * node_setData( struct node *this, struct data *data ){
    this->data = data;
    return this;
}

int node_indexOf(struct node *this){
    int index = 0;
    while( Node.hasPrev(this) ){
        index++;
        this = this->PREV;
    }
    return index;
}
