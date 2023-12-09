#include "test_date.h"
#include <string>

void test_leap_year_helper(int year, bool invert) {
	if (!is_leap_year(year) * !invert) {
		std::cout
			<< "Checking if " << year << " is "
			<< (invert ? "NOT" : "indeed") << "a leap year..." << '\n';
		throw std::runtime_error(std::string((invert ? "Did not expect"
		                                             : "Expected"))
		                        + " a leap year");
	}
	std::cout << year << " is " << (invert ? "NOT" : "indeed")
	          << " a leap year" << '\n';
}


void test_count_leap_years(int start_y, int end_y, int expected) {
	int lyears{ leap_years_from_year_span(start_y, end_y) };
	if (lyears != expected) {
		throw std::runtime_error(
			"Wrong number of years returned when calculating leap years from"
			"year " + std::to_string(start_y) +
			" to " + std::to_string(end_y) +
			". Expected: " +
			std::to_string(expected) + " leap years,"
			" but got " +
			std::to_string(lyears) + " leap years."
		);
	}
	std::cout << "Test passed, there are " << lyears << " leap years from year "
	          << start_y << " to " << end_y << '\n';
}

void test_count_leap_years_multiple() {
	test_count_leap_years(2000, 2008, 2);
	test_count_leap_years(2000, 2075, 19);
	test_count_leap_years(1935, 1975, 10);
	test_count_leap_years(1755, 1766, 3);
	test_count_leap_years(1757, 1798, 10);
	test_count_leap_years(1998, 2064, 16);
	test_count_leap_years(1692, 1766, 18);
	test_count_leap_years(1909, 1923, 3);
	test_count_leap_years(1930, 2015, 21);
	test_count_leap_years(1901, 1939, 9);
	test_count_leap_years(1702, 2400, 169);
	test_count_leap_years(1928, 2656, 177);
	test_count_leap_years(1727, 1855, 31);
	test_count_leap_years(1826, 2826, 243);
	test_count_leap_years(1706, 2358, 158);
	test_count_leap_years(1827, 2661, 203);
	test_count_leap_years(1859, 1903, 10);
	test_count_leap_years(1799, 2820, 247);
	test_count_leap_years(1783, 2156, 90);
	test_count_leap_years(1966, 2403, 106);
	test_count_leap_years(1860, 1898, 10);
	test_count_leap_years(1711, 2185, 116);
}
