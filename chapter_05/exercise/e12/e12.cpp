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

// Exercise 12:	Use a pre-defined vector of secret numbers. Only play once.
// Exercise 13:	Keep playing. Generate a random secret word for each round
//				of play.

// Additions:
// Generate semi random numbers (Without the user entering a seed number).
// Type 'peek' to cheat.

const std::string CHEAT_WORD{ "peek" };

bool is_unique(std::string s, char d) {
	if (s.size() == 0) {
		return true;
	}
	for (char c : s) {
		if (c == d) {
			return false;
		}
	}
	return true;
}

bool matches_cheat_word(std::string s) {
	// assumes v's size <= secret's size <= 4
	const std::string secret { CHEAT_WORD };
	for (int i = 0; i < s.size(); ++i) {
		if (s.at(i) != secret.at(i)) {
			return false;
		}
	}
	return true;
}

std::string gen_secret() {
	seed_randint(time(NULL)); // good enough
	std::string s{ "" };
	static const std::string num{ "0123456789" };
	std::string shuffled_num{ num };
	for (int i = 0; i < 32; ++i) {
		int temp_i_1{ randint(9) };
		int temp_i_2{ randint(9) };
		char temp_c { shuffled_num.at(temp_i_1) };
		shuffled_num.at(temp_i_1) = shuffled_num.at(temp_i_2);
		shuffled_num.at(temp_i_2) = temp_c;
	}
	int start{ randint(9) };
	for (int i = 0; i < 4; ++i) {
		s += shuffled_num.at((start + i)%9);
	}
	return s;
}

std::string get_guess() {
	std::string digits{};
	bool check_for_cheat{ false };
	while (digits.size() < 4) {
		char d{};
		if (!(std::cin >> d)) {
			error("Invalid input");
		}
		if (matches_cheat_word(digits + d)) {
			digits += d;
			check_for_cheat = true;
			continue;
		} else if (check_for_cheat == true) {
			error("Invalid input, not a digit");
		}
		if (!isdigit(d)) {
			error("Invalid input, not a digit");
		}
		if (!is_unique(digits, d)) {
			error("Invalid input, a digit may only appear once");
		}
		digits += d;
	}
	return digits;
}

vector<int> gen_matches(std::string guess, std::string secret) {
	// return a vector of {bulls, cows}
	// assumes: size of guess == size of secret
	if (guess == secret) {
		return {4, 0};
	}
	int bulls{ 0 }, cows{ 0 };
	for (int i = 0; i < guess.size(); ++i) {
		if (guess.at(i) == secret.at(i)) {
			++bulls;
		} else {
			for (int j = 0; j < (guess.size() - 1); ++j) {
				if (guess.at(i) == secret.at((i + j + 1) % guess.size())) {
					++cows;
					break;
				}
			}
		}
	}
	return {bulls, cows};
}

int main()
try {
	std::cout
		<< "Bulls and Cows" << '\n' << '\n'
		<< "Try to guess the secret number:" << '\n'
		<< "- It's a 4 digit number, where each digit only appears once."
		<< '\n' << '\n'
		<< "For each incorrect guess the player gets a hint of how" << '\n'
		<< "close they are - the number of matching digits expressed" << '\n'
		<< "in terms of \"bulls\" and \"cows\":" << '\n'
		<< "- A \"bull\" means a correct digit in the correct position." << '\n'
		<< "- A \"cow\" means the guessed number contains a matching" << '\n'
		<< "   digit but not at the position indicated by the player."
		<< '\n' << '\n';

	while (std::cin) {
		std::string secret{ gen_secret() };
		vector<int> matches{ 0, 0 }; // bulls and cows

		std::cout << "Guess the secret number!" << '\n';
		while (matches.at(0) < 4) {
			std::string guess{ get_guess() };

			if (guess == CHEAT_WORD) {
				std::cout << "- - - " << secret << " - - -" << '\n';
			} else {
				std::cout
					<< "Guess: " << guess.at(0) << guess.at(1) << guess.at(2)
					<< guess.at(3) << '\n';
				matches = gen_matches(guess, secret);
				std::cout
					<< "Bulls: " << matches.at(0) << " Cows: " << matches.at(1)
					<< '\n';
			}
		}
		std::cout << "You win!" << '\n' << '\n';
	}

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
