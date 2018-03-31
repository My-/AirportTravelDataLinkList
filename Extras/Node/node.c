#include "node.h"

struct node_type Node = {
    .hasNext = node_hasNext,
    .remove = node_remove,
    .add = node_add
};

bool node_hasNext( struct node *this ){
    return this->NEXT != NULL;
}

bool node_remove( struct node *this ){
    this->PREV->NEXT = this->NEXT;
    this->NEXT->PREV = this->PREV;
    Data.delete( this->data );
    free(this);
}

struct list_type List = {
    .of = list_of,
    .get = list_get,
    .next = list_next,
    .hasNext = list_hasNext,
    .add = list_add,
    .insert = list_insert,

    .size = list_size
};
