#include <iostream>
#include <ctime>
#include "../../util.h"

using namespace std;

/* Output your birth year in decimal, hexadecimal and octal form.
 * Label each value and line up the output in columns using the
 * tab character. Also output your age.
 */
int main()
{
    int birth_year{ 1985 };

    cout << "Chapter 11, Try this 1" << '\n' << '\n';

    // Birth year
    cout << "I was born in:" << '\n' <<
        "(Decimal)"       << '\t' <<
                                        birth_year << '\n' <<
        "(Hexadecimal)"   << '\t' <<
            hex                         << birth_year << '\n' <<
        "(Octal)"         << '\t' << '\t' <<
            oct                         << birth_year << endl;

    cout << dec;
    cout << '\n';

    // Age
    time_t t{ time(nullptr) };
    tm *const tm_local{ localtime(&t) };
    int year{ 1900 + tm_local->tm_year };
    cout << "The year is now " << year <<
        ", which makes me " << (year - birth_year) <<
        " years old." << endl;

    exit_on_return();
    return 0;
}
