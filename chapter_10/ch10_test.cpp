#include "lib/std_lib_facilities.h"

void skip_to_int() {
	if (std::cin.fail()) {
		std::cin.clear();

		for (char ch; std::cin >> ch; ) {
			if (isdigit(ch) || ch == '-') {
				std::cin.unget();

				return;
			}
		}
	}

	throw std::runtime_error("no input");
}

int main() {
	std::cout << "Please enter an integer between 1 and 10" << std::endl;

	int n = 0;
	while (true) {
		if (std::cin >> n) {
			if (1 <= n && n <= 10)
				std::cout << "= " << n << std::endl;
			else
				std::cout << "Invalid range" << std::endl;
		}
		else {
			std::cout << "Not a number, try again" << std::endl;
			skip_to_int();
		}
	}

	keep_window_open();
	return 0;
}
