/**
*   All this "class" implementation is based on:
*       https://stackoverflow.com/a/2733004/5322506
*       https://stackoverflow.com/a/17622474/5322506
*       And many head banging while implementing
*
*   @by Mindaugas Sarskus
*   @date 30/03/2018
*/

#ifndef DATA
#define DATA

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
#include <string.h>     // string

#define DATA_COMPARATOR int(*compareData)(struct data*, struct data*)

// https://stackoverflow.com/a/2181941/5322506
typedef enum{ NO_COUNTRY, UK, EUROPE, ASIA, AMERICAS, AUSTRALIA, SIZE_COUNTIES }Countries;
typedef enum{ NO_TRAVEL_CLASS, ECONOMY, PREMIUM, BUSINESS, FIRST, SIZE_TRAVEL_CLASS }TravelClass;
typedef enum{ NO_TRAVEL_FREQUENCY, LESS_3_TIMES, LESS_5_TIMES, MORE_5_TIMES, SIZE_TRAVEL_FREQUENCY }TravelFrequency;
typedef enum{ NO_STAY_DURATION, ONE_DAY, LESS_3_DAYS, LESS_7_DAYS, MORE_7_DAYS, SIZE_STAY_DURATION }StayDuration;

// "class" instance fields
struct data {
    struct data_type * _it;  // because it's a pointer, it will be shared between all structs
    // "class" fields
    int id;
    char* name;
    char* surname;
    int yearBorn;
    char* email;
    Countries country;
    TravelClass travelClass;
    TravelFrequency travelFrequency;
    StayDuration stayDuration;
};

/*** function prototypes (method signatures) ***/
bool data_delete( struct data *this);
void data_setId( struct data *this, int id);
char* data_getEmail( struct data *this);
struct data * data_of(int id, char *name, char *surname, int yearBorn, char *email);
void data_setTravelData(struct data *this, Countries country, TravelClass travelClass,
                        TravelFrequency travelFrequency, StayDuration stayDuration);
char* data_toString(struct data *this);

int data_compareBornDate(struct data *n1, struct data *n2);
int data_compareId(struct data* n1, struct data* n2);

/*** "Class" static fields (methods, class variables) ***/
extern struct data_type {
    struct data * (*of)(int id, char *name, char *surname, int yearBorn, char *email);
    void (*setTravelData)(struct data *this, Countries country, TravelClass travelClass,
                        TravelFrequency travelFrequency, StayDuration stayDuration);
    bool (*delete)( struct data *this );
    char * (*getEmail)( struct data *this );
    void (*setId)( struct data *this, int id );
    char * (*toString)( struct data *this );
    int (*compareBornDate)(struct data *n1, struct data *n2);
    int (*compareId)(struct data* n1, struct data* n2);
    int counter;
} Data; // <-- it's like a "class" name

#endif
