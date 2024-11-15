#include "plot_fn.h"
#include <cmath>

double Plot::fn_log(double x)
{
	return std::log(x + 1) / std::log(fn_log_base);
}

double Plot::fn_sin(double x)
{
	return std::sin(x * fn_sin_freq) * 0.5 + 0.5;
}
