#include "filter.h"
#include "../Data/data.h"
#include "../../test/color.h"

bool travelFrom_test( bool show ){
    bool R = true, b;

    struct data *jhon = Data.of(50, "Jhon", "Doe", 1999, "my@email.com");
    Data.setTravelData(jhon, EUROPE, FIRST, LESS_3_TIMES, ONE_DAY);

    b = Filter.travelFrom(EUROPE)(jhon);
    if( show ){ printf("Filter.travelFrom(%s)() - %s\n", "EUROPE", (b ? PASS : FAILL) ); }
    R &= b;

    b = !Filter.travelFrom(AMERICAS)(jhon);
    if( show ){ printf("!Filter.travelFrom(%s)() - %s\n", "AMERICAS", (b ? PASS : FAILL) ); }
    R &= b;

    printf("%s%s%s\n\n", YELLOW_TEXT "Filter.travelFrom()()" COLOR_RESET, " - ", (R ? PASS : FAILL));
    return R;
}

// bool takeFilter( struct data * data, bool(*filter(int ))(struct data*), int value ){
//     return filter(value)(data);
// }


int main() {
    printf("Main...\n" );

    struct data *jhon  = Data.of(50, "Jhon", "Doe", 1999, "my@email.com");
    Data.setTravelData(jhon, EUROPE, FIRST, LESS_3_TIMES, ONE_DAY);

    jhon->country = ASIA;

    travelFrom_test( true );
    printf("takeFilter(): %d\n", takeFilter(jhon, Filter.travelFrom, EUROPE));

    printf("takeFilter(): %d\n", takeFilter(jhon, Filter.travelClass, FIRST));


    // struct data *jhon = (struct data*)malloc(sizeof(struct data));
    // jhon->country = EUROPE;





    // printf("is UK: %d\n", Filter.travelFrom(UK)(jhon));
    // printf("is EUROPE: %d\n", Filter.travelFrom(EUROPE)(jhon));
    // printf("%d\n", Filter.travelFrom(ASIA)(jhon));

    printf("%d\n", Filter.travelClass(FIRST)(jhon));
    printf("%d\n", Filter.travelClass(ECONOMY)(jhon));


    return 0;
}
