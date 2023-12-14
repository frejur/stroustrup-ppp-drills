#include "ddate.h"

int DDATE::Date::day()
{
	if (d_diff == 0) {
		return DDATE::EPOCH_D;
	}
	if (d_diff < EPOCH_D_UNTIL_EOFM()) {
		return DDATE::EPOCH_D + d_diff;
	}
	update();
	return d;
}

int DDATE::Date::year()
{
	if (d_diff == 0 || d_diff < EPOCH_D_UNTIL_EOFY()) {
		return DDATE::EPOCH_Y;
	}
	update();
	return y;
}

DDATE::Month DDATE::Date::month()
{
	if (d_diff == 0 || d_diff < EPOCH_D_UNTIL_EOFM()) {
		return DDATE::EPOCH_M;
	}
	update();
	return m;
}

//------------------------------------------------------------------------------

void DDATE::Date::update() {
	if (is_cached) {
		return;
	}
	// Unless the epoch is the 1st day of the year, offset until the next year
	const int d_offs{ DDATE::EPOCH_D_CALC_OFFSET() };

	long days_left{ d_diff };
	DDATE::Month new_m{ DDATE::EPOCH_M };
	int new_d{ DDATE::EPOCH_D };

	if (d_diff >= d_offs) {
		days_left = (d_offs == 0)
		            ? days_left + new_d - 1
		            : days_left - d_offs - 1;
		int years_added = (d_offs == 0) ? 0 : 1;
		int num_leap_years{ 0 };
		while (days_left) {
			int add_y{ days_left / 366 };
			if (add_y == 0) {
				if (!DDATE::is_leap_year(DDATE::EPOCH_Y + years_added)) {
					num_leap_years = 0;
					add_y = days_left / 365;
				}
				if (add_y == 0) {
					break;
				}
			} else {
				num_leap_years = (
					leap_years_from_year_span(DDATE::EPOCH_Y + years_added,
					                          DDATE::EPOCH_Y + years_added
					                          	+ add_y)
				);
			}

			years_added += add_y;
			days_left -= (add_y * 365 + num_leap_years);
		}
		y = DDATE::EPOCH_Y + years_added;
		new_m = DDATE::Month::jan;
		new_d = 1;
	}

	while (days_left) {
		int mdays{ DDATE::days_in_month(y, new_m) };
		if (days_left < (mdays - new_d + 1)) {
			new_d = days_left + 1;
			days_left = 0;
		} else {
			days_left -= (mdays - new_d + 1);
			new_m = static_cast<DDATE::Month>(static_cast<int>(new_m) + 1);
			new_d = 1;
		}
	}

	m = new_m;
	d = new_d;
	is_cached = true;
}

