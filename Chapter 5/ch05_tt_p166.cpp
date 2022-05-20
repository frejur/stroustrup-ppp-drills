#include "std_lib_facilities.h"

namespace ch05_tt_p166
{
    /*  Let’s look at our area function (from §5.6.1) again:
        (...)
        Find a pair of values so that the pre-condition of
        this version of area holds, but the post-condition
        doesn’t.
        */

    int area(int length, int width)
        // calculate area of a rectangle;
        // pre-conditions: length and width are positive
        // post-condition: returns a positive value that is the area
    {
        if (length <= 0 || width <= 0)
            cerr << "area() pre-condition error\n";
        int a = length * width;
        if (a <= 0) cerr << "area() post-condition error\n";
        return a;
    }

    int main()
    {
        const int a = -1, b = 1;
        cout << "Calculating area for rectangle A: " << a << " times " << b << "...\n";
        int area_a = area(a, b); // pre-condition error (and post)
        cout << "= " << area_a << '\n';

        constexpr int c = numeric_limits<int>::max(), d = 2;
        cout << "Calculating area for rectangle B: " << c << " times " << d << "...\n";
        int area_b = area(numeric_limits<int>::max(), d);
        // post_condition error due to integer overflow
        cout << "= " << area_b << '\n';

        int overflow = c + 1;
        // demonstrate integer overflow
        cout << "integer overflow: " << c << " + " << "1 = " << overflow << '\n';

        getchar();

        return 0;
    }
}