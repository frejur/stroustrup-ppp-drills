#include "my.h"
extern int foo;

namespace ch08_drill_01
{

    int main()
    {
        foo = 7;
        print_foo();
        print(99);
        return 0;
    }
}