#ifndef PLOT_FN_H
#define PLOT_FN_H
#include "../../lib/Point.h"
#include <chrono>
#include <random>
#include <vector>

// Functions to be plotted in My_window
struct Plot
{
	// Logarithm
	static double fn_log(double x);
	static double fn_log_base;

	// -------------------------------------------------------------------------
	// Sine
	static double fn_sin(double x);
	static double fn_sin_freq;

	// -------------------------------------------------------------------------
	// Superellipse
	static double fn_sup_upr(double x);
	static double superellipse(double x);
	static double fn_sup_lwr(double x);
	static Graph_lib::Point get_super_xy(
	    double a, double b, double m, double n, double step);
	static double fn_sup_exp_n;
	static double fn_sup_exp_m;

	// -------------------------------------------------------------------------
	// Perlin noise
	static std::vector<int> permutation_table;
	static std::vector<float> gradients;
	static std::vector<int> gen_seq(int end_n); // Generates a seq. 0 to end_n

	static inline int rand_int(int min, int max)
	{
		static std::default_random_engine ran{static_cast<unsigned>(
		    std::chrono::system_clock::now().time_since_epoch().count())};
		return std::uniform_int_distribution<>{min, max}(ran);
	}
	static inline float rand_gradient() { return rand_int(0, 1000) / 1000.0; }

	// Shuffles the sequence to create a randomly distributed list of integers
	// This should reduce patterns and biases
	static void shuffle_permutations(std::vector<int>& table, int n_times);
	static void swap_permutations(std::vector<int>& table, int a_idx, int b_idx);

	// Generates a vector of random values ranging from 0.001 to 1.0
	static std::vector<float> gen_gradients(int end_n);
};

#endif // PLOT_FN_H
