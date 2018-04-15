#include "menu_test.h"

void menu_report_test(){
    Test.display("DB Search test", MAGENTA_TEXT);

    struct db *db = DataBase.empty();
    DataBase.load(db, DB_FILE);

    // Menu.report(db);
    puts(currentTime());

}



void menu_runAll(){
    Test.display("Menu Test", BLUE_TEXT);

    menu_report_test();

}
