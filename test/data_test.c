

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


// https://stackoverflow.com/questions/1025589/setting-variable-to-null-after-free
void data_delete_test(){
    Test.display("Data remove test", MAGENTA_TEXT);

    struct node * node = Node.of(
        Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com")
    );

    Data.remove(&node->data);
    Test.assertTrue(node->data == NULL, "Data.remove()");
}

void data_email_test(){
    Test.display("Email test", MAGENTA_TEXT);
    struct data *data = Data.empty();

    Test.assertTrue( Data.setEmail(data, "er@we.we"), "er@we.we" );
    Test.assertTrue( Data.setEmail(data, "r@w.e"), "r@w.e" );
    Test.assertFalse( Data.setEmail(data, "@we.we"), "@we.we" );
    Test.assertFalse( Data.setEmail(data, "er@wewe"), "er@wewe" );
    Test.assertFalse( Data.setEmail(data, "er@we."), "er@we." );
    Test.assertFalse( Data.setEmail(data, "er@.we"), "er@.we" );
}

void data_stringify_test(){
    Test.display("Stringify Test", MAGENTA_TEXT);

    struct data *jhon = Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com");
    Data.setTravelData(jhon, UK, ECONOMY, LESS_3_TIMES, MORE_7_DAYS);

    puts(Data.toString(jhon));
    puts(Data.toJSON(jhon));
    puts(Data.toCSON(jhon));
    puts(Data.toData(jhon));
}

void data_runAll(){
    Test.display("Data Test", BLUE_TEXT);
    data_of_test();
    data_delete_test();
    data_email_test();
    data_stringify_test();
}

// int main(int argc, char const *argv[]) {
//     puts("Running");
//     data_runAll();
//     return 0;
// }
