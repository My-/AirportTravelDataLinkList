#include "data.h"



bool isEmailValid( char *email ){
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
    .compareBornDate = data_compareBornDate,
    .compareId = data_compareId,
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

void data_setTravelData( struct data *this, Countries country, TravelClass travelClass,
                        TravelFrequency travelFrequency, StayDuration stayDuration ){
    this->country = country;
    this->travelClass = travelClass;
    this->travelFrequency = travelFrequency;
    this->stayDuration = stayDuration;
    // printf("TravelData{ country: %s, travelClass: %d}\n", country_toStr[ this->country], this->travelClass);
}

bool data_setId( struct data *this, int id ){
    this->id = id;
}

bool data_setEmail( struct data *this, char* email ){
    if( isEmailValid(email) ){
        this->email = email;
        return true;
    }
    return false;
}


bool data_remove( struct data *this){
    // free(this->name);
    // if( !this->name ){ printf("Deleted.\n"); }
    // else{ printf("Not Deleted: %s\n", this->name); }
    //
    // free(this);
    // if( !this ){ printf("Deleted.\n"); }
    // else{ printf("Not Deleted: %s\n", this->name); }

}



// https://www.tutorialspoint.com/cprogramming/c_strings.htm
// https://stackoverflow.com/a/32819876/5322506
char* data_toString(struct data *this){
    // ID toString
    int len = snprintf( NULL, 0, "%d", this->id );
    char* id_str = malloc( len +1 );
    snprintf( id_str, len + 1, "%d", this->id );

    // Year born toString
    len = snprintf( NULL, 0, "%d", this->yearBorn );
    char* year_Str = malloc( len + 1 );
    snprintf( year_Str, len + 1, "%d", this->yearBorn );

    // Create Data string
    char* str = malloc( 1 );
    strcat(str, "{");
    strcat(str, "\n\tId: ");
    strcat(str, id_str);
    free(id_str);   // free memory from temporary variable
    strcat(str, "\n\tName: ");
    strcat(str, this->name);
    strcat(str, "\n\tSurname: ");
    strcat(str, this->surname);
    strcat(str, "\n\tYear born: ");
    strcat(str, year_Str);
    free(year_Str);   // free memory from temporary variable
    strcat(str, "\n\tEmail: ");
    strcat(str, this->email);
    strcat(str, "\n\tCountry: ");
    strcat(str, country_toStr[this->country]);
    strcat(str, "\n\tTravel class: ");
    strcat(str, travelClass_toStr[this->travelClass]);
    strcat(str, "\n\tTravel freaquaency: ");
    strcat(str, travelFrequency_toStr[this->travelFrequency]);
    strcat(str, "\n\tStay duration: ");
    strcat(str, stayDuration_toStr[this->stayDuration]);
    strcat(str, "\n}\n");

    return str;
}

int data_compareBornDate(struct data *d1, struct data *d2){
    return d1->yearBorn -d2->yearBorn;
}

int data_compareId(struct data *d1, struct data *d2){
    return d1->id -d2->id;
}
