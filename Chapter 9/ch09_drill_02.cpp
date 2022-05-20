#include <iostream>
#include <stdexcept>
#include <string>

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

2. The version from §9.4.2
*/

namespace ch09_drill_02
{
    struct Date {
        int y; // year
        int m; // month
        int d; // day
        Date(int y, int m, int d); // validate and intitialize
        void add_day(int n);       // increase Date by n days
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
        y = y; m = m; d = d;
    }

    void Date::add_day(int n) {
        d += n;
    }

    // stream operators

    std::ostream& operator << (std::ostream& os, const Date& d) {
        return os << '(' << d.y << ", "
            << d.m << ", "
            << d.d << ')';
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
    }
}