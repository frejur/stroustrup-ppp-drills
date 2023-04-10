#include <system_error>
#include <iostream>
#include "drill.h"

int main()
{
    try
    {
        B1 b1;
        b1.f();
        std::cout << '\n';
        b1.vf();
        std::cout << '\n';

        D1 d1;
        d1.f();
        std::cout << '\n';
        d1.vf();
        std::cout << '\n';

        return 0;
    }
    catch (std::exception& e) {
        return 1;
    }
    catch (...) {
        return 2;
    }
}
