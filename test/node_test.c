
#include "node_test.h"

void node_of_test(){
    struct data *jhon = Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com");
    struct data *bob = Data.of(11, "Bob", "Doe", 2000, "jhon@mail.com");
    struct node * head = Node.of(jhon);

    Test.display("Node creation test", MAGENTA_TEXT);
    Test.assertEqual_String("Jhon", Node.getData(head)->name, "Node.getData(head)");
    Test.assertFalse(head->NEXT, "head->NEXT");

    head->NEXT = Node.of(bob);
    Test.assertTrue(head->NEXT, "head->NEXT");
    Test.assertEqual_String("Bob", head->NEXT->data->name, "head->NEXT->data->name");


}

void node_has_test(){
    struct node *head = Node.of(
        Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com")
    );
    head->NEXT = Node.of(
        Data.of(11, "Bob", "Doe", 2000, "jhon@mail.com")
    );
    head->NEXT->PREV = head;

    Test.display("Node has test", MAGENTA_TEXT);
    Test.assertFalse(Node.hasPrev(head), "Node.hasPrev(head)");
    Test.assertTrue(Node.hasPrev(head->NEXT), "Node.hasPrev(head->NEXT)");
    Test.assertTrue(Node.hasNext(head), "Node.hasNext(head)");
    Test.assertFalse(Node.hasNext(head->NEXT), "Node.hasNext(head->NEXT)");
}

void node_remove_test(){
    struct node *head = Node.of(
        Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com")
    );

    Test.display("Node remove test", MAGENTA_TEXT);
    Test.assertTrue(false, "TODO: Fix Node.remove(), fix Dta.Delate first");
    // Test.assertTrue(Node.getData(head), "has data");
    // Node.remove(head);
    // Test.assertFalse(head, "has data");

}

void node_insert_test(){
    struct node *head = Node.of(
        Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com")
    );

    Test.display("Node insetion test", MAGENTA_TEXT);
    Test.assertFalse(Node.hasPrev(head), "Node.hasNext(head)");
    Test.assertFalse(Node.hasNext(head), "Node.hasNext(head)");

    Node.insertAfter(head, Data.of(11, "Aaran", "Doe", 2000, "jhon@mail.com") );
    Node.insertBefore(head->NEXT, Data.of(11, "Baran", "Doe", 2000, "jhon@mail.com") );
    Node.insertBefore(head, Data.of(11, "Canal", "Doe", 2000, "jhon@mail.com") );
    // Canal -> Jhon -> Baran -> Aaran
    Test.assertEqual_String("Canal", head->PREV->data->name, "Canal should be first node");
    Test.assertEqual_String("Jhon", head->data->name, "Jhon should be second node");
    Test.assertEqual_String("Baran", head->NEXT->data->name, "Baran should be third node");
    Test.assertEqual_String("Aaran", head->NEXT->NEXT->data->name, "Aaran should be last node");
}

void node_getData_test(){
    struct node *head = Node.of(
        Data.of(11, "Jhon", "Doe", 2000, "jhon@mail.com")
    );

    Test.display("Node getData test", MAGENTA_TEXT);
    Test.assertEqual_Int( 11, Node.getData(head)->id, "Checking id");
}

void node_runAll(){
    Test.display("Node Test", BLUE_TEXT);
    node_of_test();
    node_has_test();
    node_remove_test();
    node_insert_test();
    node_getData_test();
}
