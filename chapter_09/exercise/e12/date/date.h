#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <vector>

namespace CHRONO { // ----------------------------------------------------------

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul,
	aug, sep, oct, nov, dec
};

enum class Day_of_the_week {
	mon = 1, tue, wed, thu, fri, sat, sun
};

const std::vector<std::string>& MONTH_NAMES();
const std::vector<std::string>& DOTW_NAMES();

class Date {
public:
	Date(int y, Month m, int d); // validate, initialize
	Date();

	// non-modifying
	int day() const { return d; }
	Month month() const { return m; }
	int year() const { return y; }
	Day_of_the_week day_of_the_week() const;

	// modifying
	void add_days(const int n);
	void add_months(const int n);
	void add_years(const int n);
private:
	int y;
	Month m;
	int d;
};

// helper functions
bool is_date(const int y, const Month m, const int d); // validate
bool is_leap_year(const int y);
int days_in_month(const int year, const Month month);
bool is_before_date(int y1, Month m1, int d1, int y2, Month m2, int d2);
bool is_before_min_date(int y, Month m, int d);
int days_from_sofm_until_sofm(int y, Month m1, Month m2);
int days_from_sofy_until_sofm(int y, Month m);
int days_from_sofm_until_eofy(int y, Month m);
int leap_years_from_year_span(int start_y, int end_y);
int duration_in_days(const Date& start, const Date& end);
std::string dotw_to_str(const Day_of_the_week dotw);
Date next_workday(const Date& date);
int weeks_per_year(const int year);
int week_of_year(const Date& date);

// Date operator overloads
bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

// iostream Date operator overloads
std::ostream& operator<<(std::ostream& os,
						 const Date& date);
std::istream& operator>>(std::istream& is, Date& date);

std::ostream& operator<<(std::ostream& os,
						 const Month date);

std::ostream& operator<<(std::ostream& os,
						 const Day_of_the_week dotw);

} // namespace CHRONO ----------------------------------------------------------

#endif // DATE_H
