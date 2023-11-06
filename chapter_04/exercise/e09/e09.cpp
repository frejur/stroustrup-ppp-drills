#include "../../lib/std_lib_facilities.h"
#include <limits>

// Exercise 9, Exponential Rice revisited
// There's this story about rice grains...
// It describes a number series that starts at 1 and doubles for each new term.
// In the original story the series goes all the way up to 64 "squares", but
// reaching this number with built-in types leads to undefined behaviour.
// Calculate at which point the number exceeds the numerical limits of:
// 	<int>
// 	<double>

int main()
{
	std::cout << "Let's count some rice!" << '\n';

	int grains_int{ 0 };
	double grains_double{ 0 };
	unsigned long long grains_long { 0 }; // Enough on my system
	int sq{ 0 };
	constexpr int max_int{ std::numeric_limits<int>::max() };
	constexpr double max_double{ std::numeric_limits<double>::max() };
	bool max_int_reached{ false };
	bool max_double_reached{ false };
	std::string grain_str{ "grain" };
	for (int sq = 1; sq <= 64; ++sq) {
		if (sq == 1) {
			grains_int = 1;
			grains_double = 1;
			grains_long = 1;
		} else {
			grains_int *= 2;
			grains_double *= 2;
			grains_long *= 2;
			grain_str = "grains";
		}
		if (!max_int_reached && grains_long > max_int) {
			std::cout
				<< "---- " << "At this point the numeric limit of <int> "
				<< "has been exceeded." << '\n';
			max_int_reached = true;
		}
		if (max_double_reached && grains_long > max_double) {
			std::cout
				<< "---- " << "At this point the numeric limit of <double> "
				<< "has been exceeded." << '\n';
			max_double_reached = true;
		}
		std::string comp_int { grains_int == grains_long ? "TRUE" : "FALSE" };
		std::string comp_long { grains_long == grains_long ? "TRUE" : "FALSE" };
		std::cout
			<< "Square: " << sq << ' ' << '\t'
			<< "Count <int>: " << grains_int << ' ' << grain_str << '\t'
			<< "Count <double>: " << grains_double << ' ' << grain_str << '\t'
			<< "Count <long>: " << grains_long << '\n'
			<< '\t' << "Compare with long: " << '\t'
			<< "<int> "
			<< static_cast<unsigned long long>(grains_int) << " = "
			<< grains_long << " = " << comp_int << '\t'
			<< "<long> "
			<< static_cast<unsigned long long>(grains_double) << " = "
			<< grains_long << " = " << comp_long << '\n';
	}

	std::cout << "That's a lot of carbs!" << '\n';

	keep_window_open();

    return 0;
}
