/* Chapter 9, Exercise 12, Date as days since Jan 1st 1970
 *
 * Re-implement the Date class described in section 9.8 of the book, but with
 * the date represented as the number of days passed since January 1st 1970.
 *
 * Use <long int> to store the number of days.
 *
 * Catch negative numbers and long int overflow.
 *
 * The Date class implemented in the prev. exercise is used for testing.
 * The "new" Date class in this chapter uses namespace DDATE.
 * The "old" one uses namespace CHRONO.
 */

#include "../../lib/help.h"
#include "date/date.h"
#include "ddate/ddate.h"
#include "lib/istr.h"
#include "lib/pad.h"
#include <exception>
#include <iostream>

namespace CONST {
	const std::string PROMPT{ "> " };
	const std::string EXIT{ "exit" };
}

// Used for passing along data
struct Simple_date
{
	int year;
	int month;
	int day;
};

std::string month_name(Simple_date d) {
	return DDATE::MONTH_NAMES()[d.month-1];
}

bool operator==(DDATE::Date& a, const CHRONO::Date& b) {
	using DOTW = DDATE::Day_of_the_week;
	return (
		   a.year() == b.year()
		&& a.month() == static_cast<DDATE::Month>(b.month())
		&& a.day() == b.day()
		&& a.day_of_the_week() == static_cast<DOTW>(b.day_of_the_week())
	);
}

bool operator!=(DDATE::Date& a, const CHRONO::Date& b) {
	return !operator==(a, b);
}

// -----------------------------------------------------------------------------

void print_results(DDATE::Date& a, CHRONO::Date& b, Simple_date epoch) {
	DDATE::Date sunday{ next_sunday(a) };
	DDATE::Date wday( next_weekday(a) );
	auto a_dotw = a.day_of_the_week();
	auto b_dotw = b.day_of_the_week();
	std::string ep_m{ month_name(epoch) };
	std::cout
		<< "  " << a.days_since_epoch()
		<< " day(s) since "
		<< ep_m << " " << epoch.day << " " << epoch.year << '\n'
		<< '\n'
		<< pad("", 10)       << pad("A", 11)       << "  " << pad("B", 11)
			<< "TEST" << '\n'
		<< "-----------------------------------------" << '\n'
		<< pad("Year:", 10)  << pad(a.year(), 11)  << "  " << pad(b.year(), 11)
			<< (a.year() == b.year() ? "Passed" : "Failed") << '\n'
		<< pad("Month:", 10) << pad(a.month(), 11) << "  " << pad(b.month(), 11)
			<< (a.month() == static_cast<DDATE::Month>(b.month())
			    ? "Passed"
			    : "Failed") << '\n'
		<< pad("Day:", 10)   << pad(a.day(), 11)   << "  " << pad(b.day(), 11)
			<< (a.day() == b.day() ? "Passed" : "Failed") << '\n'
		<< pad("", 10)       << pad(a_dotw, 11)    << "  " << pad(b_dotw, 11)
			<< (a_dotw == static_cast<DDATE::Day_of_the_week>(b_dotw)
			    ? "Passed"
			    : "Failed") << '\n'
		<< '\n'
		<< "Next Sunday:  " << sunday << '\n'
		<< "Next weekday: " << wday << '\n'
		<< '\n';
}

// -----------------------------------------------------------------------------

void test_add_months(DDATE::Date& a, CHRONO::Date& b,
                     const std::vector<int>& test_m)
{
	for (int months : test_m) {
		DDATE::Date a2{ a.days_since_epoch() };
		CHRONO::Date b2{ b.year(), b.month(), b.day() };
		a2.add_months(months);
		b2.add_months(months);
		std::cout << "Adding " << pad(months, 8, true) << " months..."
		<< pad((a2 == b2 ? "Passed" : "Failed"), 15, true)
		<< '\n';
		if (a2 != b2) {
			std::cout << "A: " << a2 << " is not the same as "
			          << "B: " << b2 << '\n';
		}
	}
}

void test_add_years(DDATE::Date& a, CHRONO::Date& b,
                    const std::vector<int>& test_y)
{
	for (int years : test_y) {
		DDATE::Date a2{ a.days_since_epoch() };
		CHRONO::Date b2{ b.year(), b.month(), b.day() };
		a2.add_years(years);
		b2.add_years(years);
		std::cout << "Adding " << pad(years, 8, true) << " years... "
		<< pad((a2 == b2 ? "Passed" : "Failed"), 15, true)
		<< '\n';
		if (a2 != b2) {
			std::cout << "A: " << a2 << " is not the same as "
			          << "B: " << b2 << '\n';
		}
	}
}

