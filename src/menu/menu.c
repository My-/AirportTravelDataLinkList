#include "menu.h"


// https://en.wikipedia.org/wiki/C_date_and_time_functions
char *currentTime(){
    time_t current_time;
    char* c_time_string;

    /* Obtain current time. */
    current_time = time(NULL);

    if( current_time == ((time_t)-1) ){
        (void) fprintf(stderr, "Failure to obtain the current time.\n");
    }

    /* Convert to local time format. */
    c_time_string = ctime(&current_time);

    if( c_time_string == NULL ){
        (void) fprintf(stderr, "Failure to convert the current time.\n");
    }

    for(int i = 0; i < strlen(c_time_string); i++){
        if( c_time_string[i] == ' ' ){ c_time_string[i] = '_'; }
    }

    /* Print to stdout. ctime() has already added a terminating newline character. */
    // (void) printf("Current time is %s", c_time_string);
    return c_time_string;
}


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
        puts("\n=======================================");
        puts("=     Main                            =");
        puts("=======================================");
        puts("[1] - Add passenger.");
        puts("[2] - Display all passengers to screen.");
        puts("[3] - Display one passenger details.");
        puts("[4] - Update passenger details.");
        puts("[5] - Delate passenger.");
        puts("[6] - Generate statistic...");
        puts("[7] - Report...");
        puts("[8] - List all the passengers from UK (sort)...");
        puts("---------------------------------------");
        puts("[0] - Back.");
        puts("");
        scanf("%d", &choice);
        switch(choice){
            case 1: Menu.addRecord(db); break;
            case 2:
                puts("=======================================");
                puts("=     All Records in DB               =");
                puts("=======================================");
                DataBase.showAll(db);
                puts("\n");
                break;
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
int getId(struct db *db){       //TODO: show note if id exist
    int choice;
    struct data * tmpData = Data.empty();
    struct list * result = List.empty(); // initialized, because free function brakes everything if here no records in DB.

    do{
        puts("\tId: ");
        scanf("%d", &choice);
        tmpData->id = choice;
        if( !choice ){ continue; } // id can't be 0 (zero)
        if( List.isEmpty(db->list) ){ break; }
        result = DataBase.search(db, tmpData, Data.equals, Data.compareId);
    }while( result != NULL ); // OK if no mach found, no records exist with this id. So while not empty (NULL) keep asking for id.
    // free memory
    free(tmpData);
    free(result);

    return choice;
}

/* Name */
void enterString(char ** str){
    char tmpstr[30];
    scanf("%s", tmpstr);
    *str = (char*)malloc(sizeof(char)*strlen(tmpstr));
    memcpy(*str, tmpstr, strlen(tmpstr) +1);
}

/* Email */
void setEmail(struct data** data){
    char tmpstr[30];
    char * str;

    do{
        puts("\tEmail: ");
        scanf("%s", tmpstr);
    }while( !Data.setEmail(*data, tmpstr) );
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
    puts("\tName: ");
    enterString(&data->name);
    puts("\tSurname: ");
    enterString(&data->surname);
    puts("\tYear born: ");
    scanf("%d", &data->yearBorn);
    setEmail(&data);
    data->country = getCountry();
    data->travelClass = getTravelClass();
    data->travelFrequency = getTravelFrequency();
    data->stayDuration = getStayDuration();

    DataBase.addRecord(db, data);
    // DataBase.showAll(db);
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

void changeDetails(struct data**  data){
    int subchoice;

    do{
        puts("\nChange: ");
        puts("\t[1] - Surname.");
        puts("\t[2] - Email.");
        puts("\t[3] - Country.");
        puts("\t[4] - Travel Class.");
        puts("\t[4] - Travel Frequency.");
        puts("\t[4] - Stay Duration.");
        puts("---------------------------------------");
        puts("\t[0] - Back.\n");
        scanf("%d", &subchoice);
        switch (subchoice) {
            case 1:
                puts("\tSurname: ");
                enterString(&((*data)->surname));
                break;
            case 2:
                setEmail(data);
                break;
            case 3: (*data)->country = getCountry(); break;
            case 4: (*data)->travelClass = getTravelClass(); break;
            case 5: (*data)->travelFrequency = getTravelFrequency(); break;
            case 6: (*data)->stayDuration = getStayDuration(); break;
        }
    }while( subchoice );
}

void menu_updateRecord(struct db* db){
    int choice;
    struct data * tmpData = Data.empty();
    struct list* result;
    do{
        puts("=======================================");
        puts("=     Update Record                   =");
        puts("=======================================");
        puts("\nEnter ID ([0] - to exit):");
        scanf("%d", &choice);
        tmpData->id = choice;
        result = DataBase.search(db, tmpData, Data.equals, Data.compareId);

        if( List.isEmpty(result) ){
            puts("No match found! List is empty.");
        }
        else if( List.size(result) > 1 ){       // probably I should create log and brake program here.
            puts("ERROR! found more then one! Dublicate ID");
        }
        else{
            struct data *data = List.getFirst(result);
            changeDetails(&data);
        }

    }while( choice );

    // free memory
    free(tmpData);
    if( result ){ free(result); }
}

void menu_deleteRecord(struct db* db){
    int id;
    do{
        puts("=======================================");
        puts("=     Delete Record                   =");
        puts("=======================================");
        puts("\nEnter ID ([0] - to exit):");
        scanf("%d", &id);

        printf("Record (id:%d)... ", id);
        if( DataBase.removeRecord(db, id) ){ puts("deleted!"); }
        else{ puts("NOT deleted!"); }

    }while( id );
}

struct list * choiceOne(struct db *db){
    int choice;
    struct list *list = List.empty();
    struct data *tmpData = Data.empty();
    // char classStr[20];

    do{
        puts("[1] - Travel Class");
        puts("[2] - Born Before 1980\n");
        puts("Enter choice:");
        scanf("%d", &choice);

        switch( choice ){
            case 1:
                // strcmp(classStr, "travel ");
                tmpData->travelClass = getTravelClass();
                list = DataBase.search(db, tmpData, Data.equals, Data.compareTravelClass);
                // strcat(classStr, travelClass_toStr[tmpData->travelClass]);
                // printf("Trvel %s and ", travelClass_toStr[tmpData->travelClass]);
                break;
            case 2:
                tmpData->yearBorn = 1980;
                list = DataBase.search(db, tmpData, Data.less, Data.compareBornDate);
                // printf("Born before %d and ", tmpData->yearBorn);
                break;
            default:
                puts("Wrong choice! Try again.");
        }
    }while( choice < 1 || 2 < choice );

    free(tmpData);
    // List.showAll(list);
    return list;
}

int choiceTwo(){
    puts("[1] - % of passengers who travel from the UK");
    puts("[2] - % of passengers who travel from the Rest of Europe");
    puts("[3] - % of passengers who travel from the Asia");
    puts("[4] - % of passengers who travel from the Americas");
    puts("[5] - % of passengers who travel from the Australasia");
    puts("[6] - % of passengers who spent on average one day in Ireland");
    puts("[7] - % of passengers who spent on average less than 3 days in Ireland");
    puts("[8] - % of passengers who spent on average less than 7 days in Ireland");
    puts("[9] - % of passengers who spent on average more than 7 days in Ireland");
    int subchoice;
    do{
        puts("Enter choice:");
        scanf("%d", &subchoice);
    }while( subchoice < 1 || 9 < subchoice );

    return subchoice;
}

char * stats(struct list* list){
    int stats = 9;
    float * statArr = (float*)malloc(stats * sizeof(float));
    char *R = (char *)malloc(200 * sizeof(char));
    // initialize to 0 (zero)
    for(int i  = 0; i < stats; i++){
        statArr[i] = 0;
    }
    // papulate "statArr"
    struct data *currData;
    for(currData = List.getFirst(list); currData != NULL; currData = List.getNext(list)){
        Countries country = currData->country;
        StayDuration stay = currData->stayDuration;

        switch(country){
            case UK:        statArr[country -1]++;  break;
            case EUROPE:    statArr[country -1]++;  break;
            case ASIA:      statArr[country -1]++;  break;
            case AMERICAS:  statArr[country -1]++;  break;
            case AUSTRALIA: statArr[country -1]++;  break;
        }

        switch(stay){
            case ONE_DAY:       statArr[stay +4]++; break;
            case LESS_3_DAYS:   statArr[stay +4]++; break;
            case LESS_7_DAYS:   statArr[stay +4]++; break;
            case MORE_7_DAYS:   statArr[stay +4]++; break;
        }
    }
    // convert to % (percentage)
    float percent;
    char s[10];
    strcpy(R, "");
    for(int i = 0; i < stats; i++){
        percent = statArr[i] / List.size(list) *100.0f;
        sprintf(s, "%7.2f", percent);
        strcat(R, s);
    }


    return R;
}

// void showStats(float* arr){
//     for(int i = 0; i < 9; i++){
//         printf("%10.2f", arr[i]);
//     }
//     puts("");
// }

void menu_statistics(struct db* db){
    // float matches = 0.0f, size = List.size(db->list);
    struct list *tmpListOne;
     // *tmpListTwo = List.empty();
    // struct data *tmpData = Data.empty();

    puts("=======================================");
    puts("=     Statistics                      =");
    puts("=======================================");

    tmpListOne = choiceOne(db);

    // showStats( stats(tmpListOne) );
    puts(stats(tmpListOne));

    // int subchoice = choiceTwo();
    // Countries country = subchoice;
    // StayDuration stay = subchoice -5;
    //
    // switch( subchoice ){
    //     case 1:
    //     case 2:
    //     case 3:
    //     case 4:
    //     case 5:
    //         tmpData->country = country;
    //         tmpListTwo = List.search(tmpListOne, tmpData, Data.equals, Data.compareCountry);
    //         if( !List.isEmpty(tmpListTwo) ){ matches = List.size(tmpListTwo) * 100 / size; }
    //         printf("%.1f percent of passengers travel from %s.\n", matches, country_toStr[country]);
    //         break;
    //     case 6:
    //     case 7:
    //     case 8:
    //     case 9:
    //         tmpData->stayDuration = stay;
    //         tmpListTwo = List.search(tmpListOne, tmpData, Data.equals, Data.compareStayDuration);
    //         if( !List.isEmpty(tmpListTwo) ){ matches = List.size(tmpListTwo) * 100 / size; }
    //         printf("%.1f percent of passengers stayed %s.\n", matches, stayDuration_toStr[stay]);
    //         break;
    //     default:
    //         puts("Wrong choice! Try again.");
    // }

    // List.showAll(tmpListTwo);

    free(tmpListOne);
    // free(tmpListTwo);
    // free(tmpData);
}

void menu_report(struct db* db){
    struct list *tmpListOne, *tmpListTwo = List.empty();
    struct data *tmpData = Data.empty();

    puts("=======================================");
    puts("=     Report                          =");
    puts("=======================================");

    tmpListOne = choiceOne(db);

    int subchoice = choiceTwo();
    Countries country = subchoice;
    StayDuration stay = subchoice -5;

    switch( subchoice ){
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
            tmpData->country = country;
            tmpListTwo = List.search(tmpListOne, tmpData, Data.equals, Data.compareCountry);
            if( !List.isEmpty(tmpListTwo) ){ List.showAll(tmpListTwo); }
            break;
        case 6:
        case 7:
        case 8:
        case 9:
            tmpData->stayDuration = stay;
            tmpListTwo = List.search(tmpListOne, tmpData, Data.equals, Data.compareStayDuration);
            if( !List.isEmpty(tmpListTwo) ){ List.showAll(tmpListTwo); }
            break;
        default:
            puts("Wrong choice! Try again.");
    }

    // List.showAll(tmpListTwo);

    // create empty data
    if( List.isEmpty(tmpListTwo) ){
         tmpData->id = 0;
         tmpData->name = "";
         tmpData->surname = "";
         tmpData->yearBorn = 0;
         tmpData->email = "";
         tmpData->country = 0;
         tmpData->travelClass = 0;
         tmpData->travelFrequency = 0;
         tmpData->stayDuration = 0;
         List.addFront(tmpListTwo, tmpData);
    }

    char reportFile[50];
    List.saveToFile(tmpListTwo, currentTime(), Data.toString);

    free(tmpListOne);
    free(tmpListTwo);
    free(tmpData);
}

void menu_listOrdered(struct db* db){
    int choice;
    struct data *tmpData = Data.empty();
    tmpData->country = UK;
    struct list *tmpList = List.search(db->list, tmpData, Data.equals, Data.compareCountry);
    free(tmpData);

    puts("=======================================");
    puts("=     Sort Records                    =");
    puts("=======================================");
    puts("Sort by:");
    puts("\t[1] - id");
    puts("\t[2] - name");
    puts("\t[3] - surname");
    puts("\t[4] - yearBorn");
    puts("\t[5] - email");
    puts("\t[6] - country");
    puts("\t[7] - travelClass");
    puts("\t[8] - travelFrequency");
    puts("\t[9] - stayDuration");
    puts("---------------------------------------");
    puts("[0] - Back.\n");

    do{
        puts("Enter choice:");
        scanf("%d", &choice);

        switch( choice ){
            case 1: List.sort(tmpList, Data.compareId);            puts("...done"); break;
            case 2: List.sort(tmpList, Data.compareName);          puts("...done"); break;
            case 3: List.sort(tmpList, Data.compareSurname);       puts("...done"); break;
            case 4: List.sort(tmpList, Data.compareBornDate);      puts("...done"); break;
            case 5: List.sort(tmpList, Data.compareEmail);         puts("...done"); break;
            case 6: List.sort(tmpList, Data.compareCountry);       puts("...done"); break;
            case 7: List.sort(tmpList, Data.compareTravelClass);   puts("...done"); break;
            case 8: List.sort(tmpList, Data.compareTravelFrequency); puts("...done"); break;
            case 9: List.sort(tmpList, Data.compareStayDuration);  puts("...done"); break;
            default:
                puts("Wrong choice! Try again.");
        }
        if( !List.isEmpty(tmpList) ){ List.showAll(tmpList); }
    }while( choice );

    if( !List.isEmpty(tmpList) ){ free(tmpList); }
}
