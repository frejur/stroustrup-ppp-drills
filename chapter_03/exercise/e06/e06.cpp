#include "../../lib/std_lib_facilities.h"

//	Exercise 6. Prompt for 3 integer values, output sorted ascending.

int main()
{
	std::cout <<
		"Please enter three numbers to sort them."
		<< '\n';

	int val01{ 0 };
	int val02{ 0 };
	int val03{ 0 };

	while (std::cin >> val01 >> val02 >> val03) {

		int low{ val01 }; // Assume sorted
		int mid{ val02 };
		int high{ val03 };

		if (val01 > val02 && val01 > val03) {
			high = val01;
			low = val03;
		} else if (val02 > val03) {
			high = val02;
			mid = val03;
		}

		if (low > mid) {
			int temp{ mid };
			mid = low;
			low = temp;
		}

		std::cout << "Sorted: " << low << ", " << mid << ", " << high << '\n';
		std::cout << "Keep entering numbers to sort them..." << '\n';
	}
	std::cin.clear();
	std::cin.ignore();

	keep_window_open();

    return 0;
}
