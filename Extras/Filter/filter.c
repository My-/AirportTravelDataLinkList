

#include "filter.h"


struct filter Filter = {
    .travelFrom = filter_travelFrom,
    // .travelClass = filter_travelClass,
    // .travelFrequency = filter_travelFrequency,
    // .stayDuration = filter_stayDuration
};

bool filterUK(struct data *data){
    return data->country == UK;
}

bool (*filter_travelFrom(Countries country))(struct data*){
    bool (*filter)(struct data *data);
    switch (country) {
        case UK: filter = filterUK; break;
        // case EUROPE: filter = ; break;
        // case ASIA: filter = ; break;
        // case AMERICAS: filter = ; break;
        // case AUSTRALIA: filter = ; break;
    }
    return filter;
}
