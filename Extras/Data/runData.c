#include "data.h"



int main() {

    struct data *jhon = Data.of(50, "Jhon", "Doe", 1999, "my@email.com");
    Data.setTravelData(jhon, UK, FIRST, LESS_3_TIMES, ONE_DAY);

    // printf("%s\n", Data.getEmail(jhon));
    // printf("%s\n", jhon->email);
    // printf("%s\n", data_getEmail(jhon));

    printf("%s\n", Data.toString(jhon));


    // printf("%d\n", jhon->id);
    // Data.getName(jhon);
    // Data.setId(jhon, 30);
    // printf("%d\n", jhon->id);
    //
    // printf("%d\n", Data.counter);

    // struct data *doe = Data.of(5, "doe");
    //
    // printf("%d\n", Data.counter);
    //
    // Data.delete(doe);
    // Data.getName(doe);
    // Data.getName(jhon);
    // printf("%d\n", Data.counter);
    //
    //
    // struct data * tom = malloc(sizeof(struct data*));
    //
    // tom->name = "Tom";
    // tom->id = 3;
    //
    // Data.getName(tom);


    return 0;
}
