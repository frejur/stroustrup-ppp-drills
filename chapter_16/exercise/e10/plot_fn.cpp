#include "plot_fn.h"
#include <cmath>
#include <stdexcept>
#include <vector>

namespace {
double sgn(double num)
{
	return ((num != 0) * (num > 0 ? 1 : -1));
}
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

//------------------------------------------------------------------------------

double Plot::fn_sup_upr(double x)
{
	return 0.5 * (1 + superellipse(x * 2 - 1.0));
}

double Plot::fn_sup_lwr(double x)
{
	return 0.5 * (1 - superellipse(x * 2 - 1.0));
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

//------------------------------------------------------------------------------
std::vector<int> Plot::gen_seq(int end_n)
{
	std::vector<int> temp(end_n);
	for (int i = 0; i < end_n; ++i) {
		temp[i] = i;
	}
	return temp;
}

void Plot::swap_permutations(std::vector<int>& table, int a_idx, int b_idx)
{
	int temp = table[a_idx];
	table[a_idx] = table[b_idx];
	table[b_idx] = temp;
}

void Plot::shuffle_permutations(std::vector<int>& table, int n_times)
{
	for (int i = 0; i < n_times; ++i) {
		for (int j = 0; j < table.size(); ++j) {
			int rand_b = (j + Plot::rand_int(0, table.size() - 1))
			             % table.size();
			Plot::swap_permutations(table, j, rand_b);
		}
	}
}

std::vector<float> Plot::gen_gradients(int end_n)
{
	std::vector<float> temp;
	for (int i = 0; i < end_n; ++i) {
		temp.push_back(rand_gradient());
	}
	return temp;
}
