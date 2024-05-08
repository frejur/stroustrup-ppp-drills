#include "exchangerate.h"

namespace XRT = Exchange_rate_lib;
namespace MLH = Money_lib_helpers;

XRT::Exchange_rate::Exchange_rate(long double xrate) {
	if (xrate == 0) {
		whole = 0;
		return;
	}
	update(xrate);
}

void XRT::Exchange_rate::update(long double xrate) {
	int sign{ (xrate < 0) ? -1 : 1 };
	int whole_temp{ static_cast<int>(xrate * sign) };
	long double fract_as_double{
		(whole_temp == 0) ? xrate * sign : xrate * sign - whole_temp
	};
    int exp_temp{ static_cast<int>(MLH::get_exp(fract_as_double)) };
	long exp_f{(exp_temp == 0) ? 1 : static_cast<long>(MLH::exp_f(-exp_temp))};

	long long fract_temp{ 0 };
	long long fract_temp_round{ 0 };
	fract_temp = fract_as_double * MLH::XRATE_FACTOR() * exp_f;
	fract_temp_round = (
		(fract_as_double * MLH::XRATE_FACTOR() * exp_f * 10 + (5 * sign)) / 10
	);
	if (fract_temp != fract_temp_round) {
		if (MLH::count_d(fract_temp) < MLH::count_d(fract_temp_round)) {
			if (exp_temp == 0) {
				// 9.999 -> 10, etc.
				++whole_temp;
				fract_temp_round = 0;
			} else {
				++exp_temp;
			}
		}
	}

	int num_d_fract{ MLH::count_d(fract_temp) };
	while (num_d_fract < MLH::XRATE_SIGNIFICANT_DIGITS()) {
		fract_temp_round *= 10;
		++num_d_fract;
	}

	update(whole_temp * sign, fract_temp_round, exp_temp);
}

long double XRT::Exchange_rate::value() const {
	return (
		whole + fract /
		static_cast<long double>(MLH::XRATE_FACTOR() * MLH::exp_f(exp))
	);
}

long long XRT::Exchange_rate::as_integer() const {
	return (
		whole * MLH::XRATE_FACTOR() * MLH::exp_f(-exp) +
		fract);
}

int XRT::Exchange_rate::scale_factor() const {
	if (exp > 0) {
		throw std::runtime_error("Exponent should be a negative value");
	}
	long double scale{ MLH::exp_f(-exp) };
	return (scale == 0)
		? 1
		: static_cast<int>(scale);
}

void XRT::Exchange_rate::flip_currencies() {
	if (whole == 0 && fract == 0) {
		return;
	}
	int sign{ (whole < 0) ? -1 : 1 };
	long long unit_of_one{
		static_cast<long long>(
			MLH::XRATE_FACTOR() * scale_factor())
	};
	long long xrate_old{ as_integer() * sign};
	long long precision_scale_f{ MLH::factor_until_overflow(unit_of_one) };

	unit_of_one *= precision_scale_f;
	long long combined_scale_f{ unit_of_one / MLH::XRATE_FACTOR() };
	long long xrate = unit_of_one / xrate_old;

	int whole_temp{
		static_cast<int>(xrate / precision_scale_f)
	};
	long long fract_temp{
		(whole_temp == 0)
			? xrate
			: xrate - whole_temp * precision_scale_f
	};

    int count_d_unit{ static_cast<int>(MLH::get_exp(combined_scale_f)) };
	int count_d_fract{ MLH::count_d(fract_temp ) };
	int exp_temp{ count_d_fract - count_d_unit };

	long long fract_temp_round{ fract_temp };
	if (count_d_fract < MLH::XRATE_SIGNIFICANT_DIGITS()) {
		fract_temp *= MLH::exp_f
			(MLH::XRATE_SIGNIFICANT_DIGITS() - count_d_fract);
		fract_temp_round = fract_temp;
	} else if (count_d_fract > MLH::XRATE_SIGNIFICANT_DIGITS()) {
		fract_temp /= MLH::exp_f(
			count_d_fract - MLH::XRATE_SIGNIFICANT_DIGITS() - 1);
		fract_temp_round = (fract_temp + 5) / 10;
		fract_temp /= 10;
	}

	if (fract_temp != fract_temp_round) {
		if (MLH::count_d(fract_temp) < MLH::count_d(fract_temp_round)) {
			if (exp_temp == 0) {
				// 9.999 -> 10, etc.
				++whole_temp;
				fract_temp_round = 0;
			} else {
				++exp_temp;
			}
		}
	}

	update(whole_temp, fract_temp_round, exp_temp);
}

long Exchange_rate_lib::operator*(Exchange_rate xrate, long f)
{
	long long p{ 0 }; // Product

	long long x{ xrate.as_integer() };
	if (x == 0 || f == 0) {
		return p;
	}

	int sign_f{ (f < 0) ? -1 : 1 };
	f *= sign_f;

	int scale{ xrate.scale_factor() };
	long long max_f{ MLH::factor_until_overflow(x * f) };
	if (scale > max_f) {
		throw std::runtime_error("Overflow");
	}

	long long precision_f{ (scale == 0) ? max_f : max_f / scale };
	int round_f{ (precision_f > 10) ? 10 : 1 };
	precision_f /= round_f;

	p = x * f;
	p *= precision_f * round_f;
	p /= (scale * precision_f * MLH::XRATE_FACTOR());

	if (round_f == 10) {
		p = (p + 5) / 10;
	}

	return static_cast<long>(p * sign_f);
}
