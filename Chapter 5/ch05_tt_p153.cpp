#include "std_lib_facilities.h"

namespace ch05_tt_p153
{
    // To see what an uncaught exception error looks like, 
    // run a small program that uses error() without
    // catching any exceptions.

    // calculate area of a rectangle;
    int area(int length, int width)
    {
        if (length <= 0 || width <= 0)
            throw runtime_error("Invalid arguments");
        return length * width;
    }

    int main()
    {
        int x, y, a;
        char c;

        cout << "Enter two integer values followed by either 'c' "
            << "to catch errors, or 'e' to throw errors "
            << "without catching."
            << "\n>";

        while (cin >> x >> y >> c) {
            switch (c)
            {
            case 'c':
                try { a = area(x, y); }
                catch (runtime_error) { } // will throw an error
                                          // but 'a' won't be assigned the return value
                                          // it will be an uninitialized variable which
                                          // can cause major headache
                break;
            case 'e':
                a = area(x, y); // will still throw an error: Unhandled exception at 0x7674A842
                                // and 'a' will be assigned the (undesired) return value
                break;
            default:
                continue;
                break;
            }

            cout << a << '\n';
        }
        return 0;
    }
}