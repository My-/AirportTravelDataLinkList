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
    List.showAll(db->list);
}



void db_runAll(){
    Test.display("DataBase Test", BLUE_TEXT);
    db_login_test();
    db_load_test();
}
