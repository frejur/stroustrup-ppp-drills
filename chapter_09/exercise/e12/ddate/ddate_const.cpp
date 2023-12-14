#include "ddate.h"

const std::vector<int>& DDATE::MONTH_DAYS() {
	static std::vector<int> d{ 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return d;
}

const std::vector<std::string>& DDATE::MONTH_NAMES() {
    static std::vector<std::string> names{
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };
    return names;
}

const std::vector<std::string>& DDATE::DOTW_NAMES() {
    static std::vector<std::string> names{
        "Monday", "Tuesday", "Wednesday", "Thursday",
        "Friday", "Saturday", "Sunday"
    };
    return names;
}

//------------------------------------------------------------------------------

const int DDATE::EPOCH_D_UNTIL_EOFM() {
	// Calculate days from epoch until the end of the same month
	static int days{
		DDATE::days_in_month(DDATE::EPOCH_Y, DDATE::EPOCH_M) -
		(DDATE::EPOCH_D - 1)
	};
	return days;
}

const int DDATE::EPOCH_D_UNTIL_EOFY() {
	// Calculate days from epoch until the end of the same year
	static int days{
		DDATE::days_in_month(DDATE::EPOCH_Y, DDATE::EPOCH_M) -
		DDATE::EPOCH_D +
		DDATE::days_from_sofm_until_eofy(
			DDATE::EPOCH_Y,
			static_cast<DDATE::Month>(static_cast<int>(DDATE::EPOCH_M) + 1)
		)
	};
	return days;
}

const int DDATE::EPOCH_D_CALC_OFFSET() {
	static int d_offs{
		(DDATE::EPOCH_D == 1 && DDATE::EPOCH_M == DDATE::Month::jan)
		? 0
		: DDATE::EPOCH_D_UNTIL_EOFY()
	};
	return d_offs;
}

const int DDATE::EPOCH_Y_CALC_OFFSET() {
	static int y_offs{ (EPOCH_D_CALC_OFFSET()) > 0 ? 1 : 0 };
	return y_offs;
}
