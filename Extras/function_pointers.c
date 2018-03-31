

#include <stdio.h>
#include <string.h>

int size(const char * str){
    printf("%s\n", str);
    return strlen(str);
}

// int puts(const char *str)
/*
Takes function and returns function.

int ( *idputs( int(*f)(const char *) ) )(const char *){ return f; }
               |-><--||------------|                    // |return><name||parameters
      |------><----------------------|                  // |return><name|
|--><----------------------------------||------------|  // |return><name||parameters|
*/

// takes function as parameter and returns function.
int ( *idputs( int(*f)(const char *) ) )(const char *) {
    return f;
}

// tkes function as parameter returns int
int printHi(int(*f)(const char *), char* str){
    return f(str);
}


int add(int x, int y){
    return x + y;
}

int sub(int x, int y){
    return x -y;
}

// takes int and return functions
// https://stackoverflow.com/questions/20617067/returning-function-pointer-type
int (*getFunc(int n))(int, int) {
    int (*test)(int a, int b);
    switch(n){
        case 1: test = add; puts("add"); break;
        case 2: test = sub; puts("sub"); break;
    }
    return test;
}


// int ( *math( int y, int x ) )(int n) {
//     switch(n)(
//         case 1: return add;
//         case 2: return sub;
//     )
// }

int main(){

    // const char* str = "uglyC";
    // printf("%d\n", size(str));
    //
    // idputs(puts)("Hey!");
    // printf("%d\n", idputs(size)(str));

    // printf("%d\n", printHi(size, "hi"));

    printf("%d\n", getFunc(1)(3, 5));
    printf("%d\n", getFunc(2)(3, 5));

    return 0;
}
