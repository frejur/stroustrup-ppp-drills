#include "ddate.h"

bool DDATE::is_before_date(int y1, DDATE::Month m1, int d1,
                           int y2, DDATE::Month m2, int d2)
{
	return (
		   (y1 < y2)
		|| (y1 == y2 && static_cast<int>(m1) < static_cast<int>(m2))
		|| (y1 == y2 && static_cast<int>(m1) == static_cast<int>(m2)
		    && d1 < d2)
	);
}

bool DDATE::is_before_min_date(int y, DDATE::Month m, int d) {
	int min_y{ DDATE::EPOCH_Y };
	Month min_m{ DDATE::EPOCH_M };
	int min_d{ DDATE::EPOCH_D };

	return is_before_date(y, m, d, min_y, min_m, min_d);
}

// -----------------------------------------------------------------------------

bool DDATE::is_date(const int y, const DDATE::Month m, const int d)
{
	if (is_before_min_date(y, m, d)) {
		return false;
	}

	if (d <= 0) return false;
	if (m < DDATE::Month::jan || DDATE::Month::dec < m) return false;

	int mdays = days_in_month(y, m);
	return (mdays >= d);
	return true;
}

bool DDATE::is_date(long days)
{
	return days > 0;
}

// -----------------------------------------------------------------------------

int DDATE::days_in_month(const int y, const DDATE::Month m)
{
	int days = MONTH_DAYS().at(static_cast<int>(m) - 1);
	if (m == Month::feb && is_leap_year(y)) {
		++days;
	}
	return days;
}

bool DDATE::is_leap_year(const int y) {
	// leap year if multiple of 4
	return	!(y % 4) &&
		// if it is also NOT a mult. of 100,
		// or if it is also exactly div. by 400
		(y % 100 || !(y % 400));
}
