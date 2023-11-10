#include "../../lib/std_lib_facilities.h"

// Exercise 3. Celsius to Kelvin, callee throws error below absolute zero.

static constexpr char DEG{ '\370' };
static constexpr double ABS_ZERO_C{ -273.15 };
static const std::string ABS_ZERO_ERROR_MSG{
	"Invalid argument, value is below absolute zero"
};

double ctok(double c)
{
	if (c < ABS_ZERO_C) {
		error("ctok \"" + ABS_ZERO_ERROR_MSG + '"');
	}
	double k = c + 273.15;
	return k;
}

double ktoc(double k)
{
	if (k < 0) {
		error("ktoc() \"" + ABS_ZERO_ERROR_MSG + '"');
	}
	double c = k - 273.15;
	return c;
}
int main()
try {
	std::cout
		<< "Enter a temperature value in degrees Celsius or Kelvin "
		<< "to convert it" << '\n' << '\n'
		<< "With absolute zero being at " << ABS_ZERO_C << DEG << "C, "
		<< "the program will throw an error " << '\n'
		<< "for any input below that value."
		<< '\n' << '\n'
		<< "Enter a number followed by the unit 'c' or 'k':"
		<< '\n' << '\n';
	double temp{ 0 };
	double new_temp{ 0 };
	char unit{};

	std::cin >> temp >> unit;

	switch (unit) {
	case 'c':
		new_temp = ctok(temp);
		std::cout << temp << DEG << "C = " << new_temp << 'K' << '\n';
		break;
	case 'k':
		new_temp = ktoc(temp);
	std::cout << temp << "K = " << new_temp << DEG << 'C' << '\n';
		break;
	default:
		error("Invalid unit");
		break;
	}

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
