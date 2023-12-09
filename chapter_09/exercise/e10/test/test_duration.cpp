#include "test_date.h"
#include <string>

void test_duration(const Date& start, const Date& end, int expected) {
	int days{ duration_in_days(start, end) };

	if (days != expected) {
		throw std::runtime_error(
			"Wrong amount of days calculated between: " +
			std::to_string(start.year()) + ", " +
			std::to_string(static_cast<int>(start.month())) + ", " +
			std::to_string(start.day()) +
			" and " +
			std::to_string(end.year()) + ", " +
			std::to_string(static_cast<int>(end.month())) + ", " +
			std::to_string(end.day()) +
			". Expected: " + std::to_string(expected) + " days "
			"but got " + std::to_string(days) + " days"
		);
	}
	std::cout << "Test passed, the number of days between " << start
	          << " and " << end << " is: " << expected << '\n';
}

void test_duration_multiple() {
	test_duration({ 1648, Month::nov, 10 }, { 1833, Month::jul,  3 }, 67439);
	test_duration({ 1932, Month::mar, 29 }, { 2468, Month::nov,  3 }, 195990);
	test_duration({ 1840, Month::oct, 20 }, { 2925, Month::jun, 11 }, 396157);
	test_duration({ 2028, Month::nov, 30 }, { 2982, Month::feb,  8 }, 348146);
	test_duration({ 1912, Month::apr, 26 }, { 2388, Month::mar, 14 }, 173813);
	test_duration({ 1968, Month::feb, 13 }, { 2701, Month::jun, 23 }, 267853);
	test_duration({ 1772, Month::aug, 16 }, { 2954, Month::mar, 22 }, 431569);
	test_duration({ 2000, Month::dec, 1 }, { 2000, Month::dec, 31 }, 30);
	test_duration({ 2000, Month::jan, 1 }, { 2000, Month::dec, 31 }, 365);
	test_duration({ 1999, Month::dec, 1 }, { 2001, Month::dec,  1 }, 731);
	test_duration({ 1938, Month::dec, 29 }, { 2654, Month::jul, 10 }, 261342);
	test_duration({ 1862, Month::jan, 17 }, { 2059, Month::aug, 11 }, 72159);
	test_duration({ 1814, Month::apr, 23 }, { 2869, Month::mar, 13 }, 385291);
	test_duration({ 1717, Month::aug, 12 }, { 2907, Month::dec,  3 }, 434751);
	test_duration({ 1914, Month::aug, 21 }, { 3016, Month::feb,  3 }, 402298);
	test_duration({ 1978, Month::jul,  8 }, { 2366, Month::aug, 30 }, 141767);
	test_duration({ 1873, Month::oct, 27 }, { 2722, Month::jun, 17 }, 309958);
	test_duration({ 2042, Month::aug, 15 }, { 2406, Month::sep, 13 }, 132977);
	test_duration({ 2034, Month::nov, 19 }, { 2248, Month::feb,  9 }, 77878);
	test_duration({ 1751, Month::feb, 24 }, { 1956, Month::nov,  1 }, 75125);
	test_duration({ 1729, Month::sep,  3 }, { 2886, Month::oct,  2 }, 422615);
	test_duration({ 2022, Month::oct, 26 }, { 3029, Month::sep,  7 }, 367750);
	test_duration({ 1807, Month::aug,  2 }, { 2819, Month::nov,  8 }, 369724);
	test_duration({ 1678, Month::jul,  3 }, { 2223, Month::jul,  7 }, 199060);
	test_duration({ 1657, Month::jun, 30 }, { 2490, Month::mar,  3 }, 304128);
}

