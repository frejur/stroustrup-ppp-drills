#ifndef PLOT_FN_H
#define PLOT_FN_H

// Functions to be plotted in My_window
struct Plot
{
	// Logarithm
	static double fn_log(double x);
	static double fn_log_base;

	// Sine
	static double fn_sin(double x);
	static double fn_sin_freq;
};

#endif // PLOT_FN_H
