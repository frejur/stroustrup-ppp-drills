#include "ddate.h"

DDATE::Date DDATE::next_sunday(const DDATE::Date& d) {
	return {
		d.days_since_epoch() + 7 - static_cast<int>(d.day_of_the_week()) % 7
	};
};

DDATE::Date DDATE::next_weekday(const DDATE::Date& d) {
	int dotw{ static_cast<int>(d.day_of_the_week()) };
	int offs{ 1 };
	if (dotw >= 5) {
		offs = 8 - dotw;
	}
	return { d.days_since_epoch() + offs };
}
