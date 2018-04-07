
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

    Test.assertEqual_String("Jhon", List.getFirst(myList)->name, "Testin get");
    Test.assertEqual_String("Bob", List.getNext(myList)->name, "Testin next");
    Test.assertEqual_String("Clob", List.getNext(myList)->name, "Testin next");
    Test.assertFalse(List.getNext(myList), "Testin next");
    Test.assertEqual_String("Bob", List.getPrev(myList)->name, "Testin prev");
    Test.assertEqual_String("Jhon", List.getPrev(myList)->name, "Testin prev");
    Test.assertFalse(List.getPrev(myList), "Testin prev");
    Test.assertEqual_String("Jhon", List.getFirst(myList)->name, "Testin get");
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

void list_insertSorted_test(){
    Test.display("List insert ordered data test", MAGENTA_TEXT);
    struct list* myList = List.of( Data.of(1, "Jhon", "Doe", 2001, "jhon@mail.com") );
    List.addEnd( myList, Data.of(3, "Bob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(5, "Clob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(7, "Clob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(11, "Clob", "Doe", 2000, "jhon@mail.com") );

    List.insert( myList, Data.of(2, "Clob", "Doe", 2000, "jhon@mail.com"), Data.compareId );
    List.insert( myList, Data.of(6, "Clob", "Doe", 2000, "jhon@mail.com"), Data.compareId );
    List.insert( myList, Data.of(13, "Clob", "Doe", 2000, "jhon@mail.com"), Data.compareId );

    List.showAll(myList);
    Test.assertEqual_Int(8, List.size(myList), "size check");
    Test.assertEqual_Int(2, List.get(myList, 1)->id, "at index 1");
    Test.assertEqual_Int(6, List.get(myList, 4)->id, "at index 4");
    Test.assertEqual_Int(13, List.get(myList, 7)->id, "at index 7");
}

void list_getAtIndex_test(){
    Test.display("List getAtIndex test", MAGENTA_TEXT);
    struct list* myList = List.empty();

    List.addEnd( myList, Data.of(1, "Bob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(2, "Clob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(3, "Clob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(4, "Clob", "Doe", 2000, "jhon@mail.com") );

    Test.assertEqual_Int( 4, List.size(myList), "size check" );
    Test.assertEqual_Int( 1, List.get(myList, 0)->id, "id at index: 0" );
    Test.assertEqual_Int( 2, List.get(myList, 1)->id, "id at index: 1" );
    Test.assertEqual_Int( 3, List.get(myList, 2)->id, "id at index: 2" );
    Test.assertEqual_Int( 4, List.get(myList, 3)->id, "id at index: 3" );
}



void list_sort_test(){
    Test.display("List sort test", MAGENTA_TEXT);
    struct list* myList = List.of( Data.of(35, "Jhon", "Doe", 2001, "jhon@mail.com") );
    List.addEnd( myList, Data.of(33, "Bob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(42, "Clob", "Doe", 2003, "jhon@mail.com") );
    List.addEnd( myList, Data.of(10, "Bob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(14, "Clob", "Doe", 2003, "jhon@mail.com") );
    List.addEnd( myList, Data.of(19, "Bob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(27, "Clob", "Doe", 2003, "jhon@mail.com") );
    List.addEnd( myList, Data.of(44, "Bob", "Doe", 2000, "jhon@mail.com") );
    List.addEnd( myList, Data.of(26, "Clob", "Doe", 2003, "jhon@mail.com") );
    List.addEnd( myList, Data.of(31, "Bob", "Doe", 2000, "jhon@mail.com") );

    Test.assertEqual_Int(10, List.size(myList), "size check");
    List.showAll(myList);

    List.sort(myList, Data.compareId);
    Test.assertEqual_Int(10, List.get(myList, 0)->id, "id at index: 0");
    Test.assertEqual_Int(14, List.get(myList, 1)->id, "id at index: 1");
    Test.assertEqual_Int(19, List.get(myList, 2)->id, "id at index: 2");
    Test.assertEqual_Int(26, List.get(myList, 3)->id, "id at index: 3");
    Test.assertEqual_Int(27, List.get(myList, 4)->id, "id at index: 4");
    Test.assertEqual_Int(31, List.get(myList, 5)->id, "id at index: 5");
    Test.assertEqual_Int(33, List.get(myList, 6)->id, "id at index: 6");
    Test.assertEqual_Int(35, List.get(myList, 7)->id, "id at index: 7");
    Test.assertEqual_Int(42, List.get(myList, 8)->id, "id at index: 8");
    Test.assertEqual_Int(44, List.get(myList, 9)->id, "id at index: 9");
}

void list_runAll(){
    Test.display("List tests", BLUE_TEXT);

    list_create_test();
    list_get_test();
    list_add_test();
    list_insert_test();
    list_insertSorted_test();
    list_getAtIndex_test();
    list_sort_test();
}
