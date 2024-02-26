#ifndef READING_H
#define READING_H

#include <iostream>
#include <string>
#include <vector>

namespace tmpr {

const inline std::string month_marker()
{
	static std::string s{"month"};
	return s;
}
const inline std::string year_marker()
{
	static std::string s{"year"};
	return s;
}
const inline std::string indent()
{
	static std::string s{"  "};
	return s;
}
constexpr char symbol_temperature{'C'};
constexpr char symbol_degree{'\370'};

constexpr int min_year{1960};
constexpr int max_year{2050};
constexpr int implausible_min_temp{-200};
constexpr int implausible_max_temp{200};
constexpr double not_a_reading{-77777};
constexpr int not_a_month{-1};
constexpr int not_a_year{min_year - 1};

const inline std::vector<std::string> input_table_months()
{
	static std::vector<std::string> v{"jan",
	                                  "feb",
	                                  "mar",
	                                  "apr",
	                                  "may",
	                                  "jun",
	                                  "jul",
	                                  "aug",
	                                  "sep",
	                                  "oct",
	                                  "nov",
	                                  "dec"};
	return v;
}

const inline std::vector<std::string> input_table_months_full()
{
	static std::vector<std::string> v{"January",
	                                  "February",
	                                  "March",
	                                  "April",
	                                  "May",
	                                  "June",
	                                  "July",
	                                  "August",
	                                  "September",
	                                  "October",
	                                  "November",
	                                  "December"};
	return v;
}

inline std::string formatted_month(const int m_num)
{
	if (0 > m_num || m_num > 11) {
		throw std::runtime_error("Invalid month number");
	}
	return input_table_months_full()[m_num];
}
std::string formatted_temperature(double t);
std::string formatted_day(int y, int m, int d);
std::string formatted_time(int hour);

void end_of_loop(std::istream& is, char term, const std::string& message);

//------------------------------------------------------------------------------
struct Reading
{
	int day;
	int hour;
	double temperature;
};

inline bool is_valid_year(const int y)
{
	return (min_year < y || y > max_year);
}

inline bool is_valid(const Reading& r)
{
	if ((1 > r.day || r.day > 31) || (0 > r.hour || r.hour > 23)
	    || r.temperature < implausible_min_temp
	    || r.temperature > implausible_max_temp) {
		return false;
	}
	return true;
}

std::istream& operator>>(std::istream& is, Reading& r);
std::ostream& operator<<(std::ostream& os, const Reading& r);

bool operator==(const Reading& a, const Reading& b);
bool operator!=(const Reading& a, const Reading& b);

//------------------------------------------------------------------------------
struct Day
{
	std::vector<double> hour{
	    std::vector<double>(24, not_a_reading)}; // 0-indexed
};

bool days_are_eq(const Day& a, const Day& b, bool debug = false);

bool operator==(const Day& a, const Day& b);
bool operator!=(const Day& a, const Day& b);

//------------------------------------------------------------------------------
struct Month
{
	int month{not_a_month};
	std::vector<Day> day{32}; // 1-indexed
};

inline int month_to_int(const std::string& m)
{
	for (int i = 0; i < 12; ++i) {
		if (input_table_months()[i] == m) {
			return i;
		}
	}
	return not_a_month;
}

inline std::string int_to_month(const int m_num)
{
	if (0 > m_num || m_num > 11) {
		throw std::runtime_error("Invalid month number");
	}
	return input_table_months()[m_num];
}

std::istream& operator>>(std::istream& is, Month& r);
std::ostream& operator<<(std::ostream& os, const Month& r);

bool months_are_eq(const Month& a, const Month& b, bool debug = false);

bool operator==(const Month& a, const Month& b);
bool operator!=(const Month& a, const Month& b);

void print_month(std::ostream& os, const Month& m, int y);
void print_day(std::ostream& os, const Month& m, int y, int d);

struct Year_month
{
	int year;
	Month month;
};

//------------------------------------------------------------------------------
struct Year
{
	int year;
	std::vector<Month> month{12}; // 0 == January
};

std::istream& operator>>(std::istream& is, Year& y);
std::ostream& operator<<(std::ostream& os, const Year& y);

bool years_are_eq(const Year& a, const Year& b, bool debug = false);

bool operator==(const Year& a, const Year& b);
bool operator!=(const Year& a, const Year& b);

void print_year(std::ostream& os, const Year& y);

} // namespace tmpr

#endif // READING_H
