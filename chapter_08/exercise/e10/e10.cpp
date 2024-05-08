#include "../../lib/std_lib_facilities.h"

// Chapter 8, Exercise 10. Return largest element of a vector.

// A function maxv(v) that returns the largest element of vector v

// There's a lot of additional functions for generating random sequences
// which will be useful in later exercises

namespace CONST {
const std::string EXIT{ "end" };
}
//------------------------------------------------------------------------------

std::string buffer_until_eol() {
	std::string s{ "" };
	char c{};
	while(std::cin.get(c) && c != '\n') {
		s += c;
	}
	return s + c;
}

bool entered_exit() {
	return buffer_until_eol() == CONST::EXIT + '\n';
}

void swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

//------------------------------------------------------------------------------

void print_exit_cmd() {
	std::cout << "(Type '" << CONST::EXIT << "' to quit)";
}

void print_hint_numbers() {
	std::cout << "Hit <ENTER> to generate numbers. ";
	print_exit_cmd();
	std::cout << '\n';
}

void print_hint_max() {
	std::cout
		<< "Hit <ENTER> to get the largest item. ";
	print_exit_cmd();
	std::cout << '\n';
}

void print(const std::string& label, const vector<int>& int_v) {
	std::cout << label << ':' << '\n';
	if (int_v.size() == 0) {
		std::cout << "Empty" << '\n';
		return;
	}
	std::cout << "(";
	for (int i = 0; i < int_v.size(); ++i) {
		std::cout << ' ' << int_v.at(i);
		if (i == int_v.size() - 1) {
			std::cout << " )\n";
			break;
		}
		std::cout << ",";
		if ((i + 1) % 10 == 0) {
			std::cout << "\n ";
		}
	}
}

//------------------------------------------------------------------------------

// assumes max > min
int randnum(int min, int max) {;
	return min + randint(max - min);
}

vector<int> sequence(int min, int max, int n) {
	if (max < min) {
		error("Cannot generate sequence when min is greater than max");
	}
	if (n < 2 || n > max - min) {
		error("Too few / too many number of elements");
	}
	vector<int> seq{ min };
	int incr{ static_cast<int>((max - min) / (n-1.0) + 0.5) };
	for (int i = 1; i < n-1; ++i) {
		seq.push_back(min + incr * i);
	}
	seq.push_back(max);
	return seq;
}

void shuffle(vector<int> & v, int iterations) {
	if (v.size() < 3 || iterations < 1) {
		return; // don't bother
	}
	for (int i = 0; i < iterations; ++i) {
		for (int j = 0; j < v.size(); ++j) {
			int randidx{ (j + randnum(1, 3)) % (int)v.size() };
			swap(v.at(j), v.at(randidx));
		}
	}
}

//------------------------------------------------------------------------------

vector<int> get_numbers(bool& should_continue) {
	if (!should_continue) {
		return {};
	}
	print_hint_numbers();
	if (entered_exit()) {
		should_continue = false;
		return {};
	}
	int min{ randnum(20, 20 + randnum(10, 20)) };
	int max{ min + randnum(80, 160) };
	std::string label{
		"Generated sequence ("
		"min = " + std::to_string(min) + ", max = " + std::to_string(max) + ")"
	};

	vector<int> seq{ sequence(min, max, randnum(8, 16)) };
	shuffle(seq, 3);

	print(label, seq);
	std::cout << '\n';
	return seq;
}

//------------------------------------------------------------------------------

int maxi(int a, int b) {
	return (a > b) ? a : b;
}

// assumes v is not empty
int maxv(const vector<int>& v) {
	int max{ v.at(0) };
	for (int i = 1; i < v.size(); ++i) {
		max = maxi(max, v.at(i));
	}
	return max;
}

int get_max(bool& should_continue, const vector<int>& v) {
	if (!should_continue) {
		return {};
	}
	print_hint_max();
	if (entered_exit()) {
		should_continue = false;
		return {};
	}

	return maxv(v);
}

//------------------------------------------------------------------------------

int main()
try
{
    seed_randint(time(NULL)); // good enough
    std::cout
		<< "The greatest number (The max value of a given vector)"
		<< '\n';

	bool should_continue{ true }; // passed by ref, false will trigger exit
	while (should_continue) {
		vector<int> numbers{ get_numbers(should_continue) };

		int max{ get_max( should_continue, numbers) };

		if (should_continue) {
			std::cout
				<< "The largest element is: " << max
				<< '\n'	<< '\n';
		}
	}

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
