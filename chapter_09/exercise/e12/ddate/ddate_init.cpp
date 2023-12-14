#include "ddate.h"
#include <stdexcept>

DDATE::Date::Date(long days) : d_diff{ 0 }, is_cached{ false }
{
	if (!is_date(days)) {
		throw std::runtime_error("Invalid date");
	}
	d_diff = days;
}

DDATE::Date::Date(int y, Month m, int d) : d_diff{ 0 }, is_cached{ false }
{
	if (!is_date(y, m, d)) {
		throw std::runtime_error("Invalid date");
	}
	d_diff = DDATE::duration_in_days(
		DDATE::EPOCH_Y, DDATE::EPOCH_M, DDATE::EPOCH_D, y, m, d
	);
};
