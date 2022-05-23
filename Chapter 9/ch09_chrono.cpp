#include "ch09_chrono.h"
#include "std_lib_facilities.h"

namespace ch09_chrono {


    // Date constructors and member functions ------------------
    Date::Date(int yy, Month mm, int dd)
        : y{ yy }, m{ mm }, d{ dd }
    {
        if (!is_date(yy, mm, dd)) throw Invalid{};
    }

    const Date& default_date()
    {
        static Date dd{ 2001, Month::jan, 1 };
        return dd;
    }

    Date::Date()
        :y{ default_date().year() },
        m{ default_date().month() },
        d{ default_date().day() }
    {}

    void Date::add_day(int n)
    {
        // ...
    }

    void Date::add_month(int n)
    {
        // ...
    }

    void Date::add_year(int n)
    {
        if (m == Month::feb && d == 29 && !is_leap_year(y + n))
        {
            m = Month::mar;
            d = 1;
        }
        y += n;
    }

    // helper functions ----------------------------------------

    bool is_date(int y, Month m, int d)
    {
        // assumes valid year

        if (d <= 0) return false;
        if (m < Month::jan || Month::dec < m) return false;

        int month_days;
        switch (m) {
        case Month::feb:
            month_days = (is_leap_year(y)) ? 29 : 28;
            break;
        case Month::apr: case Month::jun:
        case Month::sep: case Month::nov:
            month_days = 30;
            break;
        default:
            month_days = 31;
        }

        return (month_days >= d);
    }

    bool is_leap_year(int y) {
        // leap year if multiple of 4
        return	!(y % 4) &&
            // EXCEPT mult. of 100 but not exactly div. by 400
            (y % 100 || !(y % 400));
    }

    // Date operator overloads ---------------------------------

    bool operator==(const Date& a, const Date& b)
    {
        return a.year() == b.year() &&
               a.month() == b.month() &&
               a.year() == b.year();
    }

    bool operator!=(const Date& a, const Date& b)
    {
        return !(a == b);
    }

    // iostream Date operator overloads ------------------------

    ostream& operator<<(ostream& os, const Date& date)
    {
        return os << '(' << date.year()
                  << ',' << static_cast<int>(date.month())
                  << ',' << date.day() << ')';
    }

    istream& operator>>(istream& is, Date& date)
    {
        int y, m, d;
        char ch1, ch2, ch3, ch4;

        is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
        if (!is) return is;

        if (ch1 != '(' ||
            ch2 != ',' || ch3 != ',' ||
            ch4 != ')')
        {
            // format error fail
            is.clear(ios_base::failbit);
            return is;
        }

        date = Date(y, Month(m), d); // update Date object

        return is;
    }
    int main() {
        try {
            Date test_a = Date(1985,Month(4),11);
            cout << test_a << endl;
            cout << "Enter some dates to test:" << endl;
            Date test;
            while (cin >> test)
                cout << test << '\n';
            keep_window_open();
            return 0;
        }
        catch (...) {
            cerr << "Error";
            keep_window_open();
            return 1;
        }
    }
}
