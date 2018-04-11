

#ifndef FILTER
#define FILTER bool (*filter(int))(struct data*)

#include "../data/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string


// prototype returns function
bool filter_on( struct data *data, int machValue, FILTER );
bool (*filter_travelFrom(int country))(struct data*);
bool (*filter_travelClass(int tclass))(struct data*);
bool (*filter_travelFrequency(int frequancy))(struct data*);
bool (*filter_stayDuration(int duration))(struct data*);
bool (*filter_id(int id))(struct data*);


extern struct filter {
    bool (*on)( struct data *data, int value, FILTER );
    bool (*((*travelFrom)(int country)))(struct data*);
    bool (*((*travelClass)(int tclass)))(struct data*);
    bool (*((*travelFrequency)(int frequancy)))(struct data*);
    bool (*((*stayDuration)(int duration)))(struct data*);
    bool (*((*id)(int id)))(struct data*);

} Filter;

#endif
