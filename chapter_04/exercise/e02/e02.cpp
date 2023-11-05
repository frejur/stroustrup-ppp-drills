#include "../../lib/std_lib_facilities.h"

// Exercise 2.
// Write a program that prints out the 'median' of a vector of double's.
// The defintion of 'median':
// 	"A number where the amount of elements preceeding it is the same as
//	 the amount of elements superceeding it.
// 	 The median can be a number not contained in the original sequence."

int main()
{
	std::cout << "Enter a sequence of temperatures, enter any non numerical "
		<< "character to terminate and calculate the median." << '\n';

	vector<double> temps;
	for (double temp; std::cin >> temp; ) {
		temps.push_back(temp);
	}

	// Calculate median
	if (temps.size() < 2) {
		std::cerr << "Cannot proceed with less than two temperatures" << '\n';
	} else {
		sort(temps);
		double median_pos{ temps.size() * 0.5 };
		int median_pos_fl{ static_cast<int>(std::floor(median_pos)) };
		double median{ temps[median_pos_fl] };
		if ((float)median_pos == median_pos_fl) {
			median = (temps[median_pos_fl - 1] + temps[median_pos_fl]) * 0.5;
		}
		std::cout << "The median is: " << median << '\n';
	}

	keep_window_open();
	return 0;
}
