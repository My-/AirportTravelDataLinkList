#include "db.h"

// DB "class"
struct db_type DB {
    .login = db_login,
    .addRecord = db_addRecord,
    .removeRecord = db_removeRecord,
    .getRecord = db_getRecord,
    .search = db_search,
    .save = db_save,
    .load = db_load,
    .displayAll = db_displayAll
};

bool db_login( struct db *this, char *username, char *password ){
    int numChar;
    char readName[6], readPass[6];

    FILE* pFile;
    pFile = fopen(ADMIN_DATA_FILE, "r");

    if (pFile == NULL){ printf("Admin record file cannot be opened\n"); }
    else{
        while (!feof(pFile)) {
            numChar = fscanf(pFile, "%s %s", readName, readPass);
            if( strcmp(readName, username) == 0 ){
                if( strcmp(readPass, password) == 0 ){ return true; }
            }
            //if (numChar > 0){ printf("\t%s: %s\n", readName, readPass); }
        }
        fclose(pFile);
    }
    return false;
}

bool db_addRecord( struct db *this, struct data *data ){
    return List.insert(db->list, data, Data.compareId);
}

bool db_removeRecord(struct db *this, int id ){
    // TODO: delate record
}

struct data * db_getRecord( struct db *this, int id ){
    List.getFirst(db->list);        // reset current node to first node
    struct node *currentNode = db->list->CURRENT_NODE;

    while( Node.hasNext(currentNode) ){
        if( Node.getData(currentNode)->id == id ){ return Node.getData(currentNode); }
        else if( Node.getData(currentNode)->id > id ){ return NULL; } // short circuit
        List.getNext(db->list);     // update current node
    }

    return NULL;
}

struct list * db_search( struct db *this, int machValue, FILTER ){
    struct list *R = List.empty();
    List.getFirst(db->list);        // reset current node to first node
    struct node *currentNode = db->list->CURRENT_NODE;
    struct data *currentData;

    while( Node.hasNext(currentNode) ){
        currentData = Node.getData(currentNode);

        if( Filter.on(currentData, machValue, filter) ){
            List.addEnd(R, currentData);
        }
    }

    return R;
}

bool db_save( struct db *this, char *fileName ){

}

bool db_load( struct db *this, char *fileName ){

}

void db_showAll( struct db *this ){
    List.showAll(db->list);
}
