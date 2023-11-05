#include "my.h"
#include "../../lib/std_lib_facilities.h"

int foo = 0; // global variable defined here,
             // declared with extern keyword elsewhere

void print_foo() {
    std::cout << foo << '\n';
}

void print(int i) {
    std::cout << i << '\n';
}
