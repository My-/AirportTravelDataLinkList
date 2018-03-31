#include "filter.h"
#include "../Data/data.h"

int main() {
    printf("Main...\n" );

    // struct data *jhon = (struct data*)malloc(sizeof(struct data));
    // jhon->country = EUROPE;

    struct data *jhon  = Data.of(50, "Jhon", "Doe", 1999, "my@email.com");
    Data.setTravelData(jhon, EUROPE, FIRST, LESS_3_TIMES, ONE_DAY);

    jhon->country = ASIA;

    // printf("is UK: %d\n", Filter.travelFrom(UK)(jhon));
    // printf("is EUROPE: %d\n", Filter.travelFrom(EUROPE)(jhon));
    // printf("%d\n", Filter.travelFrom(ASIA)(jhon));

    printf("%d\n", Filter.travelClass(FIRST)(jhon));
    printf("%d\n", Filter.travelClass(ECONOMY)(jhon));


    return 0;
}
