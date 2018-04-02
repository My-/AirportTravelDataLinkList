#include "./src/test/test.h"
#include "./test/admin_test.h"
#include "./test/data_test.h"
#include "./test/filter_test.h"


int main() {

    admin_runAll();
    data_runAll();
    filter_runAll();

    return 0;
}
