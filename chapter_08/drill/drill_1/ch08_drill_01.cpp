#include "my.h"
#include <iostream>
extern int foo;

int main()
{
        foo = 7;
        print_foo();
        print(99);
        char c; std::cin >> c; // Equivalent of keep_window_open()
        return 0;
}
