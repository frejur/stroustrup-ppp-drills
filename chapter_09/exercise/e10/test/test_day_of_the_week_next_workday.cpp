#include "test_date.h"
#include <string>

void test_dotw(const Date& d, const Day_of_the_week expected) {
	Day_of_the_week dotw{ d.day_of_the_week() };

	if (dotw != expected) {
		throw std::runtime_error(
			"Wrong day-of-the-week for date: " +
			std::to_string(d.year()) + ", " +
			std::to_string(static_cast<int>(d.month())) + ", " +
			std::to_string(d.day()) +
			". Expected: " + dotw_to_str(expected) +
			" but got " + dotw_to_str(dotw)
		);
	}
	std::cout << "Test passed, the day-of-the-week for date " << d
	          << " is: " << dotw_to_str(expected) << '\n';
}

void test_workday(const Date& d, const Date& expected) {
	Date wday{ next_workday(d) };

	if (wday != expected) {
		throw std::runtime_error(
			"Wrong next workday for date: " +
			std::to_string(d.year()) + ", " +
			std::to_string(static_cast<int>(d.month())) + ", " +
			std::to_string(d.day()) +
			". Expected: " +
			std::to_string(expected.year()) + ", " +
			std::to_string(static_cast<int>(expected.month())) + ", " +
			std::to_string(expected.day()) +
			" but got " +
			std::to_string(wday.year()) + ", " +
			std::to_string(static_cast<int>(wday.month())) + ", " +
			std::to_string(wday.day())
		);
	}
	std::cout << "Test passed, the next workday for date " << d
	          << " is: " << expected << '\n';
}

void test_dotw_multiple() {
	test_dotw({ 2023, Month::dec, 8 }, Day_of_the_week::fri);
	test_dotw({ 2680, Month::may, 30 }, Day_of_the_week::sun);
	test_dotw({ 1602, Month::nov, 22 }, Day_of_the_week::fri);
	test_dotw({ 2408, Month::dec, 22 }, Day_of_the_week::mon);
	test_dotw({ 1881, Month::sep, 10 }, Day_of_the_week::sat);
	test_dotw({ 1607, Month::jul, 23 }, Day_of_the_week::mon);
	test_dotw({ 1641, Month::jun, 17 }, Day_of_the_week::mon);
	test_dotw({ 2543, Month::mar, 24 }, Day_of_the_week::sun);
	test_dotw({ 2334, Month::sep,  7 }, Day_of_the_week::fri);
	test_dotw({ 1927, Month::may, 21 }, Day_of_the_week::sat);
	test_dotw({ 2531, Month::may, 12 }, Day_of_the_week::sat);
	test_dotw({ 2141, Month::feb, 17 }, Day_of_the_week::fri);
	test_dotw({ 2886, Month::apr, 17 }, Day_of_the_week::wed);
	test_dotw({ 2544, Month::oct, 23 }, Day_of_the_week::fri);
	test_dotw({ 2996, Month::jul, 22 }, Day_of_the_week::fri);
	test_dotw({ 2612, Month::sep,  7 }, Day_of_the_week::mon);
	test_dotw({ 2220, Month::mar, 25 }, Day_of_the_week::sat);
	test_dotw({ 1865, Month::jan, 14 }, Day_of_the_week::sat);
	test_dotw({ 1603, Month::dec, 26 }, Day_of_the_week::fri);
	test_dotw({ 2037, Month::jun,  7 }, Day_of_the_week::sun);
	test_dotw({ 2835, Month::feb,  6 }, Day_of_the_week::tue);
	test_dotw({ 2376, Month::nov, 23 }, Day_of_the_week::tue);
	test_dotw({ 1620, Month::may,  2 }, Day_of_the_week::sat);
	test_dotw({ 1900, Month::jan,  1 }, Day_of_the_week::mon);
}

void test_workday_multiple() {
	test_workday({ 2408, Month::dec, 22 }, { 2408, Month::dec, 23 });
	test_workday({ 2408, Month::dec, 22 }, { 2408, Month::dec, 23 });
	test_workday({ 2835, Month::feb,  6 }, { 2835, Month::feb,  7 });
	test_workday({ 1641, Month::jun, 19 }, { 1641, Month::jun, 20 });
	test_workday({ 2334, Month::sep,  6 }, { 2334, Month::sep,  7 });
	test_workday({ 2023, Month::dec,  8 }, { 2023, Month::dec, 11 });
	test_workday({ 1881, Month::sep, 10 }, { 1881, Month::sep, 12 });
	test_workday({ 2680, Month::may, 30 }, { 2680, Month::may, 31 });
}

