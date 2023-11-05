#include <iostream>
#include <stdexcept>
#include <string>
#include "../../lib/std_lib_facilities.h"

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

4. The version from §9.7.1
*/

enum class Month {
	jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Year {
	static const int min = 0;
	static const int max = 3000;
public:
	class Invalid { };
	explicit Year(int yy) : y{ yy } {
		if (yy < min || max <= yy)
			throw std::invalid_argument("Invalid year value " + std::to_string(y));
	}
	int year() const { return y; }
private:
	int y;
};

class Date {
	Year y;  // year
	Month m; // month
	int d;   // day
public:
	Date(Year y, Month m, int d); // validate and intitialize
	void add_day(int n);          // increase Date by n days
	int year() const { return y.year(); }
	Month month() const { return m; }
	int day() const { return d; }
};

// member functions

Date::Date(Year yy, Month mm, int dd)
	:y{ yy }, m{ mm }, d{ dd } {
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

	// Error: the explicit keyword in the declaration
	// of Year's constructor prevents the implicit
	// conversion of integer literal to Year object
	//Date today{ 1978, Month::jun, 25 };

	Date today{ Year{1978}, Month::jun, 25 };
	Date tomorrow = today;
	tomorrow.add_day(1);

	std::cout << "Today is: " << today
		<< ", Tomorrow is: " << tomorrow << '\n';

	// Test validation
	const Year invalid_y{ -1 };
	const int invalid_m = 13;
	const int invalid_d = 300;

	Date invalid{ invalid_y, Month::jun, 1 };
	//Date invalid{ 2000, invalid_m, 1 };
	//Date invalid{ 2000, Month::jun, invalid_d };

	keep_window_open();

	return 0;
}
catch (const std::invalid_argument& ia) {
	std::cerr << "Invalid argument: " << ia.what() << '\n';
	keep_window_open();
	return 1;
}
