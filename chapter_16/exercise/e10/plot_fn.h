#ifndef PLOT_FN_H
#define PLOT_FN_H
#include "../../lib/Point.h"

// Functions to be plotted in My_window
struct Plot
{
	// Logarithm
	static double fn_log(double x);
	static double fn_log_base;

	// Sine
	static double fn_sin(double x);
	static double fn_sin_freq;

	// Superellipse
	static double fn_sup_upr(double x);
	static double superellipse(double x);
	static double fn_sup_lwr(double x);
	static Graph_lib::Point get_super_xy(
	    double a, double b, double m, double n, double step);
	static double fn_sup_exp_n;
	static double fn_sup_exp_m;
};

#endif // PLOT_FN_H
