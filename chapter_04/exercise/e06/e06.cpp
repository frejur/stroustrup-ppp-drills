#include "../../lib/std_lib_facilities.h"

// Exercise 6, Numerical / Spelled-out.
// Prompt for numericals: integers or spelled-out numbers in the range 1 - 10.
// Output the converted number, numerical gives spelled-out and vice versa.


int main()
{
	std::cout
		<< "Enter numbers to convert them from numerical to spelled-out "
		<< "versions and vice versa. Only numbers within the range of "
		<< "0 to 10 are supported." << '\n';

	vector<std::string> spelled_out {
		"zero", "one", "two", "three", "four", "five",
		"six", "seven", "eight", "nine", "ten"
	};

	std::string input_str{};
	while (std::cin >> input_str) {
		if (input_str.size() < 3) {
			for (int i = 0; i < input_str.size(); ++i) {
				std::cin.putback(input_str[i]);
			}
			int input_num{ 0 };
			std::cin >> input_num;
			if (0 <= input_num && input_num <= 10) {
				std::cout
					<< input_num << " = " << spelled_out[input_num] << '\n';
			}
			continue;
		}
		for (int i = 0; i < spelled_out.size(); ++i) {
			if (spelled_out[i] == input_str) {
				std::cout << spelled_out[i] << " = " << i << '\n';
				break;
			}
		}
	}

	keep_window_open();

    return 0;
}
