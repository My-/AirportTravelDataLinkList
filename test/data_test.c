

#include "data_test.h"


void data_of_test(){
    struct data *jhon = Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com");
    Data.setTravelData(jhon, UK, ECONOMY, LESS_3_TIMES, MORE_7_DAYS);

    if( Test.assertEqual_String == NULL ){ puts("is null"); }
    Test.assertEqual_String("Jhon", jhon->name, "Testing name");
    Test.assertEqual_String("Doe", jhon->surname, "Testing surname");
    Test.assertEqual_String("jhon@mail.com", jhon->email, "Testing email");
    Test.assertEqual_Int(11, jhon->id, "Testing id");
    jhon->id = 60;
    Test.assertEqual_Int(60, jhon->id, "Testing id");
    Test.assertEqual_Int(2000, jhon->yearBorn, "Testing Year");
    Test.assertEqual_Int(ECONOMY, jhon->travelClass, "Testing travel class");
}

void data_delete_test(){
    struct data *jhon = Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com");
    Data.setTravelData(jhon, UK, ECONOMY, LESS_3_TIMES, MORE_7_DAYS);

    Test.display("Node remove test", MAGENTA_TEXT);
    // Data.delete(jhon);
    Test.assertTrue(false, "TODO: Fix Data.delete()");
}

void data_runAll(){
    Test.display("Data Test", BLUE_TEXT);
    data_of_test();
    data_delete_test();
}

// int main(int argc, char const *argv[]) {
//     puts("Running");
//     data_runAll();
//     return 0;
// }
