
#include "list.h"




// List "class"
struct list_type List = {
    .empty = list_empty,
    .of = list_of,
    .get = list_get,
    .getFirst = list_getFirst,
    .getLast = list_getLast,
    .getNext = list_getNext,
    .getPrev = list_getPrev,
    .addEnd = list_addEnd,
    .addFront = list_addFront,
    .insertBefore = list_insertBefore,
    .insertAfter = list_insertAfter,
    .insert = list_insert,
    .sort = list_sort,
    .size = list_size,
    .showAll = list_showAll
};


///////////////////////////////////////////////////////////////////////////////

/** Private class methods **/



// https://en.wikipedia.org/wiki/Quicksort
// https://www.tutorialspoint.com/data_structures_algorithms/quick_sort_algorithm.htm
struct node *partition( struct list *list,
                        struct node *lo,
                        struct node *hi,
                        DATA_COMPARATOR){

    struct node *pivot = hi;
    struct node *start = lo;
    struct node *end = hi->PREV;

    while( Node.indexOf(start) < Node.indexOf(end) ){
        if( compareData(Node.getData(start), Node.getData(pivot)) > 0 ){         // if start more then pivot
            if( compareData(Node.getData(pivot), Node.getData(end)) > 0 ){ Node.swapData(start, end); }
            else{ end = end->PREV; }
        }
        else{ start = start->NEXT; }               // if less then pivot update start
    }
    // at this point start and end is same node
    if( compareData(Node.getData(start), Node.getData(pivot)) > 0){ Node.swapData(start, pivot); }
    return start;
}

void quickSort( struct list *list,
                struct node *lo,
                struct node *hi,
                DATA_COMPARATOR){

    if( !(lo && hi) ){ return; }
    if( Node.indexOf(lo) < Node.indexOf(hi) ){
        struct node *p = partition(list, lo, hi, compareData);
        quickSort(list, lo, p->PREV, compareData);
        quickSort(list, p->NEXT, hi, compareData);
    }
}

// void swapData(struct node *n1, struct node *n2){
//     struct data *tmp = Node.getData(n1);
//     Node.setData( n1, Node.getData(n2) );
//     Node.setData( n2, tmp );
// }
//
// int compareBornDate(struct node *n1, struct node *n2){
//     return Node.getData(n1)->yearBorn -Node.getData(n2)->yearBorn;
// }
//
// int compareId(struct node* n1, struct node* n2){
//     return Node.getData(n1)->id -Node.getData(n2)->id;
// }

///////////////////////////////////////////////////////////////////////////////

struct list * list_empty(){
    struct list * this = (struct list*)(malloc(sizeof(struct list)));
    this->FIRST_NODE = NULL;
    // this->PREV_NODE = NULL;
    this->CURRENT_NODE = NULL;
    this->LAST_NODE = NULL;
    this->size = 0;

    return this;
}

struct list * list_of( struct data *data ){
    struct list * this = List.empty();
    struct node * newNode = Node.of(data);
    this->FIRST_NODE = newNode;
    // this->PREV_NODE = newNode;
    this->CURRENT_NODE = newNode;
    this->LAST_NODE = newNode;
    this->size = 1;

    return this;
}

struct data * list_get(struct list *this, int index ){
    if( index < 1 ){                            // negative or 0 (zero)
        this->CURRENT_NODE = this->FIRST_NODE;
        return Node.getData( this->CURRENT_NODE );
    }else if( (List.size(this) -1) <= index ){  // equals or bigger then (List.size -1)
        this->CURRENT_NODE = this->LAST_NODE;
        return Node.getData( this->CURRENT_NODE );
    }
    // else. start from begining by default
    this->CURRENT_NODE = this->FIRST_NODE;
    int i = 0, updater = 1, half = List.size(this) / 2;

    if( half <= index ){ // if index is in bigger half, start from the end.
        this->CURRENT_NODE = this->LAST_NODE;
        i = List.size(this) -1;
        updater = -1;
    }

    struct data *R = NULL;
    while( i != index ){
        i += updater;
        if( updater < 0 ){ R = List.getPrev(this); }
        else{ R = List.getNext(this); }
    }

    if( R == NULL ){ printf("NULL at index: %d\n", index); }
    return R;
}

struct data * list_getFirst(struct list *this ){
    this->CURRENT_NODE = this->FIRST_NODE;
    return Node.getData(this->CURRENT_NODE); // same as this->CURRENT_NODE->data
}

struct data * list_getLast(struct list *this ){
    this->CURRENT_NODE = this->LAST_NODE;
    return Node.getData(this->CURRENT_NODE);
}

struct data * list_getNext(struct list *this ){
    if( Node.hasNext(this->CURRENT_NODE) ){
        this->CURRENT_NODE = this->CURRENT_NODE->NEXT;
        // this->PREV_NODE = this->CURRENT_NODE->PREV;
        return Node.getData(this->CURRENT_NODE);
    }
    return NULL;
}

struct data * list_getPrev(struct list *this ){
    if( Node.hasPrev(this->CURRENT_NODE) ){
        this->CURRENT_NODE = this->CURRENT_NODE->PREV;
        // this->PREV_NODE = this->CURRENT_NODE->PREV;
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

bool list_insertAfter( struct list *this, struct data *data ){ // TODO: remove return type
    if( this->LAST_NODE == this->CURRENT_NODE ){
        list_addEnd(this, data);
    }else{
        Node.insertAfter(this->CURRENT_NODE, data);
        this->size++;
    }
}

bool list_insert( struct list *this, struct data *data, DATA_COMPARATOR ){
    struct node *tmp = Node.of(data);
    List.getFirst(this);        // resets CURRENT_NODE to first position
    while( Node.hasNext(this->CURRENT_NODE) ){
        if( compareData(Node.getData(tmp), Node.getData(this->CURRENT_NODE)) < 0 ){
            Node.insertBefore(this->CURRENT_NODE, data);
            this->size++;
            free(tmp);
            return true;
        }
        List.getNext(this);     // move CURRENT_NODE to next position
    }
    List.addEnd(this, data);
    free(tmp);
    return false;
}

void list_sort( struct list *this, DATA_COMPARATOR ){
    quickSort(this, this->FIRST_NODE, this->LAST_NODE, compareData);
}

// gets number of nodes in list
int list_size(struct list * this){ return this->size; }

void list_showAll( struct list *this ){
    List.getFirst(this);
    printf("%d, ", this->CURRENT_NODE->data->id);
    while( Node.hasNext(this->CURRENT_NODE) ){
        printf("%d, ", List.getNext(this)->id);
    }
    puts("");
}
