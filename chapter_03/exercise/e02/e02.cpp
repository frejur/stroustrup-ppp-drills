#include "../../lib/std_lib_facilities.h"

int main()
{
	std::cout <<
		"Please enter the number of miles you would like to convert to km:"
		<< '\n';
	double m{ 0 };

	while (std::cin >> m) {
		std::cout <<
			m << " miles = " << m * 1.609 << " kilometers" << '\n';
		std::cout <<
			"Please enter another number." << '\n';
	}
	std::cin.clear();
	std::cin.ignore();

	keep_window_open();

    return 0;
}
