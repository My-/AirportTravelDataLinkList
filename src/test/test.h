#ifndef TEST_H
#define TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>    // boolean
#include <string.h>     // string

#include "color.h"

#define FAIL (RED_TEXT "FAIL" COLOR_RESET)
#define PASS (GREEN_TEXT "PASS" COLOR_RESET)

void test_display(char* text, char * color);
bool test_assertTrue( bool actual, char * message );
bool test_assertFalse( bool actual, char * message );
bool test_assertEqual_String( char* expected, char* actual, char * message );
bool test_assertEqual_Int( int expected, int actual, char * message );


extern struct test {
    void (*display)(char * text, char * color);
    bool (*assertTrue)( bool actual, char * message );
    bool (*assertFalse)( bool actual, char * message );
    bool (*assertEqual_String)( char* expected, char* actual, char * message );
    bool (*assertEqual_Int)( int expected, int actual, char * message );
} Test;

#endif
