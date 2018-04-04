
#include "list.h"
// #include "../Data/data.c"

// List "class"
struct list_type List = {
    .empty = list_empty,
    .of = list_of,
    .get = list_get,
    .next = list_next,
    .prev = list_prev,
    .addEnd = list_addEnd,
    .addFront = list_addFront,
    .insertBefore = list_insertBefore,
    .insertAfter = list_insertAfter,
    .size = list_size
};

struct list * list_empty(){
    struct list * this = (struct list*)(malloc(sizeof(struct list)));
    this->FIRST_NODE = NULL;
    this->PREV_NODE = NULL;
    this->CURRENT_NODE = NULL;
    this->LAST_NODE = NULL;
    this->size = 0;

    return this;
}

struct list * list_of( struct data *data ){
    struct list * this = List.empty();
    struct node * newNode = Node.of(data);
    this->FIRST_NODE = newNode;
    this->PREV_NODE = newNode;
    this->CURRENT_NODE = newNode;
    this->LAST_NODE = newNode;
    this->size = 1;

    return this;
}

struct data * list_get(struct list *this ){
    return Node.getData(this->CURRENT_NODE); // same as this->CURRENT_NODE->data
}

struct data * list_next(struct list *this ){
    if( Node.hasNext(this->CURRENT_NODE) ){
        this->CURRENT_NODE = this->CURRENT_NODE->NEXT;
        this->PREV_NODE = this->CURRENT_NODE->PREV;
        return Node.getData(this->CURRENT_NODE);
    }
    return NULL;
}

struct data * list_prev(struct list *this ){
    if( Node.hasPrev(this->CURRENT_NODE) ){
        this->CURRENT_NODE = this->CURRENT_NODE->PREV;
        this->PREV_NODE = this->CURRENT_NODE->PREV;
        return Node.getData(this->CURRENT_NODE);
    }
    return NULL;
}

bool list_addEnd( struct list *this, struct data *data ){
    if( this->FIRST_NODE != NULL ){         // not empty list
        Node.insertAfter(this->LAST_NODE, data);
        this->LAST_NODE = this->LAST_NODE->NEXT;
        this->size++;
    }
    else{ list_addFront(this, data); }      // empty list
}

bool list_addFront( struct list *this, struct data *data ){
    if( this->FIRST_NODE != NULL ){         // not empty list
        Node.insertBefore(this->FIRST_NODE, data);
        this->FIRST_NODE = this->FIRST_NODE->PREV;
        this->size++;
    }else{                                  // empty list
        struct node * newNode = Node.of(data);
        this->FIRST_NODE = newNode;
        this->CURRENT_NODE = newNode;
        this->LAST_NODE = newNode;
        this->size = 1;
    }
}

bool list_insertBefore( struct list *this, struct data *data ){
    if( this->FIRST_NODE == this->CURRENT_NODE ){
        list_addFront(this, data);
    }else{
        Node.insertBefore(this->CURRENT_NODE, data);
        this->size++;
    }
}

bool list_insertAfter( struct list *this, struct data *data ){
    if( this->LAST_NODE == this->CURRENT_NODE ){
        list_addEnd(this, data);
    }else{
        Node.insertAfter(this->CURRENT_NODE, data);        
        this->size++;
    }
}

// gets number of nodes in list
int list_size(struct list * this){ return this->size; }
