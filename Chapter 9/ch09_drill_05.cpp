#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
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

5. The version from §9.7.4
*/

namespace ch09_drill_05
{
    enum class Month {
        jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

    class Date {
        int y;   // year
        Month m; // month
        int d;   // day
    public:
        Date();
        Date(int y, Month m, int d); // validate and intitialize
        void add_day(int n);       // increase Date by n days
        int year() const { return y; }
        Month month() const { return m; }
        int day() const { return d; }
    };

    const Date& default_date() {
        static Date dd{ 2001, Month::jan, 1 };
        return dd;
    }

    Date::Date()
        :y{ default_date().year() },
        m{ default_date().month() },
        d{ default_date().day() }
    {}

    // member functions

    Date::Date(int yy, Month mm, int dd)
        :y{ yy }, m{ mm }, d{ dd } {
        if (y < 0 || y>3000)
            throw std::invalid_argument("Invalid year value: " + std::to_string(y));
        if (d < 1 || d>31)
            throw std::invalid_argument("Invalid day value " + std::to_string(d));
    }

    void Date::add_day(int n) {
        d += n;
    }

    // stream operators

    std::ostream& operator << (std::ostream& os, const Date& d) {
        return os << '(' << d.year() << ", "
            << int(d.month()) << ", "
            << d.day() << ')';
    }

    int main()
        try
    {
        // Initialize test dates
        Date today{ 1978, Month::jun, 25 };
        Date tomorrow = today;
        tomorrow.add_day(1);

        std::cout << "Today is: " << today
            << ", Tomorrow is: " << tomorrow << '\n';

        Date default_d;
        std::cout << "Default date: " << default_d << '\n';

        std::cout << "Vector of 10 default dates:" << '\n';
        Vector<Date> dates(10);
        for (Date d : dates) std::cout << " - " << default_d << '\n';

        // Test validation
        const int invalid_y = -1;
        const int invalid_m = 13;
        const int invalid_d = 300;

        //Date invalid{ invalid_y, Month::jun, 1 };
        //Date invalid{ 2000, invalid_m, 1 };
        //Date invalid{ 2000, Month::jun, invalid_d };

        return 0;
    }
    catch (const std::invalid_argument& ia) {
        std::cerr << "Invalid argument: " << ia.what() << '\n';
        keep_window_open();
        return 1;
    }
}
