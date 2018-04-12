
#include "./src/admin/admin.h"
#include "./src/data/data.h"
#include "./src/filter/filter.h"
#include "./src/node/node.h"
#include "./src/list/list.h"
#include "./src/db/db.h"
#include "./src/menu/menu.h"


#define STR_LENGTH 30


/***************************************************************/




/***************************************************************/


int main() {
    // char * adminName = adminLogin();
    char * adminName = "adminLogin()";
    puts(adminName);

    struct db * db = DataBase.empty();
    if( !DataBase.load(db, DB_FILE) ){
        puts("No previous Data Base records found!");
    }

    Menu.main(db);





    return 0;
}
