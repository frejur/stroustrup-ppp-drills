#include "test_date.h"
#include <string>

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

