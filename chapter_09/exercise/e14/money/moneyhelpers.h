#ifndef MONEYHELPERS_H
#define MONEYHELPERS_H
#include <stdexcept>
#include <vector>

namespace Money_lib_helpers { // -----------------------------------------------

constexpr long get_exp(long double num) {
	long exp{ 0 };
	if (num == 0) {
		return exp;
	}
	if (num < 0) {
		throw std::runtime_error("Expected a positive number");
	}
	long double new_num{ num };
	// Fraction
	while(new_num < 1) {
		--exp;
		new_num *= 10;
	}
	// Whole number
	while(new_num > 1) {
		++exp;
		new_num /= 10;
	}
	return exp;
};

constexpr int count_d(long long num) {
	if (num == 0) {
		return 1;
	}

    int c = 0;
    while (num != 0) {
        num /= 10;
        ++c;
    }
    return c;
}

constexpr long double exp_f(int e) {
	if (e == 0) {
		return 1;
	}
	long double f{ 1 };
	if (e > 0) {
		for (int i = 1; i <= e; ++i) {
			f *= 10;
		}
	} else {
		for (int i = e; i <= 0; ++i) {
			f /= 10;
		}
	}
	return f;
}

constexpr long long factor_until_overflow(long long n) {
	long long accumulator = 1;

	// Keep multiplying until overflow
	long long n_new{ n * 10 };
	while ((n < n_new) && ((n_new) / 10 == n)) {
		accumulator *= 10;
		n = n_new;
		n_new *= 10;
	}

	return accumulator;
}

constexpr long decimal_to_cents(double amt_as_dbl, bool allow_infoloss=false) {
	amt_as_dbl *= 100;
	long amt_as_long{ static_cast<long>(amt_as_dbl) };

	if (allow_infoloss) {
		return amt_as_long;
	}

	if (amt_as_dbl != amt_as_long) {
		throw std::runtime_error("Cannot create Money from the given "
								 "floating-point value since it would lead "
								 "to information loss");
	}
	return amt_as_long;
}

constexpr int XRATE_SIGNIFICANT_DIGITS() { return 7; };
constexpr long long XRATE_FACTOR() {
	return exp_f(XRATE_SIGNIFICANT_DIGITS());
}

} // namespace Money_lib_helpers -----------------------------------------------

#endif // MONEYHELPERS_H
