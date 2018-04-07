

#ifndef FILTER
#define FILTER bool (*on)( struct data *data, bool(*filter(int ))(struct data*), int value )

#include "../data/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string


// prototype returns function
bool filter_on( struct data *data, bool(*filter(int ))(struct data*), int value );
bool (*filter_travelFrom(int country))(struct data*);
bool (*filter_travelClass(int tclass))(struct data*);
bool (*filter_travelFrequency(int frequancy))(struct data*);
bool (*filter_stayDuration(int duration))(struct data*);


extern struct filter {
    FILTER;
    bool (*((*travelFrom)(int country)))(struct data*);
    bool (*((*travelClass)(int tclass)))(struct data*);
    bool (*((*travelFrequency)(int frequancy)))(struct data*);
    bool (*((*stayDuration)(int duration)))(struct data*);
} Filter;

#endif
