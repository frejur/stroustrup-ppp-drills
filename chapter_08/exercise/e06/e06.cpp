#include "../../lib/std_lib_facilities.h"

// Chapter 8, Exercise 6. Reverse the order of vector<string>.

// Write two versions of a function that reverses the order of a vector<string>:
// 1. Returns a new vector, the original vector is unchanged.
// 2. Changes the order of the original vector.

using std::string;

vector<string> reverse_new(const vector<string>& v) {
	vector<string> u{};
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

void reverse_mod(vector<string>& v) {
	if (v.size() < 2) {
		return;
	}
	for (int i = 0; i < (v.size() / 2); ++i) {
		swap(v[i], v[v.size() - 1 - i]);
	}
};

vector<string> get_strings()
{
	vector<string> string_v{};
	std::cout << "Enter words, finish with ';'" << '\n';

	std::string s{};
	while (std::cin >> s)
	try {
		if (s == ";" && string_v.size() > 0) {
			break;
		}

		// scan until ';', clear buffer and add back ';' if found
		string s2{ "" };
		for (char c : s) {
			if (c == ';') {
				while(std::cin.get(c) && c != '\n') {}
				std::cin.putback(' ');
				std::cin.putback(';');
				break;
			}
			s2 += c;
		}
		if (s2.size() > 0) {
			string_v.push_back(s2);
		}
	}
	catch (std::exception e) {
		std::cerr << "Error: " << e.what() << '\n';
	}
	catch (...) {
		error("Unknown error");
	}
	return string_v;
}

void print(const std::string& label, const vector<string>& string_v) {
	std::cout << label << ':' << '\n';
	if (string_v.size() == 0) {
		std::cout << "Empty" << '\n';
		return;
	}
	std::cout << "(";
	for (int i = 0; i < string_v.size(); ++i) {
		std::cout << ' ' << string_v.at(i);
		if (i == string_v.size() - 1) {
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
		<< "Reverse the order of words" << '\n';

	vector<string> strings{ get_strings() };

	print("Original", strings);
	std::cout << '\n';

	print("New reversed", reverse_new(strings));
	std::cout << '\n';

	print("Original again", strings);
	std::cout << '\n';

	reverse_mod(strings);
	print("Original reversed", strings);
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
