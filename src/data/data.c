#include "data.h"



bool isEmailValid( const char *email ){
    char * tail = strchr(email, '@');
    if( !tail ){ return false; }
    int tailLen = strlen(tail);
    int userLen = strlen(email) -tailLen;
    if( userLen < 1 ){ return false; }
    if( tailLen < 4 ){ return false; } // min: "@a.a"

    char * country = strchr(tail, '.');
    if( !country ){ return false; }
    int countryLen = strlen(country);
    int provLen = tailLen -countryLen;
    if( countryLen < 2 ){ return false; }
    if( provLen < 2 ){ return false; }

    return true;
}

/**
*   It's like Data class.
*   For more info and refrences check data.h.
*/
struct data_type Data = {
    .empty = data_empty,
    .of = data_of,
    .setTravelData = data_setTravelData,
    .remove = data_remove,
    .setId = data_setId,
    .setEmail = data_setEmail,
    .toString = data_toString,
    .toInfo = data_toInfo,
    .toJSON = data_toJSON,
    .toCSON = data_toCSON,
    .toData = data_toData,

    .less = data_less,
    .equals = data_equals,
    .more = data_more,

    .compareId = data_compareId,
    .compareName = data_compareName,
    .compareSurname = data_compareSurname,
    .compareBornDate = data_compareBornDate,
    .compareEmail = data_compareEmail,
    .compareId = data_compareId,
    .compareBornDate = data_compareBornDate,
    .compareCountry = data_compareCountry,
    .compareTravelClass = data_compareTravelClass,
    .compareTravelFrequency = data_compareTravelFrequency,
    .compareStayDuration = data_compareStayDuration,
    .counter = 0
};

// empty data constructor
struct data * data_empty(){
    // printf("Creating data... ");
    struct data * this = (struct data*)malloc(sizeof(struct data));
    this->id = 0;
    this->name = "";
    this->surname = "";
    this->yearBorn = 0;
    this->email = "";
    Data.counter++;
    // printf("data{ id: %d, name: %s, email: %s}\n", this->id, this->name, this->email);

    return this;
}

// data constructor
struct data * data_of(int id, char *name, char *surname, int yearBorn, char *email){
    // printf("Creating data... ");
    struct data * this = (struct data*)malloc(sizeof(struct data));
    this->id = id;
    this->name = name;
    this->surname = surname;
    this->yearBorn = yearBorn;
    this->email = email;
    Data.counter++;
    // printf("data{ id: %d, name: %s, email: %s}\n", this->id, this->name, this->email);

    return this;
}

void data_setTravelData( struct data *this, int country, int travelClass, int travelFrequency, int stayDuration ){
    this->country = country;
    this->travelClass = travelClass;
    this->travelFrequency = travelFrequency;
    this->stayDuration = stayDuration;
    // printf("TravelData{ country: %s, travelClass: %d}\n", country_toStr[ this->country], this->travelClass);
}

bool data_setId( struct data *this, int id ){
    this->id = id; // TODO: validation
}

bool data_setEmail( struct data *this, const char* email ){
    if( isEmailValid(email) ){
        this->email = (char*)malloc(sizeof(char)*strlen(email));
        memcpy(this->email, email, strlen(email) +1);
        return true;
    }
    return false;
}

// https://stackoverflow.com/questions/1025589/setting-variable-to-null-after-free
bool data_remove( struct data **this){
    // and its why people hate C...
    free(*this);
    *this = NULL;
}

// http://joequery.me/code/snprintf-c/
// https://stackoverflow.com/questions/804288/creating-c-formatted-strings-not-printing-them
char* data_toString(struct data *this){
    char *s = (char*)malloc(500 *sizeof(char));

    sprintf(s, "\n\tid: %d\n\tname: %s\n\tsurname: %s\n\tyearBorn: %d\n\temail: %s\n\tcountry: %s\n\ttravelClass: %s\n\ttravelFrequency: %s\n\tstayDuration: %s\n", this->id, this->name, this->surname, this->yearBorn, this->email, country_toStr[this->country], travelClass_toStr[this->travelClass], travelFrequency_toStr[this->travelFrequency], stayDuration_toStr[this->stayDuration]);
    return s;
}

char* data_toJSON(struct data *this){
    char *s = (char*)malloc(200 *sizeof(char));

    sprintf(s, "{\n\t\"id\" : %d\n\t\"name\" : \"%s\"\n\t\"surname\" : \"%s\"\n\t\"yearBorn\" : %d\n\t\"email\" : \"%s\"\n\t\"country\" : %d\n\t\"travelClass\" : %d\n\t\"travelFrequency\" : %d\n\t\"stayDuration\" : %d\n}\n", this->id, this->name, this->surname, this->yearBorn, this->email, this->country, this->travelClass, this->travelFrequency, this->stayDuration);
    return s;
}

