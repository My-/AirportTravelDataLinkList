#include "menu.h"

struct menu Menu = {
    .main = menu_main,
    .addRecord = menu_addRecord,
    .showAll = menu_showAll,
    .showOne = menu_showOne,
    .updateRecord = menu_updateRecord,
    .deleteRecord = menu_deleteRecord,
    .statistics = menu_statistics,
    .report = menu_report,
    .listOrdered = menu_listOrdered
};

void menu_main(struct db *db){
    int choice;
    do{
        puts("=======================================");
        puts("=     Main                            =");
        puts("=======================================");
        puts("[1] - Add passenger.");
        puts("[2] - Display all passengers to screen.");
        puts("[3] - Display one passenger details.");
        puts("[4] - Update passenger details.");
        puts("[5] - Delate passenger.");
        puts("[6] - Generate statistic.");
        puts("[7] - Report.");
        puts("[8] - List all the passenger of the...");
        puts("---------------------------------------");
        puts("[0] - Back.");
        puts("");
        scanf("%d", &choice);
        switch(choice){
            case 1: Menu.addRecord(db); break;
            case 2: DataBase.showAll(db); break;
            case 3: Menu.showOne(db); break;
            case 4: Menu.updateRecord(db); break;
            case 5: Menu.deleteRecord(db); break;
            case 6: Menu.statistics(db); break;
            case 7: Menu.report(db); break;
            case 8: Menu.listOrdered(db); break;
        }
    }while( choice );
}

/* ID */
int getId(struct db *db){
    int choice;
    struct data * tmpData = Data.empty();
    struct list * result;

    do{
        puts("\tId: ");
        scanf("%d", &choice);
        tmpData->id = choice;
        if( !choice ){ continue; } // id can't be 0 (zero)
        result = DataBase.search(db, tmpData, Data.equals, Data.compareId);
    }while( result != NULL ); // OK if no mach found, no records exist with this id. So while not empty (NULL) keep asking for id.
    // free memory
    free(tmpData);
    if( result ){ free(result); }

    return choice;
}

/* Pick Country */
int getCountry(){
    int choice;
    do{
        puts("\tCountry travelin from: ");
        puts("\t\t[1]: UK.");
        puts("\t\t[2]: Rest Europe.");
        puts("\t\t[3]: Asia.");
        puts("\t\t[4]: Americas.");
        puts("\t\t[5]: Australia.");
        scanf("%d", &choice);
    }while(choice < 1 || 5 < choice);

    return choice;
}

/* Travel Class */
int getTravelClass(){
    int choice;
    do{
        puts("\tTravel class:");
        puts("\t\t[1]: Economy class.");
        puts("\t\t[2]: Premium class.");
        puts("\t\t[3]: Business class.");
        puts("\t\t[4]: First class:");
        scanf("%d", &choice);
    }while(choice < 1 || 4 < choice);

    return choice;
}

/* Travel Frequency */
int getTravelFrequency(){
    int choice;
    do{
        puts("\tTravel frequency:");
        puts("\t\t[1]: 3 times and less.");
        puts("\t\t[2]: 5 times and less.");
        puts("\t\t[3]: more than 5 times.");
        scanf("%d", &choice);
    }while(choice < 1 || 3 < choice);

    return choice;
}

/* Stay Duration */
int getStayDuration(){
    int choice;
    do{
        puts("\tStay Duration:");
        puts("\t\t[1]: 1 day");
        puts("\t\t[2]: 3 days and less.");
        puts("\t\t[3]: 7 days and less.");
        puts("\t\t[4]: more than 7 days.");
        scanf("%d", &choice);
    }while(choice < 1 || 4 < choice);

    return choice;
}


void menu_addRecord(struct db* db){
    struct data* data = Data.empty();
    char str[30];
    int choice;

    puts("Enter passenger details:");

    data->id = getId(db); // set id

    /* Name */
    puts("\tName: ");
    scanf("%s", str);
    data->name = (char*)malloc(sizeof(char)*strlen(str));
    memcpy(data->name, str, strlen(str) +1);

    /* Surname */
    puts("\tSurname: ");
    scanf("%s", str);
    data->surname = (char*)malloc(sizeof(char)*strlen(str));
    memcpy(data->surname, str, strlen(str) +1);

    /* Year Born */
    puts("\tYear born: ");
    scanf("%d", &data->yearBorn);

    /* Email */
    do{
        puts("\tEmail: ");
        scanf("%s", str);
    }while(Data.setEmail(data, str));
    data->email = (char*)malloc(sizeof(char)*strlen(str));
    memcpy(data->email, str, strlen(str) +1);

    data->country = getCountry();
    data->travelClass = getTravelClass();
    data->travelFrequency = getTravelFrequency();
    data->stayDuration = getStayDuration();

    DataBase.addRecord(db, data);
}

void menu_showAll(struct db* db){
    puts("=======================================");
    puts("=     All Records in Data Base        =");
    puts("=======================================");
    List.showAll(db->list);
}

void menu_showOne(struct db* db){
    int choice;
    struct data * tmpData = Data.empty();
    struct list* result;
    do{
        puts("=======================================");
        puts("=     Show One                        =");
        puts("=======================================");
        puts("\nEnter ID ([0] - to exit):");
        scanf("%d", &choice);
        tmpData->id = choice;
        result = DataBase.search(db, tmpData, Data.equals, Data.compareId);

        if( List.isEmpty(result) ){ puts("No match found!"); }
        else if( List.size(result) > 1 ){ puts("ERROR! found more then one!"); }
        else{ List.showAll(result); }

    }while( choice );

    // free memory
    free(tmpData);
    if( result ){ free(result); }
}

void menu_updateRecord(struct db* db){
    int choice;
    struct data * tmpData = Data.empty();
    struct list* result;
    do{
        puts("=======================================");
        puts("=     Show One                        =");
        puts("=======================================");
        puts("\nEnter ID ([0] - to exit):");
        scanf("%d", &choice);
        tmpData->id = choice;
        result = DataBase.search(db, tmpData, Data.equals, Data.compareId);

        if( List.isEmpty(result) ){
            puts("No match found!");
        }
        else if( List.size(result) > 1 ){       // probably I should create log and brake program here.
            puts("ERROR! found more then one!");
        }
        else{

        }

    }while( choice );

    // free memory
    free(tmpData);
    if( result ){ free(result); }
}

void menu_deleteRecord(struct db* db){

}

void menu_statistics(struct db* db){

}

void menu_report(struct db* db){

}

void menu_listOrdered(struct db* db){

}
