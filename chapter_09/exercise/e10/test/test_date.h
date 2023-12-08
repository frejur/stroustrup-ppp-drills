#ifndef TEST_DATE_H
#define TEST_DATE_H

#include "../date/date.h"
#include <string>

void test_leap_year_helper(int year, bool invert=false) {
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

void test_is_valid_date(int y, Month m, int d, bool invert=false) {
	if (!is_date(y, m, d) * !invert) {
		std::cout
			<< "Checking if " << '(' << y << ", "
			<< m << ", " << d <<  ") is "
			<< (invert ? "NOT" : "indeed") << " a valid date..." << '\n';
		throw std::runtime_error(std::string((invert ? "Did not expect"
		                                             : "Expected"))
		                        + " a valid date");
	}
	std::cout << '(' << y << ", " << m << ", " << d << ") is "
	          << (invert ? "NOT" : "indeed")
	          << " a valid date" << '\n';
}

void test_add_year_eof_feb() {
	Date d{ 2020, Month::feb, 29 };
	std::cout << "Adding a a year to date " << d << "..." << '\n';
	d.add_years(1);
	if (d.month() != Month::mar || d.day() != 1) {
		throw std::runtime_error("Expected date to switch to March");
	}
	std::cout << "New date: " << d << '\n';
}

void test_add_days(const Date& start, const int add_days, const Date& expected)
{
	Date s{ start };
	s.add_days(add_days);

	if (s != expected) {
		throw std::runtime_error(
			"Wrong date after adding " + std::to_string(add_days) +
			" days to " +
			std::to_string(start.year()) + ", " +
			std::to_string(static_cast<int>(start.month())) + ", " +
			std::to_string(start.day()) +
			". Expected: " +
			std::to_string(expected.year()) + ", " +
			std::to_string(static_cast<int>(expected.month())) + ", " +
			std::to_string(expected.day()) +
			" but got " +
			std::to_string(s.year()) + ", " +
			std::to_string(static_cast<int>(s.month())) + ", " +
			std::to_string(s.day())
		);
	}
	std::cout << "Test passed, added " << add_days << " days to "
	          << start << " and got " << expected << " as expected." << '\n';
}

void test_add_days_multiple() {
	// some generated test dates known to be true
	test_add_days({ 1680, Month::feb, 20 }, 172085, { 2151, Month::apr, 17 });
	test_add_days({ 2000, Month::apr, 10 }, 10, { 2000, Month::apr, 20 });
	test_add_days({ 2000, Month::apr, 10 }, 20, { 2000, Month::apr, 30 });
	test_add_days({ 2000, Month::apr, 10 }, 21, { 2000, Month::may, 1 });
	test_add_days({ 2000, Month::apr, 10 }, 20, { 2000, Month::apr, 30 });
	test_add_days({ 1624, Month::feb, 15 }, 1685, { 1628, Month::sep, 26 });
	test_add_days({ 1889, Month::feb, 14 }, 1614, { 1893, Month::jul, 17 });
	test_add_days({ 1814, Month::dec, 17 }, 957, { 1817, Month::jul, 31 });
	test_add_days({ 1697, Month::mar, 16 }, 280, { 1697, Month::dec, 21 });
	test_add_days({ 1694, Month::sep, 17 }, 112, { 1695, Month::jan, 7 });
	test_add_days({ 1850, Month::jun, 18 }, 1184, { 1853, Month::sep, 14 });
	test_add_days({ 1922, Month::jul, 5 }, 433, { 1923, Month::sep, 11 });
	test_add_days({ 1660, Month::jun, 9 }, 891, { 1662, Month::nov, 17 });
	test_add_days({ 1819, Month::may, 2 }, 1003, { 1822, Month::jan, 29 });
	test_add_days({ 1879, Month::dec, 3 }, 352081, { 2843, Month::nov, 20 });
	test_add_days({ 1986, Month::apr, 28 }, 256851, { 2689, Month::jul, 22 });
	test_add_days({ 1757, Month::feb, 10 }, 223470, { 2368, Month::dec, 14 });
	test_add_days({ 1834, Month::jun, 2 }, 189506, { 2353, Month::apr, 8 });
	test_add_days({ 2013, Month::jul, 20 }, 328860, { 2913, Month::dec, 9 });
	test_add_days({ 1602, Month::jun, 19 }, 292216, { 2402, Month::jul, 11 });
	test_add_days({ 1902, Month::jun, 28 }, 205181, { 2464, Month::apr, 2 });
	test_add_days({ 1662, Month::jul, 11 }, 200305, { 2210, Month::dec, 11 });
	test_add_days({ 1825, Month::aug, 6 }, 154725, { 2249, Month::mar, 21 });
}

void test_add_months(const Date& start, const int add_months,
                     const Date& expected)
{
	Date s{ start };
	s.add_months(add_months);
	if (s != expected) {
		throw std::runtime_error(
			"Wrong date after adding " + std::to_string(add_months) +
			" months to " +
			std::to_string(start.year()) + ", " +
			std::to_string(static_cast<int>(start.month())) + ", " +
			std::to_string(start.day()) +
			". Expected: " +
			std::to_string(expected.year()) + ", " +
			std::to_string(static_cast<int>(expected.month())) + ", " +
			std::to_string(expected.day()) +
			" but got " +
			std::to_string(s.year()) + ", " +
			std::to_string(static_cast<int>(s.month())) + ", " +
			std::to_string(s.day())
		);
	}
	std::cout << "Test passed, added " << add_months << " months to "
	          << start << " and got " << expected << " as expected." << '\n';
}

void test_add_months_multiple() {
	test_add_months({ 2000, Month::jan, 31 }, 1, { 2000, Month::feb, 29 });
	test_add_months({ 2001, Month::jan, 31 }, 1, { 2001, Month::feb, 28 });
	test_add_months({ 1771, Month::feb, 20 }, 18, { 1772, Month::aug, 20 });
	test_add_months({ 1796, Month::jan, 12 }, 25, { 1798, Month::feb, 12 });
	test_add_months({ 1930, Month::aug, 3 }, 22, { 1932, Month::jun, 3 });
	test_add_months({ 1697, Month::sep, 27 }, 36, { 1700, Month::sep, 27 });
	test_add_months({ 1736, Month::oct, 24 }, 4, { 1737, Month::feb, 24 });
	test_add_months({ 1642, Month::jan, 19 }, 26, { 1644, Month::mar, 19 });
	test_add_months({ 1617, Month::apr, 24 }, 22, { 1619, Month::feb, 24 });
	test_add_months({ 1732, Month::apr, 28 }, 7, { 1732, Month::nov, 28 });
	test_add_months({ 1989, Month::feb, 7 }, 4, { 1989, Month::jun, 7 });
	test_add_months({ 1702, Month::jun, 7 }, 9905, { 2527, Month::nov, 7 });
	test_add_months({ 1795, Month::may, 6 }, 9712, { 2604, Month::sep, 6 });
	test_add_months({ 1730, Month::mar, 24 }, 6340, { 2258, Month::jul, 24 });
	test_add_months({ 1942, Month::nov, 8 }, 7179, { 2541, Month::feb, 8 });
	test_add_months({ 1696, Month::dec, 8 }, 10753, { 2593, Month::jan, 8 });
	test_add_months({ 1703, Month::jan, 25 }, 9973, { 2534, Month::feb, 25 });
	test_add_months({ 1856, Month::apr, 24 }, 7331, { 2467, Month::mar, 24 });
	test_add_months({ 1810, Month::jun, 5 }, 10788, { 2709, Month::jun, 5 });
	test_add_months({ 1878, Month::jul, 14 }, 8045, { 2548, Month::dec, 14 });
}

void test_days_until_eofy(int y, Month m, int expected) {
	int days{ days_from_sofm_until_eofy(y, m) };
	if (days != expected) {
		throw std::runtime_error(
			"Wrong number of days returned when calculating duration "
			"( " + std::to_string(y) + ", "
			+ std::to_string(static_cast<int>(m)) +
			") until end of the same year. " +
			". Expected: " +
			std::to_string(expected) + " days,"
			" but got " +
			std::to_string(days) + " days."
		);
	}
	std::cout << "Test passed, there are " << days << " days from "
	          << "( " << y << ", " << m << ") until the end of the same year"
	          << '\n';
}

void test_days_until_eofy_multiple() {
	test_days_until_eofy(2000, Month::jan, 366);
	test_days_until_eofy(1939, Month::apr, 275);
	test_days_until_eofy(1761, Month::apr, 275);
	test_days_until_eofy(1760, Month::oct, 92);
	test_days_until_eofy(1783, Month::oct, 92);
	test_days_until_eofy(1935, Month::oct, 92);
	test_days_until_eofy(1715, Month::sep, 122);
	test_days_until_eofy(1610, Month::feb, 334);
	test_days_until_eofy(1756, Month::apr, 275);
	test_days_until_eofy(1683, Month::jan, 365);
	test_days_until_eofy(1635, Month::may, 245);
	test_days_until_eofy(1959, Month::mar, 306);
	test_days_until_eofy(1818, Month::mar, 306);
	test_days_until_eofy(1972, Month::oct, 92);
	test_days_until_eofy(1806, Month::sep, 122);
	test_days_until_eofy(1682, Month::feb, 334);
	test_days_until_eofy(1824, Month::jul, 184);
	test_days_until_eofy(1620, Month::mar, 306);
	test_days_until_eofy(1610, Month::nov, 61);
}

void test_days_until_sofm(int y, Month m, int expected) {
	int days{ days_from_sofy_until_sofm(y, m) };
	if (days != expected) {
		throw std::runtime_error(
			"Wrong number of days returned when calculating duration "
			"from the start of the year until "
			"( " + std::to_string(y) + ", "
			+ std::to_string(static_cast<int>(m)) +
			") of the same year. " +
			". Expected: " +
			std::to_string(expected) + " days,"
			" but got " +
			std::to_string(days) + " days."
		);
	}
	std::cout << "Test passed, there are " << days << " days from the start"
	             " of the year until "
	          << "( " << y << ", " << m << ") of the same year"
	          << '\n';
}

void test_days_until_sofm_multiple() {
	test_days_until_sofm(2000, Month::jan, 0);
	test_days_until_sofm(2006, Month::apr, 90);
	test_days_until_sofm(1672, Month::feb, 31);
	test_days_until_sofm(1800, Month::dec, 334);
	test_days_until_sofm(1913, Month::feb, 31);
	test_days_until_sofm(1724, Month::mar, 60);
	test_days_until_sofm(1765, Month::feb, 31);
	test_days_until_sofm(1645, Month::aug, 212);
	test_days_until_sofm(1929, Month::dec, 334);
	test_days_until_sofm(1884, Month::jun, 152);
	test_days_until_sofm(1988, Month::nov, 305);
	test_days_until_sofm(1897, Month::oct, 273);
	test_days_until_sofm(1858, Month::oct, 273);
	test_days_until_sofm(1845, Month::oct, 273);
	test_days_until_sofm(1617, Month::apr, 90);
	test_days_until_sofm(1698, Month::jan, 0);
	test_days_until_sofm(1812, Month::aug, 213);
	test_days_until_sofm(1950, Month::oct, 273);
	test_days_until_sofm(1739, Month::oct, 273);
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

void test_date() {
	std::cout << '\n'
	          << "Testing is_leap_year()..." << '\n'
	          << '\n';
	test_leap_year_helper(2020);
	test_leap_year_helper(2019, true);
	test_leap_year_helper(400 * 5);
	test_leap_year_helper(400 * 5 + 100, true);

	test_is_valid_date(2020, Month::feb, 29);
	test_is_valid_date(2019, Month::feb, 29, true);

	test_add_year_eof_feb();

	std::cout << '\n'
	          << "Testing add_years()..." << '\n'
	          << '\n';

	test_add_days_multiple();

	std::cout << '\n'
	          << "Testing add_months()..." << '\n'
	          << '\n';

	test_add_months_multiple();

	std::cout << '\n'
	          << "Testing days_from_sofm_until_eofy()..." << '\n'
	          << '\n';

	test_days_until_eofy_multiple();

	std::cout << '\n'
	          << "Testing days_from_sofy_until_sofm()..." << '\n'
	          << '\n';

	test_days_until_sofm_multiple();

	std::cout << '\n'
	          << "Testing leap_years_from_year_span()..." << '\n'
	          << '\n';

	test_count_leap_years_multiple();

	std::cout << '\n'
	          << "Testing duration_in_days()..." << '\n'
	          << '\n';

	test_duration_multiple();
}


#endif // TEST_DATE_H
