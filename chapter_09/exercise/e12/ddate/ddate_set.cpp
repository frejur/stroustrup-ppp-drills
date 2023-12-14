#include "ddate.h"
#include "../lib/narrow_cast.h"
#include <stdexcept>

void DDATE::Date::add_days(const long n)
{
	if (n < 0) {
		throw std::runtime_error("Cannot add a negative number of days");
	}
	if (n == 0) {
		return;
	}
	long long new_d_diff{ d_diff + n };
	d_diff = narrow_cast<long>(new_d_diff);
	is_cached = false;
}

void DDATE::Date::add_months(const int n)
{
	if (n < 0) {
		throw std::runtime_error("Cannot add a negative number of months");
	}
	if (n == 0) {
		return;
	}

	int new_y{ year() };
	DDATE::Month new_m{ month() };
	int new_d{ day() };

	int m_left{ n };
	int m_to_sofy_next{ 13 - static_cast<int>(new_m) };
	if (n < m_to_sofy_next) {
		new_m = static_cast<DDATE::Month>(static_cast<int>(new_m) + n);
	} else {
		m_left -= m_to_sofy_next;
		int add_y{ m_left / 12 };
		new_y += + 1 + add_y;
		m_left -= add_y * 12;
		new_m = static_cast<DDATE::Month>(1 + m_left);
	}
	int m_days{ DDATE::days_in_month(new_y, new_m) };
	if (new_d > m_days) {
		new_d = m_days;
	}

	add_days(duration_in_days(year(), month(), day(), new_y, new_m, new_d));
};

void DDATE::Date::add_years(const int n)
{
	if (n < 0) {
		throw std::runtime_error("Cannot add a negative number of years");
	}
	if (n == 0) {
		return;
	}
	int new_d{ day() };
	DDATE::Month new_m{ month() };
	int new_y{ year() + n };
	if (new_m == DDATE::Month::feb && new_d == 29 && !is_leap_year(new_y))
	{
		new_m = DDATE::Month::mar;
		new_d = 1;
	}

	add_days(
		duration_in_days(year(), month(), day(), new_y, new_m, new_d)
	);
}

void DDATE::Date::subtract_days(const long n)
{
	if (n < 0) {
		throw std::runtime_error("Cannot subtract a negative number of days");
	}
	if (n == 0) {
		return;
	}
	if (n > d_diff) {
		throw std::runtime_error("Cannot subtract by the given number of days "
		                         "as that would result in a negative date "
								 "value.");
	}
	d_diff -= n;
	is_cached = false;
}

// void DDATE::Date::subtract_months(const int n)
// {};

// void DDATE::Date::subtract_years(const int n)
// {};
