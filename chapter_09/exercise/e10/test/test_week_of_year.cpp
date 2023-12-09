#include "test_date.h"
#include <string>

void test_wofyear(const Date& date, int expected) {
	int w{ week_of_year(date) };
	if (w != expected) {
		throw std::runtime_error(
			"Wrong ISO week number for : " +
			std::to_string(date.year()) + ", " +
			std::to_string(static_cast<int>(date.month())) + ", " +
			std::to_string(date.day()) +
			". Expected: " + std::to_string(expected) +
			" but got " + std::to_string(w)
		);
	}
	std::cout << "Test passed, date " << date
	          << " is in ISO week " << expected << " of year " << date.year()
	          << "." << '\n';
}

void test_wofyear_multiple() {
	test_wofyear({ 2021, Month::jun,  6 }, 22);
	test_wofyear({ 2021, Month::nov, 15 }, 46);
	test_wofyear({ 2691, Month::sep, 22 }, 39);
	test_wofyear({ 2571, Month::nov, 21 }, 47);
	test_wofyear({ 2401, Month::may, 30 }, 22);
	test_wofyear({ 2851, Month::jan, 31 }, 5);
	test_wofyear({ 1936, Month::nov, 25 }, 48);
	test_wofyear({ 1801, Month::feb, 10 }, 7);
	test_wofyear({ 2671, Month::jul, 30 }, 30);
	test_wofyear({ 1804, Month::jan, 19 }, 3);
	test_wofyear({ 1868, Month::oct, 21 }, 43);
	test_wofyear({ 1858, Month::oct,  8 }, 40);
	test_wofyear({ 2397, Month::sep, 27 }, 39);
	test_wofyear({ 2525, Month::jul, 14 }, 28);
	test_wofyear({ 2594, Month::may, 14 }, 20);
	test_wofyear({ 2810, Month::oct,  9 }, 40);
	test_wofyear({ 1872, Month::mar, 22 }, 12);
	test_wofyear({ 1989, Month::jul,  4 }, 27);
	test_wofyear({ 1721, Month::aug, 29 }, 35);
	test_wofyear({ 1937, Month::nov, 15 }, 46);
	test_wofyear({ 1651, Month::jun, 27 }, 26);
	test_wofyear({ 2552, Month::may, 28 }, 21);
	test_wofyear({ 1963, Month::aug, 10 }, 32);
	test_wofyear({ 2957, Month::sep,  5 }, 36);
	test_wofyear({ 1900, Month::jan,  1 }, 1);
}
