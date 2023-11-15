#include "../../lib/std_lib_facilities.h"

// Chapter 6, Exercise 9. Integers to digits
// Prompt for integer values with 1 - 4 digits.
// Split the values into individual digits and store them as <int>'s
// Write out the registered digits with their corresponding place values, eg:
// 123 -> "1 hundred and 2 tens and 3 ones"

//------------------------------------------------------------------------------

class Digit {
public:
	Digit(int num);
	std::string to_string();
private:
	int number{};
	int ones{};
	int tens{};
	int hundreds{};
	int thousands{};
	bool is_negative{};
};

Digit::Digit(int num) : number(num) {
	std::string digits_str{ std::to_string(num) };
	if (digits_str.front() == '-') {
		is_negative = true;
		digits_str = digits_str.substr(1, digits_str.size()-1);
	}
	for (int i = digits_str.size()-1; i >= 0 ; --i) {
		int d{ digits_str.at(i) - '0'};
		switch (digits_str.size() - i) {
		case 1:
			ones = d;
			break;
		case 2:
			tens = d;
			break;
		case 3:
			hundreds = d;
			break;
		case 4:
			thousands = d;
			break;
		default:
			break;
		}
	}
}

std::string Digit::to_string() {
	std::string s{ std::to_string(number) + " is" };
	if (number == 0) {
		return s + " zero.";
	}
	if (is_negative) {
		s += " Minus";
	}
	if (thousands > 0) {
		s += " " + std::to_string(thousands) + " thousand";
		if (thousands > 1 || thousands < -1) {
			s += 's';
		}
	}
	if (hundreds > 0) {
		if (number > 999 || number < -999) {
			s += " and";
		}
		s += " " + std::to_string(hundreds) + " hundred";
		if (hundreds > 1 || hundreds < -1) {
			s += 's';
		}
	}
	if (tens > 0) {
		if (number > 99 || number < -99) {
			s += " and";
		}
		s += " " + std::to_string(tens) + " ten";
		if (tens > 1 || tens < -1) {
			s += 's';
		}
	}
	if (ones > 0) {
		if (number > 9 || number < -9) {
			s += " and";
		}
		s+= " " + std::to_string(ones) + " one";
		if (ones > 1 || ones < -1) {
			s += 's';
		}
	}
	s += '.';
	return s;
}

int main()
{
	std::cout
		<< "Read digits and compose them into integers" << '\n'
		<< "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << '\n'
		<< "Please enter some integers ranging between -9999 to 9999." << '\n'
		<< '\n' << '\n';

	int input_i{ 0 };
	while (std::cin >> input_i) {
		if (-9999 > input_i || input_i > 9999) {
			std::cout << "Invalid range, skipping..." << '\n';
			continue;
		}
		Digit d{ input_i };
		std::cout << d.to_string() << '\n';
	}

	keep_window_open();

	return 0;
}
