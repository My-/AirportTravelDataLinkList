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
    .setData = node_setData,
    .indexOf = node_indexOf,
    .swapData = node_swapData,
    .totalNodes = 0
};

/** Private class methods **/

void node_swapData(struct node *n1, struct node *n2){
    struct data *tmp = Node.getData(n1);
    Node.setData( n1, Node.getData(n2) );
    Node.setData( n2, tmp );
}


/** Public class methods **/

struct node * node_of( struct data *data ){
    struct node * newNode = (struct node*)malloc(sizeof(struct node));
    newNode->data = data;
    newNode->PREV = NULL;
    newNode->NEXT = NULL;

    return newNode;
}

bool node_hasNext( struct node *this ){ return this->NEXT; }
bool node_hasPrev( struct node *this ){ return this->PREV; }

void node_remove( struct node *this ){  // TODO: fix it
    this->PREV->NEXT = this->NEXT;
    this->NEXT->PREV = this->PREV;
    Data.remove( this->data );
    free(this);
}

void node_insertBefore( struct node *this, struct data *data ){
    struct node * newNode = Node.of(data);
    if( this->PREV ){
        newNode->PREV = this->PREV;
        this->PREV->NEXT = newNode;
    }
    this->PREV = newNode;
    newNode->NEXT = this;
}

void node_insertAfter( struct node *this, struct data *data ){
    struct node * newNode = Node.of(data);
    if( this->NEXT ){
        newNode->NEXT = this->NEXT;
        // if( this->PREV ){ this->PREV->NEXT = newNode; }
        this->NEXT->PREV = newNode;
    }
    this->NEXT = newNode;
    newNode->PREV = this;
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