char* data_toCSON(struct data *this){
    char *s = (char*)malloc(200 *sizeof(char));

    sprintf(s, "\n\tid: %d\n\tname: '%s'\n\tsurname: '%s'\n\tyearBorn: %d\n\temail: '%s'\n\tcountry: %d\n\ttravelClass: %d\n\ttravelFrequency: %d\n\tstayDuration: %d\n", this->id, this->name, this->surname, this->yearBorn, this->email, this->country, this->travelClass, this->travelFrequency, this->stayDuration);
    return s;
}

char* data_toData(struct data *this){
    char *s = (char*)malloc(200 *sizeof(char));

    sprintf(s, "%d %s %s %d %s %d %d %d %d\n", this->id, this->name, this->surname, this->yearBorn, this->email, this->country, this->travelClass, this->travelFrequency, this->stayDuration);
    return s;
}


// https://www.tutorialspoint.com/cprogramming/c_strings.htm
// https://stackoverflow.com/a/32819876/5322506
char* data_toInfo(struct data *this){
    // printf("%d %d\n", this->id, this->yearBorn);
    // ID toString
    int len = snprintf( NULL, 0, "%d", this->id );
    char* id_str = malloc( len +1 );
    snprintf( id_str, len + 1, "%d", this->id );

    // Year born toString
    len = snprintf( NULL, 0, "%d", this->yearBorn );
    char* year_Str = malloc( len + 1 );
    snprintf( year_Str, len + 1, "%d", this->yearBorn );

    // printf("%s %s : %d %d\n", id_str, year_Str, this->id, this->yearBorn);

    // Create Data string
    char* str = malloc( 1 );
    strcat(str, "{");
    strcat(str, "\n\tId: ");
    strcat(str, id_str);
    strcat(str, "\n\tName: ");
    strcat(str, this->name);
    strcat(str, "\n\tSurname: ");
    strcat(str, this->surname);
    strcat(str, "\n\tYear born: ");
    strcat(str, year_Str);
    strcat(str, "\n\tEmail: ");
    strcat(str, this->email);
    strcat(str, "\n\tCountry: ");
    strcat(str, (this->country < SIZE_COUNTIES ? country_toStr[this->country] : country_toStr[0]));
    strcat(str, "\n\tTravel class: ");
    strcat(str, (this->travelClass < SIZE_TRAVEL_CLASS ? travelClass_toStr[this->travelClass] : travelClass_toStr[0]));
    strcat(str, "\n\tTravel freaquaency: ");
    strcat(str, (this->travelFrequency < SIZE_TRAVEL_FREQUENCY ? travelFrequency_toStr[this->travelFrequency] : travelFrequency_toStr[0]));
    strcat(str, "\n\tStay duration: ");
    strcat(str, (this->stayDuration < SIZE_STAY_DURATION ? stayDuration_toStr[this->stayDuration] : stayDuration_toStr[0]));
    strcat(str, "\n}\n");

    // printf("%s %s : %d %d\n", id_str, year_Str, this->id, this->yearBorn);

    free(id_str);   // free memory from temporary variable
    free(year_Str);   // free memory from temporary variable
    return str;
}

/* Logical Operators */
bool data_less(struct data *d1, struct data *d2, DATA_COMPARATOR){
    return compareData(d1, d2) < 0;
}
bool data_equals(struct data *d1, struct data *d2, DATA_COMPARATOR){
    return compareData(d1, d2) == 0;
}
bool data_more(struct data *d1, struct data *d2, DATA_COMPARATOR){
    return compareData(d1, d2) > 0;
}

/* Comparators */
int data_compareId(struct data *d1, struct data *d2){
    return d1->id -d2->id;
}
int data_compareName( struct data *n1, struct data *n2 ){
    return strcmp(n1->name, n2->name);
}
int data_compareSurname( struct data *n1, struct data *n2 ){
    return strcmp(n1->surname, n2->surname);
}
int data_compareBornDate(struct data *d1, struct data *d2){
    return d1->yearBorn -d2->yearBorn;
}
int data_compareEmail( struct data *n1, struct data *n2 ){
    return strcmp(n1->email, n2->email);
}
int data_compareCountry( struct data *d1, struct data *d2 ){
    return d1->country -d2->country;
}
int data_compareTravelClass( struct data *d1, struct data *d2 ){
    return d1->travelClass -d2->travelClass;
}
int data_compareTravelFrequency( struct data *d1, struct data *d2 ){
    return d1->travelFrequency -d2->travelFrequency;
}
int data_compareStayDuration( struct data *d1, struct data *d2 ){
    return d1->stayDuration -d2->stayDuration;
}
