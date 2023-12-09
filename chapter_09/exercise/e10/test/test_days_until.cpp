#include "test_date.h"
#include <string>

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
