#include "ddate.h"

// Returns the number of leap years contained in the given span of years.
// The start year is included, the end year is not, e.g.:
//     2000 to 2008 has 2 leap years
int DDATE::leap_years_from_year_span(int start_y, int end_y)
{
	--start_y; // include start year
	--end_y;   // exclude end year

	return (end_y / 4 - start_y / 4)
	     - (end_y / 100 - start_y / 100)
	     + (end_y / 400 - start_y / 400);
}

// -----------------------------------------------------------------------------

// Returns the number of days from (and including) the start of the given month
// and year, until the start of the other given month of the same year.
long DDATE::days_from_sofm_until_sofm(int y, DDATE::Month m1, DDATE::Month m2) {
	if (m2 < m1) {
		throw std::runtime_error("Cannot calculate the number of days between "
		                         "two months when the second month occurs "
		                         "before the first month.");
	}
	int d{ 0 };
	if (m1 == m2) {
		return d;
	}
	int m1_i { static_cast<int>(m1) };
	int m2_i { static_cast<int>(m2) };
	for (int i = m1_i; i < m2_i; i++) {
		d += DDATE::MONTH_DAYS()[i-1];
	}
	if (   m1 <= DDATE::Month::feb && m2 > DDATE::Month::feb
	    && DDATE::is_leap_year(y)) {
		++d;
	}

	return d;
}
// Returns the number of days from (and including) the start of the given year,
// until the start of the given month of the same year.
long DDATE::days_from_sofy_until_sofm(int y, DDATE::Month m) {
	return DDATE::days_from_sofm_until_sofm(y, DDATE::Month::jan, m);
}

// Returns the number of days from (and including) the start of the given month
// of the given year, until the end of the same year.
long DDATE::days_from_sofm_until_eofy(int y, DDATE::Month m) {
	int d{ 0 };
	int mi { static_cast<int>(m) };
	for (int i = mi; i <= 12; i++) {
		d += DDATE::MONTH_DAYS()[i-1];
	}
	if (m <= DDATE::Month::feb && DDATE::is_leap_year(y)) {
		++d;
	}

	return d;
}

long DDATE::duration_in_days(int y1, DDATE::Month m1, int d1,
                            int y2, DDATE::Month m2, int d2)
{
if (is_before_date(y2, m2, d2, y1, m1, d1)) {
		throw std::runtime_error("Cannot calculate duration, the end date "
		                         "occurs before the start date");
	}
	if (y1 == y2 && m1 == m2 && d1 == d2) {
		return 0;
	}

	int days{ 0 };
	int y_diff{ y2 - y1 };
	int m_diff{ static_cast<int>(m2) -
	            static_cast<int>(m1) };
	int d_diff{ d2 - d1 };
	if (y_diff) {
		days += days_from_sofm_until_eofy(y1, m1) - d1;
		// note that we are now at "start year + 1"
		if (y_diff > 1) {
			days += 365 * (y_diff-1) +
					leap_years_from_year_span(y1 + 1, y2);
		}
		days += days_from_sofy_until_sofm(y2, m2) + d2;
	} else {
		if (m_diff) {
			days += days_from_sofm_until_sofm(y1, m1, m2)
			        - d1 + d2;
		} else {
			days = d_diff;
		}
	}
	return days;
}
