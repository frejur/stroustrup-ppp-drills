#include "plot_fn.h"
#include <cmath>

double Plot::fn_log(double x)
{
	return std::log(x + 1) / std::log(fn_log_base);
}
