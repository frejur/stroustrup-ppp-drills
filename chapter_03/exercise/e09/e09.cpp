#include "../../lib/std_lib_facilities.h"
#include <string>

//	Exercise 9.
//	Prompt for a spelled-out number (string) and output the numeric version.
//	Range 0 - 4 can be 'translated', anything else outputs "not a number I know"

int main()
{
	std::cout <<
		"Please spell out a number and it may be interpreted."
		<< '\n';

	std::string num_str{ 0 };
	while (true) {
		std::cin >> num_str;
		if (std::cin.fail()) {
			break;
		}

		std::string output{ "not a number I know" };
		if (num_str == "zero") {
			output = "0";
		} else if (num_str == "one") {
			output = "1";
		} else if (num_str == "two") {
			output = "2";
		} else if (num_str == "three") {
			output = "3";
		} else if (num_str == "four") {
			output = "4";
		}

		std::cout << num_str << " is " << output << "!" << '\n';

		std::cout << "Give it another go!..." << '\n';
	}

	std::cin.clear();
	std::cin.ignore();

	keep_window_open();

    return 0;
}
