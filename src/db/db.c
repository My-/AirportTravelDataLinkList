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
    // TODO: delate record
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

struct list * db_search( struct db *this, int machValue, FILTER ){
    struct list *R = List.empty();
    List.getFirst(this->list);        // reset current node to first node
    struct node *currentNode = this->list->CURRENT_NODE;
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
    FILE* pFile;
    pFile = fopen(fileName, "w");

    if( !pFile ){ puts("The file could not be opened"); }
    else{

        fclose(pFile);
        return true;
    }
    return false;
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

        while( !feof(pFile) ){
            // puts("reading...");
			numChar = fscanf(pFile, "%s", input); // 35 = #
			// numChar = fscanf(pFile, "%c", &ch); // 35 = #
            // scanf(" %s(%d)", input, numChar);

			if( numChar > 0 ){
                if( strchr(input, '#') ){       // skip coments
                     // puts("comment");
                     fgets (input, 600, pFile);
                }
				else{
                    // printf("Input: %s\n", input);
                    // https://www.tutorialspoint.com/c_standard_library/c_function_memcpy.htm
                    struct data* data = Data.empty();
                    data->id = (int)strtol(input, NULL, 10);

                    fscanf(pFile, "%s", str);
                    data->name = (char*)malloc(sizeof(char)*strlen(str));
                    memcpy(data->name, str, strlen(str) +1);

                    fscanf(pFile, "%s", str);
                    data->surname = (char*)malloc(sizeof(char)*strlen(str));
                    memcpy(data->surname, str, strlen(str) +1);

                    // puts("data");
                    // puts(data->name);
                    // puts(data->surname);
                    fscanf(pFile, "%d", &data->yearBorn);

                    fscanf(pFile, "%s", str);
                    data->email = (char*)malloc(sizeof(char)*strlen(str));
                    memcpy(data->email, str, strlen(str) +1);

                    fscanf(pFile, "%d %d %d %d", &data->country, &data->travelClass, &data->travelFrequency, &data->stayDuration);

                    List.addEnd(this->list, data);

                    // printf("size: %d\n", List.size(this->list));
                    // printf("%d, %s, %s, %d, %s, %d, %d, %d, %d\n", data->id, data->name, data->surname, data->yearBorn, data->email, data->country, data->travelClass, data->travelFrequency, data->stayDuration);
                    // List.showAll(this->list);
                    // puts( Data.toString(Node.getData(this->list->CURRENT_NODE)));
                }

                // if( ch == '#' ){       // skip coments
                //      puts("comment");
                //      fgets (input, 600, pFile);
                // }
				// else{
                //     // printf("Input: %s\n", input);
                //     printf("Input: %d\n", (ch -'0'));
                //     fgets (input, 600, pFile);
                //
                // }
			}
		}
        fclose(pFile);
        // printf("size: %d\n", List.size(this->list));
        // List.showAll(this->list);
        return true;
    }
    return false;
}

void db_showAll( struct db *this ){
    List.showAll(this->list);
}
