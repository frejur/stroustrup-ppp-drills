#include "../../lib/std_lib_facilities.h"
#include <string>

//	Exercise 8. Prompt for an integer value, output whether its odd / even.

int main()
{
	std::cout <<
		"Please enter a number to determine if it's odd or even."
		<< '\n';

	int num{ 0 };
	while (true) {
		std::cin >> num;
		if (std::cin.fail()) {
			break;
		}

		std::string is_odd{ "is an odd number." };
		std::string is_even{ "is an even number." };

		std::cout << num << ' ' << ((num % 2 == 0) ? is_even : is_odd) << '\n';

		std::cout << "Keep entering numbers..." << '\n';
	}

	std::cin.clear();
	std::cin.ignore();

	keep_window_open();

    return 0;
}
