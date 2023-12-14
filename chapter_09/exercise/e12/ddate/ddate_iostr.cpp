#include "ddate.h"
#include <iostream>
#include "../lib/narrow_cast.h"

std::ostream& DDATE::operator<<(std::ostream& os, DDATE::Date& date)
{
	os << date.day_of_the_week() << ", "
	   << date.day() << " " << date.month() << " " << date.year();
	return os;
}

std::istream& DDATE::operator>>(std::istream& is, DDATE::Date& date)
{
	long long days;

	is >> days;
	if (!is) {
		return is;
	}

	date = DDATE::Date(narrow_cast<long>(days));

	return is;
}

// -----------------------------------------------------------------------------

std::ostream& DDATE::operator<<(std::ostream& os, const DDATE::Month month) {
	return os << DDATE::MONTH_NAMES()[static_cast<int>(month) - 1];
}

std::ostream& DDATE::operator<<(std::ostream& os,
                                const DDATE::Day_of_the_week dotw)
{
	return os << DDATE::DOTW_NAMES()[static_cast<int>(dotw) - 1];
}
