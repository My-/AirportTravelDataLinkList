
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
    .insertUnique = list_insertUnique,
    .sort = list_sort,
    .size = list_size,
    .showAll = list_showAll,
    .isEmpty = list_isEmpty,
    .search = list_search,
    .saveToFile = list_saveToFile,
    .removeRecords = list_removeRecords
};


///////////////////////////////////////////////////////////////////////////////


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

///////////////////////////////////////////////////////////////////////////////

struct list * list_empty(){
    struct list * this = (struct list*)(malloc(sizeof(struct list)));
    this->FIRST_NODE = NULL;
    this->CURRENT_NODE = NULL;
    this->LAST_NODE = NULL;
    this->size = 0;

    return this;
}

struct list * list_of( struct data *data ){
    struct list * this = List.empty();
    struct node * newNode = Node.of(data);
    this->FIRST_NODE = newNode;
    this->CURRENT_NODE = newNode;
    this->LAST_NODE = newNode;
    this->size = 1;

    return this;
}

// gets data from list at given index
struct data * list_get(struct list *this, int index ){
    if( index < 1 ){                            // negative or 0 (zero)
        this->CURRENT_NODE = this->FIRST_NODE;
        return Node.getData( this->CURRENT_NODE );
    }
    else if( (List.size(this) -1) <= index ){  // equals or bigger then (List.size -1)
        this->CURRENT_NODE = this->LAST_NODE;
        return Node.getData( this->CURRENT_NODE );
    }
    // else. start from begining by default...
    this->CURRENT_NODE = this->FIRST_NODE;
    int i = 0, updater = 1, half = List.size(this) / 2;

    if( half <= index ){ // ...if index is in bigger half, start from the end.
        this->CURRENT_NODE = this->LAST_NODE;
        i = List.size(this) -1;
        updater = -1;
    }

    // start from start/end and go towards middle
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
    if( list_isEmpty(this) ){ return NULL; }
    this->CURRENT_NODE = this->FIRST_NODE;
    return Node.getData(this->CURRENT_NODE); // same as this->CURRENT_NODE->data
}

struct data * list_getLast(struct list *this ){
    if( list_isEmpty(this) ){ return NULL; }
    this->CURRENT_NODE = this->LAST_NODE;
    return Node.getData(this->CURRENT_NODE);
}

struct data * list_getNext(struct list *this ){
    if( list_isEmpty(this) ){ return NULL; }
    if( Node.hasNext(this->CURRENT_NODE) ){
        this->CURRENT_NODE = this->CURRENT_NODE->NEXT;

        return Node.getData(this->CURRENT_NODE);
    }
    return NULL;
}

struct data * list_getPrev(struct list *this ){
    if( list_isEmpty(this) ){ return NULL; }
    if( Node.hasPrev(this->CURRENT_NODE) ){
        this->CURRENT_NODE = this->CURRENT_NODE->PREV;

        return Node.getData(this->CURRENT_NODE);
    }
    return NULL;
}

bool list_addEnd( struct list *this, struct data *data ){
    if( this->FIRST_NODE ){                 // not empty list
        Node.insertAfter(this->LAST_NODE, data);
        this->LAST_NODE = this->LAST_NODE->NEXT;
        this->size++;
    }
    else{ list_addFront(this, data); }      // empty list
}

