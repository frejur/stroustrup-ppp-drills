#include "../../lib/std_lib_facilities.h"

// Exercise 8. Bulls and Cows, Wordle edition

// Rewrite the program from Chapter 5, Exercise 12 - 13:
// The secret is a combination of letters rather than four numbers.

const std::string CHEAT_WORD{ "PEEK" };

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
	static const std::string abc{ "abcdefghijklmnopqrstuvwxyz" };
	std::string shuffled_abc{ abc };
	for (int i = 0; i < 64; ++i) {
		int temp_i_1{ randint(abc.size()-1) };
		int temp_i_2{ randint(abc.size()-1) };
		char temp_c { shuffled_abc.at(temp_i_1) };
		shuffled_abc.at(temp_i_1) = shuffled_abc.at(temp_i_2);
		shuffled_abc.at(temp_i_2) = temp_c;
	}
	int start{ randint(abc.size()-1) };
	for (int i = 0; i < 4; ++i) {
		s += shuffled_abc.at((start + i)%(abc.size()-1));
	}
	return s;
}

std::string get_guess() {
	std::string letters{};
	bool check_for_cheat{ false };
	while (letters.size() < 4) {
		char c{};
		if (!(std::cin >> c)) {
			error("Invalid input");
		}
		if (matches_cheat_word(letters + c)) {
			letters += c;
			check_for_cheat = true;
			continue;
		} else if (check_for_cheat == true) {
			error("Invalid input, not a lowercase letter");
		}
		if (!('a' <= c && c <= 'z' )) {
			error("Invalid input, not a lowercase letter");
		}
		if (!is_unique(letters, c)) {
			error("Invalid input, a letter may only appear once");
		}
		letters += c;
	}
	return letters;
}

vector<int> gen_matches(std::string guess, std::string secret) {
	// return a vector of {bulls, cows}
	// assumes: size of guess == size of secret
	// assumes: guess and secret contain no duplicate chars
	if (guess == secret) {
		return {4, 0};
	}
	int bulls{ 0 }, cows{ 0 };
	for (int i = 0; i < guess.size(); ++i) {
		for (int j = 0; j < (guess.size()); ++j) {
			if (guess.at(i) == secret.at(j)) {
				if (i == j) {
					++bulls;
				} else {
					++cows;
				}
				break;
			}
		}
	}
	return {bulls, cows};
}

int main()
try {
	std::cout
		<< "8u115 4nd C0w5!" << '\n' << '\n'
		<< "Try to guess the secret code:" << '\n'
		<< "- It's a combination of 4 unique letters."
		<< '\n' << '\n'
		<< "For each incorrect guess the player gets a hint of how" << '\n'
		<< "close they are - the number of matching letters expressed" << '\n'
		<< "in terms of \"bulls\" and \"cows\":" << '\n'
		<< "- A \"bull\" means a correct letter in the correct position." << '\n'
		<< "- A \"cow\" means the guessed code contains a matching" << '\n'
		<< "  letter but not at the position indicated by the player."
		<< '\n' << '\n';

	while (std::cin) {
		std::string secret{ gen_secret() };
		vector<int> matches{ 0, 0 }; // bulls and cows

		std::cout << "Guess the secret code (lowercase only)!" << '\n';
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
