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
    // .compareData = node_compareData,
    .totalNodes = 0
};

/** Private class methods **/

void node_swapData(struct node *n1, struct node *n2){
    struct data *tmp = Node.getData(n1);
    Node.setData( n1, Node.getData(n2) );
    Node.setData( n2, tmp );
}
//
// int compareBornDate(struct node *n1, struct node *n2){
//     return Node.getData(n1)->yearBorn -Node.getData(n2)->yearBorn;
// }
//
// int compareId(struct node* n1, struct node* n2){
//     return Node.getData(n1)->id -Node.getData(n2)->id;
// }


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

// int (*node_compareData( struct node*, struct node*))(COMPARATOR_DATA){
//     return
// }
