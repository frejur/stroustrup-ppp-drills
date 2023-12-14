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

// The 1st of Jan 1601 is the "epoch" of this Date class.
// This coincides with the adoptation of the Gregorian calendar in some parts
// of the world...
const std::vector<int>& min_date_vals() {
	static std::vector<int> v{ 1601, 1, 1 };
	return v;
}

const Day_of_the_week& min_dotw() {
	static Day_of_the_week dotw{ Day_of_the_week::mon }; // NOTE: 1st Jan 1601
	return dotw;
}

static constexpr int weeks_per_year_before_min_date{ 52 }; // NOTE: 1st Jan 1601

// -----------------------------------------------------------------------------

bool is_before_date(int y1, Month m1, int d1, int y2, Month m2, int d2) {
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

	return is_before_date(y, m, d, min_y, min_m, min_d);
}

// -----------------------------------------------------------------------------
// Returns the number of days from (and including) the start of the given month
// and year, until the start of the other given month of the same year.
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
	if (m1 <= Month::feb && m2 > Month::feb && is_leap_year(y)) {
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

// Returns the number of leap years contained in the given span of years.
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
	if (is_before_date(end.year(), end.month(), end.day(),
	                   start.year(), start.month(), start.day())
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
			days += days_from_sofm_until_sofm(start.year(), start.month(),
			                                  end.month())
			        - start.day() + end.day();
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

std::ostream& operator<<(std::ostream& os, const DDATE::Date& month)
{
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

// Add days (This is a NOT very elegant and "brute force" way of doing it)
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
// -----------------------------------------------------------------------------

Day_of_the_week Date::day_of_the_week() const {
	return static_cast<Day_of_the_week>(
		static_cast<int>(min_dotw()) +
		(duration_in_days({ min_date_vals()[0],
		                   static_cast<Month>(min_date_vals()[1]),
		                   min_date_vals()[2] }, {y, m, d})
		 % 7)
	);
}

std::string dotw_to_str(const Day_of_the_week dotw) {
	using DOTW = Day_of_the_week;
	switch (dotw) {
	case DOTW::mon:
		return "Monday";
		break;
	case DOTW::tue:
		return "Tuesday";
		break;
	case DOTW::wed:
		return "Wednesday";
		break;
	case DOTW:: thu:
		return "Thursday";
		break;
	case DOTW::fri:
		return "Friday";
		break;
	case DOTW::sat:
		return "Saturday";
		break;
	case DOTW::sun:
		return "Sunday";
		break;
	default:
		break;
	}
	return "";
}

Date next_workday(const Date& date) {
	int dotw{ static_cast<int>(date.day_of_the_week()) };
	int add_d{ 1 };
	if (dotw > 4) {
		add_d += (7 - dotw);
	}
	Date new_date{ date };
	new_date.add_days(add_d);
	return new_date;
}

// ISO number of weeks per year
// Returns 52 (Short) or 53 (Long)
//
// "The long years, with 53 weeks in them, can be described by any of the
// following equivalent definitions:
// (...)<Confusing set of conditions>(...)"
// Source: https://en.wikipedia.org/wiki/ISO_week_date)
//
// I interpreted the set of conditions as follows:
//  1. Any year (Leap or common) where Jan 1 is a Thursday
//  2. Any year (Leap or common) where Dec 31 is a Thursday
//  3. Any leap year where Jan 1 is a Wednesday
//  4. Any leap year where Dec 31 is a Friday
int weeks_per_year(const int year) {
	if (year < min_date_vals()[0] - 1) {
		throw std::runtime_error("Cannot calculate weeks per year for any year"
		                         "less than the year before the minimum date"
								 "year");
	}
	if (year == min_date_vals()[0] - 1) {
		return weeks_per_year_before_min_date;
	}

	using DOTW = Day_of_the_week;
	Date jan_1{ year, Month::jan, 1};
	DOTW dotw_start{ jan_1.day_of_the_week() };
	if (dotw_start == DOTW::thu) {
		return 53;
	}

	bool is_leap{ is_leap_year(year) };
	if (is_leap && dotw_start == DOTW::wed) {
		return 53;
	}

	DOTW dotw_end{ static_cast<DOTW>(
	                   (static_cast<int>(dotw_start) +
	                       ( (is_leap ? 365 : 364) % 7 )
	                   ) % 7
	               ) };
	if (dotw_end == DOTW::thu ||
	   (is_leap && dotw_end == DOTW::fri)
	) {
		return 53;
	}

	return 52;
}

// Definition of an ISO week-number:
// Each year has 52 to 53 full weeks (1 to 53, Monday to Sunday).
// The first week starts on the Monday closest to the start of the year:
// > When Jan 1st is a Monday, that's also the first day of the first week.
// > When Jan 1st is a Tuesday, Wednesday or Thursday, the first week
//   starts in December of the previous year, shifted X number of days BACK.
//   So the FIRST week will contain days from BOTH years.
// > Similarly, when Jan 1st is a Friday, Saturday or Sunday, the first week
//   starts in January, shifted X days FORWARD.
//   This means that the LAST week of the previous year will contain days
//   from BOTH years.

int week_of_year(const Date& date) {
	Date first_mon{ date.year(), Month::jan, 1 };
	int dotw{ static_cast<int>(first_mon.day_of_the_week()) - 1 };
	int num_weeks{ weeks_per_year(date.year()) };
	if (dotw > 3) { // Past thursday
		if (dotw > 0) {
			first_mon.add_days(7 - dotw);
			if (is_before_date(date.year(), date.month(), date.day(),
			                   first_mon.year(), first_mon.month(),
			                   first_mon.day())
			) {
				if (num_weeks == 53) {
					return 52; // a "long" iso year is always preceded by a
					           // short one
				}
				return weeks_per_year(date.year() - 1);
			}
		}
	} else if (dotw != 0) {
		first_mon = {date.year() - 1, Month::dec, 31 - dotw + 1 };
	}

	return duration_in_days(first_mon, date) / 7 + 1;
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
