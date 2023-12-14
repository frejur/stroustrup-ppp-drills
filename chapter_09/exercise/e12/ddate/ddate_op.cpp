#include "ddate.h"

bool DDATE::operator==(const DDATE::Date& a, const DDATE::Date& b)
{
	return a.days_since_epoch() == b.days_since_epoch();
}

bool DDATE::operator!=(const DDATE::Date& a, const DDATE::Date& b)
{
	return !DDATE::operator==(a, b);
}
