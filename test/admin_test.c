#include "admin_test.h"

bool adminLogin_test(bool show){
    bool R = true, b;
    char v1[10], v2[10];

    strcpy(v1, "aaa"); strcpy(v2, "111");
    b = adminLoginValidate(v1, v2);
    if( show ){ printf( "adminLoginValidate(%s, %s) - %s\n", v1, v2, (b ? PASS : FAILL) ); }
    R &= b;

    strcpy(v1, "aaa"); strcpy(v2, "222");
    b = adminLoginValidate(v1, v2);
    if( show ){ printf( "adminLoginValidate(%s, %s) - %s\n", v1, v2, (b ? PASS : FAILL) ); }
    R &= b;

    printf("%s%s%s\n\n", YELLOW_TEXT "adminLogin_test()" COLOR_RESET, " - ", (R ? PASS : FAILL));
    return R;
}

bool runAll_adminTest(bool show){
    bool R = true, b;

    b = adminLogin_test(show);
    if( show ){ printf("adminLogin_test() - %s\n", (b ? PASS : FAILL) ); }
    R &= b;

    printf("%s%s%s\n\n", YELLOW_TEXT "runAll_adminTest()" COLOR_RESET, " - ", (R ? PASS : FAILL));
    return R;
}
