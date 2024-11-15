#include "plot_fn.h"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace {
double sgn(double num)
{
	return ((num != 0) * (num > 0 ? 1 : -1));
}
double superellipse_vertical_offset{0.01};
} // namespace
//------------------------------------------------------------------------------

double Plot::fn_log(double x)
{
	return std::log(x + 1) / std::log(fn_log_base);
}

double Plot::fn_sin(double x)
{
	return std::sin(x * fn_sin_freq) * 0.5 + 0.5;
}

double Plot::fn_sup_upr(double x)
{
	const double offs_y = superellipse_vertical_offset;
	return offs_y + (0.5 - offs_y * 1) * (1 + superellipse(x * 2 - 1.0));
}

double Plot::fn_sup_lwr(double x)
{
	const double offs_y = superellipse_vertical_offset;
	return offs_y + (0.5 - offs_y * 1) * (1 - superellipse(x * 2 - 1.0));
}

double Plot::superellipse(double x)
{
	const double a = 1.0;
	const double b = 1.0;
	const double m = fn_sup_exp_n;
	const double n = fn_sup_exp_m;

	double t = 1 - std::pow(std::abs(x) / a, m);

	double y = b * std::pow(t, 1.0 / n);
	return y;
}
