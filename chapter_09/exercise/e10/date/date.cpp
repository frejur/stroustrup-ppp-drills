#include "date.h"
#include <stdexcept>
#include <vector>

// helper functions ----------------------------------------

const std::vector<int>& month_days() {
	static std::vector<int> d{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return d;
}

int days_in_month(const int y, const Month m) {
	int days = month_days().at(static_cast<int>(m) - 1);
	if (m == Month::feb && is_leap_year(y)) {
		days ++;
	}
	return days;
}

// -----------------------------------------------------------------------------

const std::vector<int>& min_date_vals() {
	static std::vector<int> v{ 1601, 1, 1 };
	return v;
}

const Day_of_the_week& min_dotw() {
	static Day_of_the_week dotw{ Day_of_the_week::mon };
	return dotw;
}

// -----------------------------------------------------------------------------

bool date_is_before_date(int y1, Month m1, int d1, int y2, Month m2, int d2) {
	return (
		   (y1 < y2)
		|| (y1 == y2 && static_cast<int>(m1) < static_cast<int>(m2))
		|| (y1 == y2 && static_cast<int>(m1) == static_cast<int>(m2)
		    && d1 < d2)
	);
}

bool is_before_min_date(int y, Month m, int d) {
	int min_y{ min_date_vals()[0] };
	Month min_m{ static_cast<Month>(min_date_vals()[1]) };
	int min_d{ min_date_vals()[2] };

	return date_is_before_date(y, m, d, min_y, min_m, min_d);
}

// -----------------------------------------------------------------------------
// Returns the number of days from (and including) the start of the given month
//  and year, until the start of the other given month of the same year.
int days_from_sofm_until_sofm(int y, Month m1, Month m2) {
	if (m2 < m1) {
		throw std::runtime_error("Cannot calculate the number of days between"
		                         "two months when the second month occurs "
		                         "before the first month.");
	}
	int d{ 0 };
	if (m1 == m2) {
		return d;
	}
	int m1_i { static_cast<int>(m1) };
	int m2_i { static_cast<int>(m2) };
	for (int i = m1_i; i < m2_i; i++) {
		d += month_days()[i-1];
	}
	if (m2 > Month::feb && is_leap_year(y)) {
		++d;
	}

	return d;
}
// Returns the number of days from (and including) the start of the given year,
// until the start of the given month of the same year.
int days_from_sofy_until_sofm(int y, Month m) {
	return days_from_sofm_until_sofm(y, Month::jan, m);
}

// Returns the number of days from (and including) the start of the given month
// of the given year, until the end of the same year.
int days_from_sofm_until_eofy(int y, Month m) {
	int d{ 0 };
	int mi { static_cast<int>(m) };
	for (int i = mi; i <= 12; i++) {
		d += month_days()[i-1];
	}
	if (m <= Month::feb && is_leap_year(y)) {
		++d;
	}

	return d;
}

// Returns the number of leap years contained in the give span of years.
// The start year is included, the end year is not, e.g.:
//     2000 to 2008 has 2 leap years
int leap_years_from_year_span(int start_y, int end_y)
{
	--start_y; // include start year
	--end_y;   // exclude end year

	return (end_y / 4 - start_y / 4)
	     - (end_y / 100 - start_y / 100)
	     + (end_y / 400 - start_y / 400);
}

int duration_in_days(const Date& start, const Date& end) {
	if (!date_is_before_date(start.year(), start.month(), start.day(),
	                        end.year(), end.month(), end.day())
	) {
		throw std::runtime_error("Cannot calculate duration, the end date "
		                         "occurs before the start date");
	}
	if (start == end) {
		return 0;
	}

	int days{ 0 };
	int y_diff{ end.year() - start.year() };
	int m_diff{ static_cast<int>(end.month()) -
	            static_cast<int>(start.month()) };
	int d_diff{ end.day() - start.day() };
	if (y_diff) {
		days += days_from_sofm_until_eofy(start.year(), start.month()) -
		        start.day();
		// note that we are now at "start year + 1"
		if (y_diff > 1) {
			days += 365 * (y_diff-1) +
					leap_years_from_year_span(start.year() + 1, end.year());
		}
		days += days_from_sofy_until_sofm(end.year(), end.month()) +
		        end.day();
	} else {
		if (m_diff) {
			days = (is_leap_year(end.year()) ? 366 : 365) -
			       (( days_from_sofy_until_sofm(end.year(), end.month()) +
			          end.day() ) -
			        ( days_from_sofm_until_eofy(start.year(), start.month()) -
			         start.day() )
			       );
		} else {
			days = d_diff;
		}
	}
	return days;
}

// -----------------------------------------------------------------------------
bool is_date(const int y, const Month m, const int d)
{
	if (is_before_min_date(y, m, d)) {
		return false;
	}

	if (d <= 0) return false;
	if (m < Month::jan || Month::dec < m) return false;

	int mdays = days_in_month(y, m);
	return (mdays >= d);
}

bool is_leap_year(const int y) {
	// leap year if multiple of 4
	return	!(y % 4) &&
		// if it is also NOT a mult. of 100,
		// or if it is also exactly div. by 400
		(y % 100 || !(y % 400));
}
// -----------------------------------------------------------------------------

Date::Date(int yy, Month mm, int dd)
	: y{ yy }, m{ mm }, d{ dd }
{
	if (!is_date(yy, mm, dd)) throw std::runtime_error("Invalid date");
}

std::ostream& operator<<(std::ostream& os, const Month month) {
	os << static_cast<int>(month);
	return os;
}

const Date& default_date()
{
	static Date dd{ 2001, Month::jan, 1 };
	return dd;
}

// -----------------------------------------------------------------------------

Date::Date()
	:y{ default_date().year() },
	m{ default_date().month() },
	d{ default_date().day() }
{}

void Date::add_days(const int n)
{
	int days { n };
	int dd{ d };
	Month mm{ m };
	int yy{ y };
	while (days > 0) {
		int mdays{ days_in_month(yy, mm) - dd };
		if (days <= mdays) {
			dd += days;
			days = 0;
		} else {
			if (mm == Month::dec) {
				mm = Month::jan;
				++yy;
			} else {
				mm = static_cast<Month>(static_cast<int>(mm) + 1);
			}
			dd = 1;
			days -= mdays + 1;
		}
	}
	if (!is_date(yy, mm, dd)) {
		throw std::runtime_error("Adding the given number of days produces an"
								 " invalid date");
	}
	y = yy;
	m = mm;
	d = dd;
}

void Date::add_months(const int n)
{
	int months{ n };
	int mm{ static_cast<int>(m) };
	int yy{ y };
	while (months > 0) {
		int ymonths{ 12 - mm };
		if (months <= ymonths) {
			mm += months;
			months = 0;
		} else {
			++yy;
			mm = 1;
			months -= ymonths + 1;
		}
	}
	Month month{ static_cast<Month>(mm) };
	int mdays{ days_in_month(yy, month) };
	int day{ d };
	if (day > mdays) {
		day = mdays;
	}
	if (!is_date(yy, month, day)) {
		throw std::runtime_error("Adding the given number of days produces an"
								 " invalid date");
	}
	y = yy;
	m = month;
	d = day;
}

void Date::add_years(const int n)
{
	if (m == Month::feb && d == 29 && !is_leap_year(y + n))
	{
		m = Month::mar;
		d = 1;
	}
	y += n;
}

// Date operator overloads ---------------------------------

bool operator==(const Date& a, const Date& b)
{
	return a.year() == b.year() &&
		   a.month() == b.month() &&
		   a.day() == b.day();
}

bool operator!=(const Date& a, const Date& b)
{
	return !(operator==(a, b));
}

// iostream Date operator overloads ------------------------

std::ostream& operator<<(std::ostream& os, const Date& date)
{
	return os << '(' << date.year()
			  << ',' << static_cast<int>(date.month())
			  << ',' << date.day() << ')';
}

std::istream& operator>>(std::istream& is, Date& date)
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
		is.clear(std::ios_base::failbit);
		return is;
	}

	date = Date(y, Month(m), d); // update Date object

	return is;
}