// -----------------------------------------------------------------------------

char get_mode_of_input(bool& should_continue) {
	std::cout
		<< "Select the mode of input:" << '\n'
		<< "  a = Express date as the number of days passed since the 'epoch'"
		<< '\n'
		<< "  b = Express date as Year, Month, Days"
		<< '\n' << '\n';

	char c{};
	while (std::cin)
	try {
		std::cout << "Enter 'a' or 'b' (or '" << CONST::EXIT << "')"
		          << '\n';

		std::cout << CONST::PROMPT;

		if (entered_exit(CONST::EXIT)) {
			should_continue = false;
			c = 0;
		}
		std::string choice{ buffer_until_eol() };
		if (choice == "a\n") {
			c = 'a';
			break;
		} else if (choice == "b\n") {
			c = 'b';
			break;
		}
	}
	catch (std::exception& e) {
		clear_buffer();
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (...) {
		clear_buffer();
		throw std::runtime_error("Unexpected error");
	}
	return c;
}

void get_date_by_days(Simple_date epoch) {
	DDATE::Date test;
	CHRONO::Date compare;
	while (std::cin)
	try{
		std::cout << "Enter the number of days passed since "
			<< month_name(epoch) << " " << epoch.day << " " << epoch.year
			<< " (or '" << CONST::EXIT << "')"
			<< '\n';
		std::cout << CONST::PROMPT;

		if (entered_exit(CONST::EXIT)) {
			return;
		}

		if (count_input_int_vals() != 1) {
			continue;
		}

		std::cin >> test;
		clear_buffer();
		compare = CHRONO::Date(epoch.year,
		                       static_cast<CHRONO::Month>(epoch.month),
		                       epoch.day);
		compare.add_days(test.days_since_epoch());
		print_results(test, compare, epoch);

		std::cout << "Some additional tests:" << '\n';
		test_add_months(test, compare, {1, 23, 34, 123});
		test_add_years(test, compare, {1, 4, 122, 401});
		std::cout << '\n';
	}
	catch (std::exception& e) {
		clear_buffer();
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (...) {
		clear_buffer();
		throw std::exception("Unknown");
	}
}

void get_date_by_ymd(Simple_date epoch) {
	DDATE::Date test;
	CHRONO::Date compare;
	while (std::cin)
	try{
		std::cout << "Enter the <Year> <Month> and <Day> as integers"
			<< " (or '" << CONST::EXIT << "')"
			<< '\n';
		std::cout << CONST::PROMPT;

		if (entered_exit(CONST::EXIT)) {
			return;
		}

		if (count_input_int_vals() != 3) {
			continue;
		}

		std::cin >> compare;
		clear_buffer();
		test = DDATE::Date(compare.year(),
		                   static_cast<DDATE::Month>(compare.month()),
		                   compare.day());

		print_results(test, compare, epoch);

		std::cout << "Some additional tests:" << '\n';
		test_add_months(test, compare, {1, 23, 34, 123});
		test_add_years(test, compare, {1, 4, 122, 401});
		std::cout << '\n';
	}
	catch (std::exception& e) {
		clear_buffer();
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (...) {
		clear_buffer();
		throw std::exception("Unknown");
	}
}

// -----------------------------------------------------------------------------

int main()
try {
	DDATE::Date ep;
	std::cout
		<< "Number of days passed since "
		<< ep.month() << " " << ep.day() << " " << ep.year() << '\n'
	    << "This program takes any date represented as the no. of days " << '\n'
	    << "passed since the 'epoch date', and prints out its characteristics."
		<< '\n' << '\n'
		<< "An instance of the Date class from the previous exercise is" << '\n'
		<< "used to confirm the validity of the printed data."
		<< '\n' << '\n'
		<< "The results from the Date class of this exercise are marked 'A'."
		<< '\n'
		<< "The results used for validation are marked 'B'."
		<< '\n' << '\n';

	bool should_continue{ true };
	char choice{ get_mode_of_input(should_continue) };
	if (should_continue) {
		Simple_date ep_simple{
			ep.year(), static_cast<int>(ep.month()), ep.day()
		};
		if (choice == 'a') {
			get_date_by_days(ep_simple);
		} else {
			get_date_by_ymd(ep_simple);
		}
	}


	std::cout << "Enter any character to exit" << '\n';
	help::wait_for_enter();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Unexpected error: " << e.what() << '\n';
	std::cout << "Enter any character to exit" << '\n';
	help::wait_for_enter();
	return 1;
}
catch (...) {
	std::cerr << "Unexpected unknown error" << '\n';
	std::cout << "Enter any character to exit" << '\n';
	help::wait_for_enter();
	return 2;
}
