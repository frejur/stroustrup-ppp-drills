#include <iostream>
#include <ctime>
#include "../../util.h"

using namespace std;

/* Complete the code fragment on page 384, try the
 * folowing input:
 *      1234 4d2 2322 2322
 * Then the following:
 *      1234 1234 1234 1234
 * Explain the results and try some other inputs */
int main()
{
    int a, b, c, d;

    while (cin) {
        cin >> a >> hex >> b >> oct >> c >> d;
        cout << a << '\t' << b << '\t' << c << '\t' << d << endl;
    }

    exit_on_return();
    return 0;
}
