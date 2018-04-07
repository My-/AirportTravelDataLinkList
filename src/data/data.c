#include "data.h"

/**
*   It's like enum .toString() method.
*       https://stackoverflow.com/a/2161797/5322506
*/
static char *country_toStr[] = { "United Kingdom", "Rest Europe", "Asia", "Americas", "Australia" };
static char *travelClass_toStr[] = { "Economy class", "Premium class", "Business class", "First class" };
static char *travelFrequency_toStr[] = { "less then 3 times", "less then 5 times", "more than 5 times" };
static char *stayDuration_toStr[] = { "1 day", "3 and less days", "7 and less days", "more than 7 days" };

/**
*   It's like Data class.
*   For more info and refrences check data.h.
*/
struct data_type Data = {
    .of = data_of,
    .setTravelData = data_setTravelData,
    .delete = data_delete,
    .getEmail = data_getEmail,
    .setId = data_setId,
    .toString = data_toString,
    .compareBornDate = data_compareBornDate,
    .compareId = data_compareId,
    .counter = 0
};

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

void data_setTravelData(struct data *this, Countries country, TravelClass travelClass,
                        TravelFrequency travelFrequency, StayDuration stayDuration){
    this->country = country;
    this->travelClass = travelClass;
    this->travelFrequency = travelFrequency;
    this->stayDuration = stayDuration;
    // printf("TravelData{ country: %s, travelClass: %d}\n", country_toStr[ this->country], this->travelClass);
}

char* data_getEmail( struct data *this){
    printf("email is %s\n", this->email);
    return this->email;
}

void data_setId( struct data *this, int id){
    this->id = id;
    printf("id set to: %d\n", this->id);
}

bool data_delete( struct data *this){
    // free(this->name);
    if( !this->name ){ printf("Deleted.\n"); }
    else{ printf("Not Deleted: %s\n", this->name); }

    free(this);
    if( !this ){ printf("Deleted.\n"); }
    else{ printf("Not Deleted: %s\n", this->name); }

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
