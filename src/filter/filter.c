

#include "filter.h"
// #include "../data/data.c" // need it to suport Data "class"



// Filter "class"
struct filter Filter = {
    .travelFrom = filter_travelFrom,
    .travelClass = filter_travelClass,
    .travelFrequency = filter_travelFrequency,
    .stayDuration = filter_stayDuration
};

// Country filters.
bool filterUK(struct data *data){ return data->country == UK; }
bool filterEUROPE(struct data *data){ return data->country == EUROPE; }
bool filterASIA(struct data *data){ return data->country == ASIA; }
bool filterAMERICAS(struct data *data){ return data->country == AMERICAS; }
bool filterAUSTRALIA(struct data *data){ return data->country == AUSTRALIA; }
bool filterFalse(struct data *data){ return false; }

// Country filter factory.
bool (*filter_travelFrom(int country))(struct data*){
    bool (*filter)(struct data *data);
    switch (country) {
        case UK: filter = filterUK; break;
        case EUROPE: filter = filterEUROPE; break;
        case ASIA: filter = filterASIA; break;
        case AMERICAS: filter = filterAMERICAS; break;
        case AUSTRALIA: filter = filterAUSTRALIA; break;
        default: filter = filterFalse;  // if not from list return false
    }
    return filter;
}


// Travel class filters
bool filterECONOMY(struct data *data){ return data->travelClass == ECONOMY; }
bool filterPREMIUM(struct data *data){ return data->travelClass == PREMIUM; }
bool filterBUSINESS(struct data *data){ return data->travelClass == BUSINESS; }
bool filterFIRST(struct data *data){ return data->travelClass == FIRST; }

// Travel class filter factory
bool (*filter_travelClass(int tclass))(struct data*){
    bool (*filter)(struct data *data);
    switch (tclass) {
        case ECONOMY: filter = filterECONOMY; break;
        case PREMIUM: filter = filterPREMIUM; break;
        case BUSINESS: filter = filterBUSINESS; break;
        case FIRST: filter = filterFIRST; break;
        default: filter = filterFalse;  // if not from list return false
    }
    return filter;
}


// Travel frequency filters
bool filterLESS_3_TIMES(struct data *data){ return data->travelFrequency == LESS_3_TIMES; }
bool filterLESS_5_TIMES(struct data *data){ return data->travelFrequency == LESS_5_TIMES; }
bool filterMORE_5_TIMES(struct data *data){ return data->travelFrequency == MORE_5_TIMES; }

// Travel frequency filter factory
bool (*filter_travelFrequency(int frequancy))(struct data*){
    bool (*filter)(struct data *data);
    switch (frequancy){
        case LESS_3_TIMES: filter = filterLESS_3_TIMES; break;
        case LESS_5_TIMES: filter = filterLESS_5_TIMES; break;
        case MORE_5_TIMES: filter = filterMORE_5_TIMES; break;
        default: filter = filterFalse;  // if not from list return false
    }
    return filter;
}


// Stay duration filters
bool filterONE_DAY(struct data *data){ return data->stayDuration == ONE_DAY; }
bool filterLESS_3_DAYS(struct data *data){ return data->stayDuration == LESS_3_DAYS; }
bool filterLESS_7_DAYS(struct data *data){ return data->stayDuration == LESS_7_DAYS; }
bool filterMORE_7_DAYS(struct data *data){ return data->stayDuration == MORE_7_DAYS; }

// Stay duration filter factory
bool (*filter_stayDuration(int duration))(struct data*){
    bool (*filter)(struct data *data);
    switch (duration){
        case ONE_DAY: filter = filterONE_DAY; break;
        case LESS_3_DAYS: filter = filterLESS_3_DAYS; break;
        case LESS_7_DAYS: filter = filterLESS_7_DAYS; break;
        case MORE_7_DAYS: filter = filterMORE_7_DAYS; break;
        default: filter = filterFalse;  // if not from list return false
    }
    return filter;
}

/**
*   Function takes ( data, FilterFunction, filtering parameter )
*   returns true if match;
*/
bool takeFilter( struct data * data, bool(*filter(int ))(struct data*), int value ){
    return filter(value)(data);
}
