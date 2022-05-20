#include "my.h"
#include "std_lib_facilities.h"

int foo = 0; // global variable defined here,
             // declared with extern keyword elsewhere

void print_foo() {
    cout << foo << '\n';
}

void print(int i) {
    cout << i << '\n';
}