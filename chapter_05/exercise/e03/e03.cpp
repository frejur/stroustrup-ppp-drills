#include "../../lib/std_lib_facilities.h"

// Exercise 3. Celsius to Kelvin, caller throws error below absolute zero.

static constexpr char DEG{ '\370' };
static constexpr double ABS_ZERO{ -273.15 };
static const std::string ABS_ZERO_ERROR_MSG{
	"Invalid argument to ctok(), value is below absolute zero"
};

double ctok(double c)
{
	double k = c + 273.15;
	return k;
}

int main()
try {
	std::cout
		<< "Enter a temperature value in degrees Celsius "
		<< "to convert it into Kelvin" << '\n' << '\n'
		<< "With absolute zero being at " << ABS_ZERO << DEG << "C, "
		<< "the program will throw an error " << '\n'
		<< "for any input below that value."
		<< '\n' << '\n';
	double c = 0;
	std::cin >> c;
	if (c < ABS_ZERO) {
		error("CALLER says \"" + ABS_ZERO_ERROR_MSG + '"');
	}
	double k = ctok(c);
	std::cout << c << DEG << "C = " << k << 'K' << '\n';

	keep_window_open();
	return 0;
}
catch (std::exception e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
