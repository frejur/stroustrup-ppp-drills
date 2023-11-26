#include "../../lib/std_lib_facilities.h"

// Chapter 8, Exercise 2. Pass-by-ref print vector.

// Write a function print() that takes two arguments:
// 1. A string called 'label'
// 2. A vector of <int>'s
// The function prints the vector to std::cout

// Own additions:
// - Ask for user input (Label -> Integers -> ';')

std::string get_label()
{
	std::string label{};
	std::cout << "Please enter a label" << '\n';
	std::cin >> label;
	return label;
}

vector<int> get_integers()
{
	vector<int> int_v{};
	std::cout << "Enter integers, finish with ';'" << '\n';

	char c{};
	while (std::cin >> c)
	try {
		if (int_v.size() > 0 && c == ';') {
			break;
		}

		int i{};
		if (isdigit(c)) {
			std::cin.putback(c);
			std::cin >> i;
			int_v.push_back(i);
		} else {
			error("Invalid input");
		}
	}
	catch (std::exception e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (...) {
		error("Unknown error");
	}
	return int_v;
}

void print(const std::string& l, const vector<int>& int_v) {
	std::cout
		<< "Label:   " << '\t' << l << '\n'
		<< "Integers:" << '\t' << '{' << '\n';
	for (int i : int_v) {
		std::cout
		<< "         " << '\t' << '\t' << i << '\n';
	}
	std::cout
		<< "         " << '\t' << '}' << '\n';
}

int main()
try
{
	std::cout
		<< "Labeled vector of integers (String and vector pass-by-ref)" << '\n';

	const std::string label{ get_label() };
	const vector<int> integers{ get_integers() };

	print(label, integers);

	std::cout << "Goodbye!" << '\n';
	keep_window_open();
	return 0;
}
catch (std::exception e) {
	std::cerr << "Error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	std::cerr << "Unknown error" << '\n';
	keep_window_open();
	return 2;
}
