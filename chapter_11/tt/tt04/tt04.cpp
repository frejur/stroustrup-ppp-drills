#include <iostream>
#include <ctime>
#include "../../util.h"

using namespace std;

/* Write some code to print the number:
 *      1234567.89
 * Three times, using:
 *      1. defaultfloat
 *      2. fixed
 *      3. scientific
 * Which output gives the most accurate representation?
 * Explain why. */

int main()
{
    const auto num{ 1234567.89 };

    cout <<
        "defaultfloat"  << '\t' << '\t' <<
            num << '\n' <<
        "fixed"         << '\t' << '\t' << '\t' <<
            fixed <<
            num << '\n' <<
        "scientific"    << '\t' << '\t' <<
            scientific <<
            num << endl;

    exit_on_return();
    return 0;
}

/* Output:
 * defaultfloat            1.23457e+06
 * fixed                   1234567.890000 (Most accurate)
 * scientific              1.234568e+06
 *
 * The default precision is: 6
 *
 * When using the 'defaultfloat' notation this number
 * determines the number of significant digits:
 * 1 . 2 3 4 5 7 e+06
 * ^   ^ ^ ^ ^ ^
 * 1   2 3 4 5 6
 *
 * When 'fixed' and 'scientific' notations are used, this
 * number is used to determine the number of decimal places:
 * 1 2 3 4 5 6 7 . 8 9 0 0 0 0
 * ^ ^ ^ ^ ^ ^ ^   ^ ^ ^ ^ ^ ^
 * 0 0 0 0 0 0 0   1 2 3 4 5 6
 *
 * 1 . 2 3 4 5 6 8 e+06
 * ^   ^ ^ ^ ^ ^ ^
 * 0   1 2 3 4 5 6
 * /
