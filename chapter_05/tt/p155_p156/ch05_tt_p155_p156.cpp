#include "../../lib/std_lib_facilities.h"

/*  A program for finding the lowest, highest, and average
	temperature values in a set of data.
	
	Page 155: Get this program to run. Check that our input
	really does produce that output. Try to "break" the program
	(i.e., get it to give wrong results) by giving it other
	input sets. What is the least amount of input you can give
	it to get it to fail?
	
	Page 156: Check some information sources to pick good
	values for the min_temp (the "minimum temperature") and
	max_temp (the "maximum temperature") constants for our
	program. Those values will determine the limits of
	usefulness of our program.
	*/

int main()
{
	constexpr float min_temp{ -459.67 };       // Absolute zero
	constexpr float max_temp{ 9941 };          // The sun

	vector<double> temps;                      // temperatures

	for (double temp; std::cin >> temp; )           // read and put into temps
		temps.push_back(temp);

	// any non numerical input breaks the loop and proceeds to
	// find the highest and lowest temp. and the sum

	double sum = 0;

	// default initial values of these variables (0) cause errors
	double high_temp = min_temp; // used to be 0
	double low_temp = max_temp;  // used to be 0
		
	for (int x : temps)
	{
		if (x > high_temp) high_temp = x;      // find high
		if (x < low_temp) low_temp = x;        // find low
		sum += x;                              // compute sum
	}
	// error (with default high and low initial values):
	// if all values are <0, the highest temp. will still be 0
	// if all values are >0, the lowest temp. will still be 0
	// error:
	// if vector is empty (user enters no values)
	// > high, low remain at initial values, sum is NaN (div. by 0)

	std::cout << "High temperature: " << high_temp << '\n';
	std::cout << "Low temperature: " << low_temp << '\n';
	std::cout << "Average temperature: " << sum / temps.size() << '\n';

	keep_window_open();

	return 0;
}
