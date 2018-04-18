#include "db.h"

// DB "class"
struct db_type DataBase = {
    .empty = db_empty,
    .login = db_login,
    .addRecord = db_addRecord,
    .removeRecord = db_removeRecord,
    .getRecord = db_getRecord,
    .search = db_search,
    .save = db_save,
    .load = db_load,
    .showAll = db_showAll
};

struct db * db_empty(){
    struct db* this = (struct db*)malloc(sizeof(struct db));
    this->list = List.empty();
}

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
    return List.insertUnique(this->list, data, Data.compareId);
}

bool db_removeRecord(struct db *this, int id ){
    struct data * tmpData = Data.empty();
    tmpData->id = id;

    bool isOK = List.removeRecords(this->list, tmpData, Data.compareId);
    free(tmpData);
    tmpData = NULL;

    return isOK;
}

struct data * db_getRecord( struct db *this, int id ){
    List.getFirst(this->list);        // reset current node to first node
    struct node *currentNode = this->list->CURRENT_NODE;

    while( Node.hasNext(currentNode) ){
        if( Node.getData(currentNode)->id == id ){ return Node.getData(currentNode); }
        else if( Node.getData(currentNode)->id > id ){ return NULL; } // short circuit
        List.getNext(this->list);     // update current node
    }

    return NULL;
}



struct list * db_search( struct db *this, struct data *compareTo, DATA_PREDICATE, DATA_COMPARATOR ){
    struct list *R = List.empty();
    List.getFirst(this->list);        // reset current node to first node
    struct node **currentNode = &this->list->CURRENT_NODE;
    struct data *currentData = Node.getData(*currentNode);

    if( predicateData(currentData, compareTo, compareData) ){
        List.addEnd(R, currentData);
    }

    while( Node.hasNext(*currentNode) ){
        List.getNext(this->list);
        currentData = Node.getData(*currentNode);

        // printf("%d - %d = %d\n",currentData->id, compareTo->id, compareData(currentData, compareTo));

        if( predicateData(currentData, compareTo, compareData) ){
            List.addEnd(R, currentData);
        }

    }
    // if list empty( no maches found) return NULL.
    return List.isEmpty(R) ? NULL : R;
}

bool db_save( struct db *this, char *fileName ){
    List.saveToFile(this->list, fileName, Data.toData );
}

bool db_load( struct db *this, char *fileName ){
    FILE* pFile;
    pFile = fopen(fileName, "r");

    if( pFile == NULL ){ puts("The file could not be opened"); }
    else{
        char ch;
        char input[300];
        int numChar;
        int len, id, yearBorn, country, travelClass, travelFrequency, stayDuration;
        char str[30];
        // struct data* data = Data.empty();

        while( !feof(pFile) ){
            numChar = fscanf(pFile, "%s", input); // read first lins record

            if( numChar > 0 ){
                if( strchr(input, '#') ){       // skip comments (comment starts with '#')
                     fgets (input, 600, pFile);
                }
				else{
                    // printf("Input: %s\n", input);
                    // https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
                    struct data* data = Data.empty();    // data to be placed inside node in a list

                    // data->id = (int)strtol(input, NULL, 10); // convert string to int

                    // http://en.cppreference.com/w/c/string/byte/strtoimax
                    char* endptr;
                    data->id = strtoimax(input,&endptr,10);

                    fscanf(pFile, "%s", str);
                    data->name = (char*)malloc(sizeof(char)*strlen(str));
                    memcpy(data->name, str, strlen(str) +1);

                    fscanf(pFile, "%s", str);
                    data->surname = (char*)malloc(sizeof(char)*strlen(str));
                    memcpy(data->surname, str, strlen(str) +1);

                    fscanf(pFile, "%d", &data->yearBorn);

                    fscanf(pFile, "%s", str);
                    data->email = (char*)malloc(sizeof(char)*strlen(str));
                    memcpy(data->email, str, strlen(str) +1);

                    fscanf(pFile, "%d %d %d %d", &data->country, &data->travelClass, &data->travelFrequency, &data->stayDuration);

                    List.addEnd(this->list, data);

                    // printf("size: %d\n", List.size(this->list));
                    // printf("%d, %s, %s, %d, %s, %d, %d, %d, %d\n", data->id, data->name, data->surname, data->yearBorn, data->email, data->country, data->travelClass, data->travelFrequency, data->stayDuration);

                }
			}
		}
        fclose(pFile);
        return true;
    }
    return false;
}

void db_showAll( struct db *this ){
    List.showAll(this->list);
}
