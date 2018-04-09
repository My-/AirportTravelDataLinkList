
#include "./test/admin_test.h"
#include "./test/data_test.h"
#include "./test/filter_test.h"
#include "./test/node_test.h"
#include "./test/list_test.h"
#include "./test/db_test.h"


#define STR_LENGTH 30


/***************************************************************/




/***************************************************************/


int main() {
    char * adminName = adminLogin();
    puts(adminName);




    return 0;
}
