#include "../../lib/std_lib_facilities.h"

// Exercise 6. Celsius < - > Fahrenheit.

static constexpr char DEG{ '\370' };
static constexpr double ABS_ZERO_C{ -273.15 };
static constexpr double ABS_ZERO_F{ -459.67 };
static const std::string ABS_ZERO_ERROR_MSG{
	"Invalid argument, value is below absolute zero"
};

double ctof(double c)
{
	if (c < ABS_ZERO_C) {
		error("ctof() \"" + ABS_ZERO_ERROR_MSG + '"');
	}
	return 9 / 5.0 * c + 32;
}

double ftoc(double f)
{
	if (f < ABS_ZERO_F) {
		error("ftoc() \"" + ABS_ZERO_ERROR_MSG + '"');
	}
	return (f - 32) * 5.0 / 9;
}
int main()
try {
	std::cout
		<< "Enter a temperature value in degrees Celsius or Fahrenheit "
		<< "to convert it" << '\n' << '\n'
		<< "With absolute zero being at " << ABS_ZERO_C << DEG << "C and "
		<< ABS_ZERO_F << "F, "
		<< "the program will throw an error " << '\n'
		<< "for any input below that value."
		<< '\n' << '\n'
		<< "Enter a number followed by the unit 'c' or 'f':"
		<< '\n' << '\n';
	double temp{ 0 };
	double new_temp{ 0 };
	char unit{};

	std::cin >> temp >> unit;

	switch (unit) {
	case 'c':
		new_temp = ctof(temp);
		std::cout << temp << DEG << "C = " << new_temp << 'F' << '\n';
		break;
	case 'f':
		new_temp = ftoc(temp);
	std::cout << temp << "F = " << new_temp << DEG << 'C' << '\n';
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
