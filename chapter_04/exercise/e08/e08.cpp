#include "../../lib/std_lib_facilities.h"

// Exercise 8, Exponential Rice
// There's this story about rice grains...
// It describes a number series that starts at 1 and doubles for each new term.
// Calculate at which point the number exceeds:
// 	* 1,000
// 	* 1,000,000
// 	* 1,000,000,000

int main()
{
	std::cout << "Let's count some rice!" << '\n';

	int grains{ 0 };
	int sq{ 0 };
	constexpr int max_start{ 1000 };
	int max_current{ max_start };
	std::string grain_str{ "grain" };
	for (int i = 1; i <=3; ++i) {
		while (grains < max_current) {
			++sq;
			if (sq == 1) {
				grains = 1;
			} else {
				grains *= 2;
				grain_str = "grains";
			}
			std::cout << "Square: " << sq << ' ' << '\t';
			std::cout << "Count: " << grains << ' ' << grain_str << '\n';
		}
		std::cout
			<< "---- Goal reached, at least: " << max_current << " grains"
			<< '\n';
		max_current *= 1000;
	}


	std::cout << "That's a lot of carbs!" << '\n';

	keep_window_open();

    return 0;
}
