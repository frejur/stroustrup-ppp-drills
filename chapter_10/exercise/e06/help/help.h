#ifndef HELP_H
#define HELP_H
#include <stdexcept>
#include <string>

namespace help {

std::string extract_ch_from_end(std::string& s, int num_ch, bool copy = false);
inline std::string copy_ch_from_end(std::string& s, int num_ch)
{
	return extract_ch_from_end(s, num_ch, true);
};

inline constexpr int scale_factor(int decimal_count)
{
	if (decimal_count < 1) {
		return 1;
	}
	int f = 1;
	for (int i = 0; i < decimal_count; ++i) {
		f *= 10;
	}
	return f;
}

inline constexpr int exp_f_from_int(int i)
{
	// Returns the factor of exponent, 1e0 = 1, 1e1 = 10, etc.
	i = (i > 0) ? i : -i;
	int exp = 1;
	while (i > 10) {
		i /= 10;
		exp *= 10;
	}
	return exp;
}

} // namespace help

#endif // HELP_H
