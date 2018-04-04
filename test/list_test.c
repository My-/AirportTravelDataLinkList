
#include "list_test.h"

void list_create_test(){
    Test.display("List create test", MAGENTA_TEXT);
    struct list* myList = List.empty();

    Test.assertEqual_Int(0, myList->size, "empty list");
    Test.assertFalse(myList->FIRST_NODE, "empty list");

    myList = List.of(
        Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com")
    );
    Test.assertEqual_Int(1, myList->size, "One node list");
    Test.assertTrue(myList->FIRST_NODE, "One node list");
    Test.assertEqual_Int(11, myList->FIRST_NODE->data->id, "One node list. Test id");
}

void list_get_test(){
    Test.display("List get data test", MAGENTA_TEXT);
    struct list* myList = List.of(
        Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com")
    );
    List.addEnd(myList,
        Data.of(22, "Bob", "Doe", 2000, "jhon@mail.com")
    );
    List.addEnd(myList,
        Data.of(33, "Clob", "Doe", 2000, "jhon@mail.com")
    );

    Test.assertEqual_String("Jhon", List.get(myList)->name, "Testin get");
    Test.assertEqual_String("Bob", List.next(myList)->name, "Testin next");
    Test.assertEqual_String("Clob", List.next(myList)->name, "Testin next");
    Test.assertFalse(List.next(myList), "Testin next");
    Test.assertEqual_String("Bob", List.prev(myList)->name, "Testin prev");
    Test.assertEqual_String("Jhon", List.prev(myList)->name, "Testin prev");
    Test.assertFalse(List.prev(myList), "Testin prev");
    Test.assertEqual_String("Jhon", List.get(myList)->name, "Testin get");
}

void list_add_test(){
    Test.display("List add data test", MAGENTA_TEXT);
    struct list* myList = List.empty();

    List.addEnd(myList,
        Data.of(22, "Bob", "Doe", 2000, "jhon@mail.com")
    );
    List.addEnd(myList,
        Data.of(33, "Clob", "Doe", 2000, "jhon@mail.com")
    );
    List.addFront(myList,
        Data.of(5, "Alob", "Doe", 2000, "jhon@mail.com")
    );
    // Alob >> Bob >> Clob
    Test.assertEqual_String("Alob", myList->FIRST_NODE->data->name, "list first node");
    Test.assertEqual_String("Bob", myList->FIRST_NODE->NEXT->data->name, "list first node");
    Test.assertEqual_String("Clob", myList->FIRST_NODE->NEXT->NEXT->data->name, "list first node");

}

void list_insert_test(){
    Test.display("List insert data node test", MAGENTA_TEXT);
    struct list* myList = List.empty();

    List.insertAfter(myList,
        Data.of(22, "Bob", "Doe", 2000, "jhon@mail.com")
    );
    List.insertAfter(myList,
        Data.of(22, "Cob", "Doe", 2000, "jhon@mail.com")
    );
    List.insertAfter(myList,
        Data.of(22, "Dob", "Doe", 2000, "jhon@mail.com")
    );

    // Bob >> Dob >> Cob
    Test.assertEqual_Int(3, myList->size, "size check");
    Test.assertEqual_String("Bob", myList->CURRENT_NODE->data->name, "insert after test");
    Test.assertEqual_String("Dob", myList->CURRENT_NODE->NEXT->data->name, "insert after test");
    Test.assertEqual_String("Cob", myList->CURRENT_NODE->NEXT->NEXT->data->name, "insert after test");

    myList = List.empty();
    List.insertBefore(myList,
        Data.of(22, "Bob", "Doe", 2000, "jhon@mail.com")
    );
    List.insertBefore(myList,
        Data.of(22, "Cob", "Doe", 2000, "jhon@mail.com")
    );
    List.insertBefore(myList,
        Data.of(22, "Dob", "Doe", 2000, "jhon@mail.com")
    );

    // Cob >> Dob >> Bob
    Test.assertEqual_Int(3, myList->size, "size check");
    Test.assertEqual_String("Cob", myList->CURRENT_NODE->PREV->PREV->data->name, "insert before test");
    Test.assertEqual_String("Dob", myList->CURRENT_NODE->PREV->data->name, "insert before test");
    Test.assertEqual_String("Bob", myList->CURRENT_NODE->data->name, "insert before test");
}


void list_runAll(){
    Test.display("List tests", BLUE_TEXT);

    list_create_test();
    list_get_test();
    list_add_test();
    list_insert_test();
}
