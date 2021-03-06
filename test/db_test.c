#include "db_test.h"

void db_login_test(){
    Test.display("DB login test", MAGENTA_TEXT);
    struct db *db = DataBase.empty();

    Test.assertTrue( DataBase.login(db, "aaa", "111"), "adminLoginValidate(\"aaa\", \"111\")" );
    Test.assertTrue( DataBase.login(db, "bbb", "222"), "adminLoginValidate(\"bbb\", \"222\")" );
    Test.assertTrue( DataBase.login(db, "ccc", "333"), "adminLoginValidate(\"ccc\", \"333\")" );

    Test.assertFalse( DataBase.login(db, "cca", "333"), "adminLoginValidate(\"cca\", \"333\")" );
    Test.assertFalse( DataBase.login(db, "aaa", "11"), "adminLoginValidate(\"aaa\", \"11\")" );
    Test.assertFalse( DataBase.login(db, "bbb", "333"), "adminLoginValidate(\"bbb\", \"333\")" );
    Test.assertFalse( DataBase.login(db, "bbb", "2222"), "adminLoginValidate(\"bbb\", \"2222\")" );
}

void db_load_test(){
    Test.display("DB load test", MAGENTA_TEXT);
    struct db *db = DataBase.empty();

    DataBase.load(db, DB_FILE);
    Test.assertEqual_Int(8, List.size(db->list), "list size");
    // List.showAll(db->list);

    Test.display("DB add record test", MAGENTA_TEXT);

    struct data *benny = Data.of(15, "Benny", "Hill ", 1924, "bhill@mail.com");
    Data.setTravelData(benny, UK, ECONOMY, LESS_3_TIMES, MORE_7_DAYS);
    DataBase.addRecord(db, benny);

    Test.assertEqual_Int(15, List.get(db->list, 6)->id, "at index 6");
    Test.assertEqual_Int(19, List.getLast(db->list)->id, "at last index");

    Test.assertEqual_Int(9, List.size(db->list), "list size");

    // List.showAll(db->list);
}



void db_search_test(){
    Test.display("DB Search test", MAGENTA_TEXT);

    struct list *list;
    struct data* data = Data.empty();
    struct db *db = DataBase.empty();
    DataBase.load(db, DB_FILE);

    // List.showAll(db->list);

    data->id = 11;
    list = DataBase.search(db, data, Data.equals, Data.compareId);
    Test.assertEqual_Int(data->id, List.getFirst(list)->id, "search");
    // puts("");
    // List.showAll(list);

    data->id = 1;
    list = DataBase.search(db, data, Data.equals, Data.compareId);
    Test.assertEqual_Int(data->id, List.getFirst(list)->id, "search");

    // puts("");
    // List.showAll(list);

    data->id = 19;
    list = DataBase.search(db, data, Data.equals, Data.compareId);
    Test.assertEqual_Int(data->id, List.getFirst(list)->id, "search");
    // puts("");
    // List.showAll(list);

    data->country = UK;
    list = DataBase.search(db, data, Data.equals, Data.compareCountry);
    Test.assertEqual_Int(4, List.size(list), "search");
    // puts("");
    // List.showAll(list);

    data->yearBorn = 1900;
    list = DataBase.search(db, data, Data.less, Data.compareBornDate);
    Test.assertEqual_Int(4, List.size(list), "search");
    // puts("");
    // List.showAll(list);

}

void db_save_test(){
    Test.display("DB Save test", MAGENTA_TEXT);

    struct list *list;
    struct data* data = Data.empty();
    struct db *db = DataBase.empty();
    DataBase.load(db, DB_FILE);

    List.showAll(db->list);

    List.saveToFile(db->list, "./res/passengersOut.txt", Data.toCSON);
}

void db_runAll(){
    Test.display("DataBase Test", BLUE_TEXT);
    db_login_test();
    db_load_test();
    db_search_test();
    db_save_test();
}
