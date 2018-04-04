/**
*   @by Mindaugas Sharskus
*   @date 2/04/2018
*/

#ifndef TEST_C
#define TEST_C


#include "test.h"


struct test Test = {
    .display = test_display,
    .assertTrue = test_assertTrue,
    .assertFalse = test_assertFalse,
    .assertEqual_String = test_assertEqual_String,
    .assertEqual_Int = test_assertEqual_Int
};

void test_display(char* text, char* color){
    printf("%s%s\n" COLOR_RESET, color, text);
}

bool test_assertTrue(bool actual, char * message){
    printf("%s: %s - ", message, (YELLOW_TEXT "true" COLOR_RESET));
    if( actual ){ printf("%s\n", PASS); }
    else{ printf("%s\n", FAIL); }

    return actual;
}

bool test_assertFalse(bool actual, char * message){
    printf("%s: %s - ", message, (YELLOW_TEXT "false" COLOR_RESET));
    if( !actual ){ printf("%s\n", PASS); }
    else{ printf("%s\n", FAIL); }

    return !actual;
}

bool test_assertEqual_String(char* expected, char* actual, char * message){
    bool R = true;
    printf("%s: %s%s%s - ", message, YELLOW_TEXT, expected, COLOR_RESET);
    int compare = strcmp(expected, actual);
    if( compare == 0 ){ printf("%s\n", PASS); }
    else{
        printf("%s\n", FAIL);
        printf("\tExpexted: %s\n", expected);
        printf("\tBut was : %s\n", actual);
        R = false;
    }

    return R;
}

bool test_assertEqual_Int(int expected, int actual, char * message){
    bool R = true;
    printf("%s: %s%d%s - ", message, YELLOW_TEXT, expected, COLOR_RESET);
    int compare = expected -actual;
    if( compare == 0 ){ printf("%s\n", PASS); }
    else{
        printf("%s\n", FAIL);
        printf("\tExpexted: %d\n", expected);
        printf("\tBut was : %d\n", actual);
        R = false;
    }

    return R;
}


#endif
