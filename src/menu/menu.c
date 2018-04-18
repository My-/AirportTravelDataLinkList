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

void appendToFile(char* fileName, char *str){
    FILE* pFile;
    pFile = fopen(fileName, "a");       // open file

    if( !pFile ){ puts("The file could not be opened"); }
    else{
        fprintf( pFile,"%s", str ); // append to file
        fclose(pFile);      // close file
    }
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
    free(tmpData);  tmpData = NULL;
    free(result);   result = NULL;

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
    free(tmpData);  tmpData = NULL;
    if( result ){ free(result); result = NULL; }
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
    free(tmpData);  tmpData = NULL;
    if( result ){ free(result); result = NULL; }
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

char * stats(struct list* list, char * lable){
    int stats = 9;
    float * statArr = (float*)malloc(stats * sizeof(float));
    char *R = (char *)malloc(500 * sizeof(char));

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
    // convert to % (percentage) and create string
    float percent;
    char s[10];
    strcpy(R, lable);
    for(int i = 0; i < stats; i++){
        percent = statArr[i] / List.size(list) *100.0f;
        sprintf(s, "%-8.2f", percent);
        strcat(R, s);
    }
    strcat(R, "\n");
    // puts(R);
    return R;
}

int choiceStats(){
    int choice;
    do{
        puts("[1] - Born Before 1980");
        puts("[2] - Travel Class\n");
        puts("Enter choice:");
        scanf("%d", &choice);
    }while( choice < 1 || 2 < choice );

    if( choice == 2 ){ choice += getTravelClass(); }

    return choice -1;
}

char * getStats(struct db *db, int choice){
    struct list *list = List.empty();
    struct data *tmpData = Data.empty();
    char * R;
    char lable[30];
// printf("choise: %d\n", choice);
// List.showAll(db->list);
    switch( choice ){
        case 0:
            tmpData->yearBorn = 1980;
            list = DataBase.search(db, tmpData, Data.less, Data.compareBornDate);
            sprintf(lable, "%-20s| ", "Born before 1980");
            R = stats(list, lable);
            // puts(R);
            break;
        case UK:        // 1
        case EUROPE:    // 2
        case ASIA:      // 3
        case AMERICAS:  // 4
        case AUSTRALIA: // 5
            tmpData->travelClass = choice;
            list = DataBase.search(db, tmpData, Data.equals, Data.compareTravelClass);
            sprintf(lable, "%-20s| ", travelClass_toStr[tmpData->travelClass]);
            R = stats(list, lable);
            break;
        default:
            puts("Wrong choice! Try again.");
    }

    free(tmpData);  tmpData = NULL;
    free(list);     list = NULL;
    // puts(R);
    return R;
}

// int choiceTwo(){
//     puts("[1] - % of passengers who travel from the UK");
//     puts("[2] - % of passengers who travel from the Rest of Europe");
//     puts("[3] - % of passengers who travel from the Asia");
//     puts("[4] - % of passengers who travel from the Americas");
//     puts("[5] - % of passengers who travel from the Australasia");
//     puts("[6] - % of passengers who spent on average one day in Ireland");
//     puts("[7] - % of passengers who spent on average less than 3 days in Ireland");
//     puts("[8] - % of passengers who spent on average less than 7 days in Ireland");
//     puts("[9] - % of passengers who spent on average more than 7 days in Ireland");
//     int subchoice;
//     do{
//         puts("Enter choice:");
//         scanf("%d", &subchoice);
//     }while( subchoice < 1 || 9 < subchoice );
//
//     return subchoice;
// }



void menu_statistics(struct db* db){
    char * stats;
    int choise = choiceStats();

    puts("=======================================");
    puts("=     Statistics                      =");
    puts("=======================================\n");

    stats = getStats(db, choise);

    printf("%20s| %-8s%-8s%-8s%-8s%-8s%-8s%-8s%-8s%-8s\n", "",
            "UK", "Europe", "Asia", "USA", "OZZY",
            "Stay 1", "Stay 3", "Stay 7", "Stay 7+");
    puts("----------------------------------------------------------------------------------------------");
    puts(stats);
}

void writeStats(struct db* db, char * filename){
    char str[200];
    char * stat;
    char * line = "----------------------------------------------------------------------------------------------\n";

    /// Writing Stats
    printf("\nWriting Statistics... ");
    sprintf(str, "\n\n====== %s ======\n", "Statistics");   // banner

    puts("DB before:");
    DataBase.showAll(db);

    // DataBase.load(db, DB_FILE);

    appendToFile(filename, str);

    puts("DB after:");
    DataBase.showAll(db);

    // table columns
    sprintf(str, "%20s| %-8s%-8s%-8s%-8s%-8s%-8s%-8s%-8s%-8s\n", "",
            "UK", "Europe", "Asia", "USA", "OZZY",
            "Stay 1", "Stay 3", "Stay 7", "Stay 7+");
    appendToFile(filename, str);
    appendToFile(filename, line);

    // write All stats
    for(int i = 0; i < SIZE_TRAVEL_CLASS; i++){
        stat = getStats(db, i);
        // puts(stat);
        appendToFile(filename, stat);
        free(stat);
        stat = NULL;
    }
    puts("done!");
}

void menu_report(struct db* db){
    char * filename = currentTime();
    char * stat;
    char str[500];
    char * line = "----------------------------------------------------------------------------------------------\n";

    puts("=======================================");
    puts("=     Report                          =");
    puts("=======================================\n");

    // Writing Data
    printf("Writing data... ");

    if( List.isEmpty(db->list) ){ // if list is empty exit
        puts("\nEmpty Data Base!");
        return;
    }
    List.saveToFile(db->list, filename, Data.toString);
    puts("done!");

    writeStats(db, filename);

    // /// Writing Stats
    // printf("\nWriting Statistics... ");
    // sprintf(str, "\n\n====== %s ======\n", "Statistics");   // banner
    //
    // puts("DB before:");
    // DataBase.showAll(db);
    //
    // // DataBase.load(db, DB_FILE);
    //
    // appendToFile(filename, str);
    //
    // puts("DB after:");
    // DataBase.showAll(db);
    //
    // // table columns
    // sprintf(str, "%20s| %-8s%-8s%-8s%-8s%-8s%-8s%-8s%-8s%-8s\n", "",
    //         "UK", "Europe", "Asia", "USA", "OZZY",
    //         "Stay 1", "Stay 3", "Stay 7", "Stay 7+");
    // appendToFile(filename, str);
    // appendToFile(filename, line);
    //
    // // write All stats
    // for(int i = 0; i < SIZE_TRAVEL_CLASS; i++){
    //     stat = getStats(db, i);
    //     // puts(stat);
    //     appendToFile(filename, stat);
    //     free(stat);
    //     stat = NULL;
    // }
    // puts("done!");
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
