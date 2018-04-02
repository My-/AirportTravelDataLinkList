
typedef struct data {
    int num;
    char* string;
    /** functions **/
    delete(): bool              // free memory
} Data = {
    0,
    NULL,
    .delete = data_delete_implementation
};

typedef struct node {
    Data* data;
    struct node* NEXT;
    struct node* PREV;
    /** functions **/
    set(Data*): bool            // Node.data = this.Data
}Node = {
    NULL,
    NULL,
    NULL,
    .set = node_set_implementation
};

typedef struct List {
    struct node* FIRST;
    struct node* PREVIOUS;
    struct node* CURRENT;
    struct node* LAST;
    /** functions **/
    get(): Data             // List.CURRENT-> Node.data
    next(): Node            // List.CURRENT = List.CURRENT-> Node.NEXT
    delete(): bool          // List.PREVIOUS-> Node.NEXT = List.CURRENT-> Node.NEXT
                            // ... List.CURRENT << free memory
                            // ... List.CURRENT = List.PREVIOUS
                            // ... List.PREVIOUS = List.CURRENT-> Node.PREV
    add(Node*): bool        // this.Node.PREV = List.LAST-> Node
                            // List.LAST -> Node.NEXT = this.Node
}

typedef struct Stream {

}

void main(){
    struct list * db = List.of(); // create empty list
    List.add(db, Data.of(1, "Aaran"));
    List.add(db, Data.of(2, "Brendon"));
    List.add(db, Data.of(3, "Cian"));



    Stream.filter(struct stream *this, bool (*filter)(struct data));

    struct stream * dbStream = Stream.of(db);
    Stream.fiter(dbStream, Filter.travelFrom(UK));
    Stream.fiter(dbStream, Filter.travelClass(FIRST));
    Stream.fiter(dbStream, Filter.stayDuration(LESS_3_DAYS));
    Stream.fiter(dbStream, Filter.travelFrequancy(LESS_3LESS_3_TIMES));

}
