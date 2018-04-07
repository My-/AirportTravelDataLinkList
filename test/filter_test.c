
#include "filter_test.h"

void filter_takeFilter_test(){
    struct data *jhon = Data.of(50, "Jhon", "Doe", 1999, "my@email.com");
    Data.setTravelData(jhon, EUROPE, FIRST, LESS_3_TIMES, ONE_DAY);

    Test.assertTrue( Filter.on(jhon, Filter.travelFrom, EUROPE), "takeFilter()");
    Test.assertTrue( Filter.on(jhon, Filter.travelClass, FIRST), "takeFilter()");
    Test.assertTrue( Filter.on(jhon, Filter.travelFrequency, LESS_3_TIMES), "takeFilter()");
    Test.assertTrue( Filter.on(jhon, Filter.stayDuration, ONE_DAY), "takeFilter()");

    Test.assertFalse( Filter.on(jhon, Filter.travelFrom, UK), "takeFilter()");
    Test.assertFalse( Filter.on(jhon, Filter.travelClass, BUSINESS), "takeFilter()");
    Test.assertFalse( Filter.on(jhon, Filter.travelFrequency, LESS_5_TIMES), "takeFilter()");
    Test.assertFalse( Filter.on(jhon, Filter.stayDuration, MORE_7_DAYS), "takeFilter()");
}

void filter_filters_test(){
    struct data *jhon = Data.of(50, "Jhon", "Doe", 1999, "my@email.com");
    Data.setTravelData(jhon, EUROPE, FIRST, LESS_3_TIMES, ONE_DAY);

    Test.assertTrue( Filter.travelFrom(EUROPE)(jhon), "Filter.travelFrom(EUROPE)(jhon)");
    Test.assertFalse( Filter.travelFrom(UK)(jhon), "Filter.travelFrom(UK)(jhon)");
    jhon->country = ASIA;
    Test.assertTrue( Filter.travelFrom(ASIA)(jhon), "Filter.travelFrom(ASIA)(jhon)");
    Test.assertFalse( Filter.travelFrom(EUROPE)(jhon), "Filter.travelFrom(EUROPE)(jhon)");

    Test.assertFalse( Filter.travelClass(ECONOMY)(jhon), "Filter.travelClass(ECONOMY)(jhon)");
    Test.assertTrue( Filter.travelClass(FIRST)(jhon), "Filter.travelClass(ECONOMY)(jhon)");
    jhon->travelClass = BUSINESS;
    Test.assertTrue( Filter.travelClass(BUSINESS)(jhon), "Filter.travelClass(BUSINESS)(jhon)");
    Test.assertFalse( Filter.travelClass(ECONOMY)(jhon), "Filter.travelClass(ECONOMY)(jhon)");


}


void filter_runAll(){
    Test.display("Filter Test", BLUE_TEXT);
    filter_takeFilter_test();
    filter_filters_test();
}
