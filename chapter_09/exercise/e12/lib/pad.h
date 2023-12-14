#ifndef PAD_H
#define PAD_H
#include <string>
#include "../ddate/ddate.h"
#include "../date/date.h"

struct Padded_string
{
	std::string s;
	int len;
	bool reverse;
};


Padded_string pad(int n, int len, bool rev=false) {
	return {std::to_string(n), len, rev};
}

Padded_string pad(std::string s, int len, bool rev=false) {
	return {s, len, rev};
}

Padded_string pad(DDATE::Month m, int len, bool rev=false) {
	std::string s{ DDATE::MONTH_NAMES()[static_cast<int>(m) - 1] };
	return {s, len, rev};
}

Padded_string pad(DDATE::Day_of_the_week dotw, int len, bool rev=false) {
	std::string s{ DDATE::DOTW_NAMES()[static_cast<int>(dotw) - 1] };
	return {s, len, rev};
}

Padded_string pad(CHRONO::Month m, int len, bool rev=false) {
	std::string s{ DDATE::MONTH_NAMES()[static_cast<int>(m) - 1] };
	return {s, len, rev};
}

Padded_string pad(CHRONO::Day_of_the_week dotw, int len, bool rev=false) {
	std::string s{ DDATE::DOTW_NAMES()[static_cast<int>(dotw) - 1] };
	return {s, len, rev};
}

std::ostream& operator<<(std::ostream& os, const Padded_string& pad)
{
	if (!pad.reverse) {
		for (int i = 0; i < pad.len; ++i) {
			if (pad.s.size() == 0 || i > pad.s.size() - 1) {
				os << ' ';
			} else {
				os << pad.s[i];
			}
		}
	} else {
		int pre_ws{ pad.len - static_cast<int>(pad.s.size()) };
		for (int i = 0; i < pre_ws; ++i) {
			os << ' ';
		}
		os << pad.s;
	}
	return os;
}


#endif // PAD_H
