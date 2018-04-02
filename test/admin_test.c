
#include "admin_test.h"


void admin_login_test(){
    Test.assertTrue( adminLoginValidate("aaa", "111"), "adminLoginValidate(\"aaa\", \"111\")" );
    Test.assertTrue( adminLoginValidate("bbb", "222"), "adminLoginValidate(\"bbb\", \"222\")" );
    Test.assertTrue( adminLoginValidate("ccc", "333"), "adminLoginValidate(\"ccc\", \"333\")" );

    Test.assertFalse( adminLoginValidate("cca", "333"), "adminLoginValidate(\"cca\", \"333\")" );
    Test.assertFalse( adminLoginValidate("aaa", "11"), "adminLoginValidate(\"aaa\", \"11\")" );
    Test.assertFalse( adminLoginValidate("bbb", "333"), "adminLoginValidate(\"bbb\", \"333\")" );
    Test.assertFalse( adminLoginValidate("bbb", "2222"), "adminLoginValidate(\"bbb\", \"2222\")" );
}

void admin_runAll(){
    admin_login_test();
}

// int main(){
//     admin_runAll();
// }
