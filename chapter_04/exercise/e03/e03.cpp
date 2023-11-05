#include "../../lib/std_lib_facilities.h"

// Exercise 3.
// Prompt the user for a series of distance values:
// "The distance between two cities along a given route"
// Store them in a vector<float>.
// Calcuate and output:
// 1. The sum of all distances.
// 2. The shortest distance.
// 3. The greatest distance.
// 4. The mean distance.

int main()
{
	std::cout << "Enter a series of distances, think of each value as the "
		<< "\"distance between two neighbouring cities along a given route\"."
		<< '\n';

	vector<double> dist_v;
	for (double d; std::cin >> d; ) {
		dist_v.push_back(d);
	}

	double sum{ 0 };
	double shortest{ 0 };
	double longest{ 0 };
	int count{ 0 };
	for (double d: dist_v) {
		if (d <= 0) {
			continue;
		}
		sum += d;
		++count;
		if (count == 1) {
			shortest = d;
			longest = d;
			continue;
		}
		if (d < shortest) {
			shortest = d;
		}
		if (d > longest) {
			longest = d;
		}
	}

	double mean{ sum };
	if (count > 1) {
		mean = sum / count;
	}

	std::cout << "The total distance: " << sum << '\n'
		<< "The shortest distance: " << shortest << '\n'
		<< "The longest distance: " << longest << '\n'
		<< "The mean distance (Any <= 0 values excluded): " << mean << '\n';

	keep_window_open();
	return 0;
}
