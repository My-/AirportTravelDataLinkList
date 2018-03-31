

#ifndef FILTER
#define FILTER

#include "../Data/data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
// #include <string.h>     // string


bool (*filter_travelFrom(Countries country))(struct data*);
// bool filter_travelClass(TravelClass tclass)(struct data*);
// bool filter_travelFrequency(TravelFrequency frequancy)(struct data*);
// bool filter_stayDuration(StayDuration duration)(struct data*);

struct filter {
    bool (*travelFrom(Countries country))(struct data*);
    // bool (*travelClass(TravelClass tclass))(struct data*);
    // bool (*travelFrequency(TravelFrequency frequancy))(struct data*);
    // bool (*stayDuration(StayDuration duration))(struct data*);
} Filter;

#endif
