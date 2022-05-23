#include <iostream>
#include <stdexcept>
#include <string>
#include "std_lib_facilities.h"

/*
This drill simply involves getting the sequence of versions of
Date to work. For each version define a Date called today
initialized to June 25, 1978.

Then, define a Date called tomorrow and give it a value by
copying today into it and increasing its day by one using
add_day().

Finally, output today and tomorrow using a << defined as in §9.8

Your check for a valid date may be very simple. Feel free to
ignore leap years. However, don’t accept a month that is not in
the [1,12] range or day of the month that is not in the
[1,31] range. Test each version with at least one invalid date
(e.g., 2004, 13, –5).

3. The version from §9.4.3
*/

namespace ch09_drill_03
{
    class Date {
        int y; // year
        int m; // month
        int d; // day
    public:
        Date(int, int, int); // validate and intitialize
        void add_day(int n);       // increase Date by n days
        int year() const { return y; }
        int month() const { return m; }
        int day() const { return d; }
    };

    // member functions

    Date::Date(int yy, int mm, int dd)
        :y{ yy }, d{ dd }, m{ mm } {
        if (y < 0 || y>3000)
            throw std::invalid_argument("Invalid year value: " + std::to_string(y));
        if (m < 1 || m>12)
            throw std::invalid_argument("Invalid month value " + std::to_string(m));
        if (d < 1 || d>31)
            throw std::invalid_argument("Invalid day value " + std::to_string(d));
    }

    void Date::add_day(int n) {
        d += n;
    }

    // stream operators

    std::ostream& operator << (std::ostream& os, const Date& d) {
        return os << '(' << d.year() << ", "
            << d.month() << ", "
            << d.day() << ')';
    }

    int main()
        try
    {
        // Initialize test dates
        Date today{ 1978, 6, 25 };
        Date tomorrow = today;
        tomorrow.add_day(1);

        std::cout << "Today is: " << today
            << ", Tomorrow is: " << tomorrow << '\n';

        // Test validation
        const int invalid_y = -1;
        const int invalid_m = 13;
        const int invalid_d = 300;

        //Date invalid{ invalid_y, 1, 1 };
        //Date invalid{ 2000, invalid_m, 1 };
        //Date invalid{ 2000, 6, invalid_d };

        return 0;
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        keep_window_open();
        return 1;
    }
}
