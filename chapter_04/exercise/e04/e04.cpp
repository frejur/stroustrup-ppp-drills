#include "../../lib/std_lib_facilities.h"

// Exercise 4, Numbers guessing game.
// Ask the user to think of a number between 1 and 100.
// Ask a maximum of 7 questions trying to narrow down the correct number.

int main()
{
	std::cout << "Think of a number between 1 and 100." << '\n';

	char y{};
	do {
		if (y == 'y') {
			break;
		}
		std::cout << "Have you retained the number in memory? "
			<< "Enter 'y' to proceed." << '\n';
	} while (std::cin >> y);

	std::cout << "Let's start." << '\n';

	const std::string txt_greater {
		"Is the number you are thinking of greater than "
	};
	const std::string txt_less {
		"Is the number you are thinking of less than "
	};

	int round{ 1 };
	int upper{ 100 };
	int lower{ 1 };
	bool ask_greater{ false };
	int guess{ static_cast<int>(upper * 0.5) };

	char yn{};
	do {
		if (round == 8 || lower == upper) {
			break;
		}
		if (yn == 'y' || yn == 'n') {
			if (ask_greater) {
				if (yn == 'y') {
					lower = guess + 1;
				} else {
					upper = guess;
				}
			} else {
				if (yn == 'y') {
					upper = guess - 1;
				} else {
					lower = guess;
				}
			}
			if (lower + 1 == upper) {
				guess = lower;
				ask_greater = true;
			} else {
				guess = lower + static_cast<int>((upper - lower) * 0.5);
				ask_greater = !ask_greater;
			}
			++round;
			std::cin.putback('\0');
			continue;
		}
		std::cout << "Round " << round << ": ";
		if (ask_greater) {
			std::cout << txt_greater << guess << "?\n";
			continue;
		}
		std::cout << txt_less << guess << "?\n";
	} while (std::cin >> yn);

	std::cout << "The number you are thinking of is: " << guess << ".\n";

	keep_window_open();

	return 0;
}