bool list_addFront( struct list *this, struct data *data ){
    if( this->FIRST_NODE ){                 // not empty list
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

bool list_insertUnique( struct list *this, struct data *data, DATA_COMPARATOR ){
    if( List.isEmpty(this) ){
        List.addFront(this, data);
        return true;
    }
    // check first element
    if( compareData(data, List.getFirst(this)) < 0 ){    // resets current to first position
        List.addFront(this, data);
        return true;
    }

    // check all the rest
    while( Node.hasNext(this->CURRENT_NODE) ){
        List.getNext(this);     // move CURRENT_NODE to next position

        // printf("%d - %d = %d\n",data->id, this->CURRENT_NODE->data->id, compareData(data, Node.getData(this->CURRENT_NODE)));

        // if data to inserd is smaller then data on the current node, insert before it
        if( compareData(data, Node.getData(this->CURRENT_NODE)) < 0 ){
            Node.insertBefore(this->CURRENT_NODE, data);
            this->size++;
            return true;
        }
        else if( compareData(data, Node.getData(this->CURRENT_NODE)) == 0  ){
            return false; // not unique
        }
    }

    if( compareData(data, Node.getData(this->LAST_NODE)) == 0  ){ return false; }
    // handle last element
    List.addEnd(this, data);
    return false;
}

void list_sort( struct list *this, DATA_COMPARATOR ){
    quickSort(this, this->FIRST_NODE, this->LAST_NODE, compareData);
}

// gets number of nodes in list
int list_size(struct list * this){ return this->size; }

void list_showAll( struct list *this ){
    int index = 0;
    if( List.isEmpty(this) ){ puts("NULL list."); return; } // if list empty here is nothing to show

    struct data* data = List.getFirst(this);
    printf("[%d]: %-4d %-10s %-10s %5d %15s %2d %2d %2d %2d\n", index, data->id, data->name, data->surname, data->yearBorn, data->email, data->country, data->travelClass, data->travelFrequency, data->stayDuration);

    while( Node.hasNext(this->CURRENT_NODE) ){
        index++;
        data = List.getNext(this);
        printf("[%d]: %-4d %-10s %-10s %5d %15s %2d %2d %2d %2d\n", index, data->id, data->name, data->surname, data->yearBorn, data->email, data->country, data->travelClass, data->travelFrequency, data->stayDuration);
    }
}

bool list_isEmpty( struct list *this ){
    if( this == NULL ){ return true; }
    return this->FIRST_NODE == NULL;
}

struct list * list_search(  struct list *this,
                            struct data *compareTo,
                            DATA_PREDICATE,
                            DATA_COMPARATOR ){
    struct list *R = List.empty();
    List.getFirst(this);        // reset current node to first node
    struct node **currentNode = &this->CURRENT_NODE;
    struct data *currentData = Node.getData(*currentNode);

    // check first element. if matches add to list
    if( predicateData(currentData, compareTo, compareData) ){
        List.addEnd(R, currentData);
    }

    // check all the rest
    while( Node.hasNext(*currentNode) ){
        List.getNext(this);
        currentData = Node.getData(*currentNode);
        // add to list if maches
        if( predicateData(currentData, compareTo, compareData) ){
            List.addEnd(R, currentData);
        }

    }
    // if list empty( no maches found) return NULL.
    return List.isEmpty(R) ? NULL : R;
}

void list_saveToFile( struct list *this, char *fileName, DATA_STRINGIFY ){
    FILE* pFile;
    pFile = fopen(fileName, "w");

    if( !pFile ){ puts("The file could not be opened"); }
    else{
        struct data *tmpData;

        for( tmpData = List.getFirst(this); tmpData != NULL; tmpData = List.getNext(this) ){
            if( List.isEmpty(this) ){ puts("Empty list"); break; }
            fprintf( pFile,"%s", stringify(tmpData) );
            free(tmpData); // stringify creates new maclloc each call.
            tmpData = NULL;
        }

        fclose(pFile);
        free(tmpData);
        tmpData = NULL;
    }
}

bool list_removeRecords( struct list *this, struct data *matchData, DATA_COMPARATOR){
    bool R = false;
    struct data *currData;

    for( currData = List.getFirst(this); currData != NULL; currData = List.getNext(this) ){

        if( compareData(matchData, currData) == 0 ){
            // Only one Node in list
            if( this->FIRST_NODE == this->LAST_NODE ){
                this->LAST_NODE = NULL;
                this->FIRST_NODE = NULL;
                Node.remove(&this->CURRENT_NODE);
                this->CURRENT_NODE = NULL;
                R = true;
                continue;
            }

            // Deleteing first Node
            if( this->CURRENT_NODE == this->FIRST_NODE ){
                this->FIRST_NODE = this->FIRST_NODE->NEXT;
                Node.remove(&this->CURRENT_NODE);
                this->CURRENT_NODE = this->FIRST_NODE;
                R = true;
                continue;
            }

            // Deleting last Node
            if( this->CURRENT_NODE == this->LAST_NODE ){
                this->LAST_NODE = this->LAST_NODE->PREV;
                Node.remove(&this->CURRENT_NODE);
                this->CURRENT_NODE = this->LAST_NODE;
                R = true;
                continue;
            }

            // Deletin from middle
            struct node * prevNode = this->CURRENT_NODE->PREV;
            Node.remove(&this->CURRENT_NODE);
            this->CURRENT_NODE = prevNode;
            R = true;

        }//if (match)

    }// for Loop
    if( R ){ this->size--; }
    return R;
}// list_removeRecords()
