#include <iostream>

namespace ch09_chrono {
    enum class Month {
        jan = 1, feb, mar, apr, may, jun, jul,
        aug, sep, oct, nov, dec
    };

    class Date {
    public:
        class Invalid {}; // throw as exception

        Date(int y, Month m, int d); // validate, intialize
        Date();

        // non-modifying
        int day() const { return d; }
        Month month() const { return m; }
        int year() const { return y; }

        // modifying
        void add_day(int n);
        void add_month(int n);
        void add_year(int n);
    private:
        int y;
        Month m;
        int d;
    };

    // helper functions
    bool is_date(int y, Month m, int d); // validate
    bool is_leap_year(int y);

    // Date operator overloads
    bool operator==(const Date& a, const Date& b);
    bool operator!=(const Date& a, const Date& b);

    // iostream Date operator overloads
    std::ostream& operator<<(std::ostream& os,
                             const Date& date);
    std::istream& operator>>(std::istream& is, Date& date);
}                   // END Chrono