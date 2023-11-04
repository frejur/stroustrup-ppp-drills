#include "../../lib/std_lib_facilities.h"
#include <string>

//	Exercise 7. Prompt for 3 string values, output sorted ascending.

int main()
{
	std::cout <<
		"Please enter three words to sort them."
		<< '\n';

	std::string val01{ 0 };
	std::string val02{ 0 };
	std::string val03{ 0 };

	while (true) {
		std::cin >> val01 >> val02 >> val03;
		if (std::cin.fail()) {
			break;
		}
		std::string low{ val01 }; // Assume sorted
		std::string mid{ val02 };
		std::string high{ val03 };

		if (val01.compare(val02) > 0  && val01.compare(val03) > 0) {
			high = val01;
			low = val03;
		} else if (val02.compare(val03) > 0) {
			high = val02;
			mid = val03;
		}

		if (low.compare(mid) > 0) {
			std::string temp{ mid };
			mid = low;
			low = temp;
		}

		std::cout << "Sorted: " << low << ", " << mid << ", " << high << '\n';
		std::cout << "Keep entering words to sort them..." << '\n';
	}

	std::cin.clear();
	std::cin.ignore();

	keep_window_open();

    return 0;
}
