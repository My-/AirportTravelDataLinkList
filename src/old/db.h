#ifndef  DB
#define DB

// https://stackoverflow.com/a/2181941/5322506
typedef enum{ UK, EUROPE, ASIA, AMERICAS, AUSTRALIA, SIZE_COUNTIES }Countries;
typedef enum{ ECONOMY, PREMIUM, BUSINESS, FIRST, SIZE_TRAVEL_CLASS }TravelClass;
typedef enum{ LESS_3_TIMES, LESS_5_TIMES, MORE_5_TIMES, SIZE_TRAVEL_FREQUENCY }TravelFrequency;
typedef enum{ ONE_DAY, LESS_3_DAYS, LESS_7_DAYS, MORE_7_DAYS, SIZE_STAY_DURATION }StayDuration;



typedef char* (*Getter)(struct data*);

char* getCountryImpl();

typedef struct data{
   int id;
   char* name;
   char* surname;
   int yearBorn;
   char* email;
   Countries country;
   TravelClass travelClass;
   TripFrequency travelFrequency;
   StayDuration stayDuration;
   struct data* this;
   // https://stackoverflow.com/a/19039085/5322506
   // https://stackoverflow.com/a/17622474/5322506
   // https://stackoverflow.com/a/11481498/5322506
   // https://stackoverflow.com/a/2733004/5322506
   Getter getCountry;
   // Getter getTravelClass;
   // Getter getTravelFrequancy;
   // Getter getStayDuration;
}Data;




typedef struct node {
    Data* data;
    struct node* NEXT;
    struct node* PREV;
}Node;


void showPassenger(Data* passenger);
Data* createPassenger();

#endif
