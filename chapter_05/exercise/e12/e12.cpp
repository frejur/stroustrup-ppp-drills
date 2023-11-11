#include "../../lib/std_lib_facilities.h"

// Exercise 12 and 13. Bulls and Cows

// The player tries to guess the secret number:
// A 4-digit number, where all digits must be unique.
// If the matching digits are in their right positions, they are "bulls".
// If they're in different positions, they are "cows".

// Example:
// The secret number is:	1 2 3 4
// Player guesses:			3 2 1 0
// Output:					Bulls: 1, Cows: 2

// Exercise 12: Use a pre-defined vector of secret numbers.
// Exercise 13: Generate a random secret word for each round of play.

int ctoi(char c) {
	return (int)c - 48;
}

bool is_unique(vector<int> v, int d) {
	if (v.size() == 0) {
		return true;
	}
	for (int i : v) {
		if (i == d) {
			return false;
		}
	}
	return true;
}

vector<int> get_guess() {
	vector<int> digit_v{};
	while (digit_v.size() < 4) {
		char d{};
		if (!(std::cin >> d)) {
			error("Invalid input");
		}
		if (!isdigit(d)) {
			error("Invalid input, not a digit");
		}
		if (!is_unique(digit_v, ctoi(d))) {
			error("Invalid input, a digit may only appear once");
		}
		digit_v.push_back(ctoi(d));
	}
	return digit_v;
}

int main()
try {
	std::cout
		<< "Bulls and Cows" << '\n' << '\n'
		<< "Try to guess the secret number:" << '\n'
		<< "- It's a 4 digit number, where each digit only appears once."
		<< '\n' << '\n'
		<< "For each incorrect guess the player gets a hint of how" << '\n'
		<< "close they are, the number of matching digits expressed" << '\n'
		<< "in terms of \"bulls\" and \"cows\":" << '\n'
		<< "- A \"bull\" means a correct digit in the correct position." << '\n'
		<< "- A \"cow\" means the guessed number contains a matching" << '\n'
		<< "   digit but not at the position indicated."
		<< '\n' << '\n';

	vector<int> guess{ get_guess() };

	std::cout
		<< "Guess: " << guess.at(0) << guess.at(1) << guess.at(2)
		<< guess.at(3) << '\n';

	keep_window_open();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
