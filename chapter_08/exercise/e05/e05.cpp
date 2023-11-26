#include "../../lib/std_lib_facilities.h"

// Chapter 8, Exercise 5. Reverse the order of vector<int>.

// Write two versions of a function that reverse the order of a vector<int>:
// 1. Returns a new vector, the original vector is unchanged.
// 2. Changes the order of the original vector.

vector<int> reverse_new(const vector<int>& v) {
	vector<int> u{};
	for (int i = v.size() - 1; i >= 0; --i) {
		u.push_back(v.at(i));
	}
	return u;
}

void swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

void reverse_mod(vector<int>& v) {
	if (v.size() < 2) {
		return;
	}
	for (int i = 0; i < (v.size() / 2); ++i) {
		swap(v[i], v[v.size() - 1 - i]);
	}
};



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
int main()
try
{
	std::cout
		<< "Reverse the order of integers" << '\n';

	vector<int> integers{ get_integers() };

	print("Original", integers);
	std::cout << '\n';

	print("New reversed", reverse_new(integers));
	std::cout << '\n';

	print("Original again", integers);
	std::cout << '\n';

	reverse_mod(integers);
	print("Original reversed", integers);
	std::cout << '\n';

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
