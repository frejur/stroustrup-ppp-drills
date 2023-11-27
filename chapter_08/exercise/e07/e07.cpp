#include "../../lib/std_lib_facilities.h"

// Chapter 8, Exercise 7 and 8. Order names by age.

// Prompt for a list of names, store in a vector.
// Prompt for the age of all names, store in a vector.
// Sort the name vector alphabetically, sort the age vector accordingly.
// Print the name-age pairs.

using std::string;

void swap(int& a, int& b) {
	int temp{ a };
	a = b;
	b = temp;
}

void swap(string& a, string& b) {
	string temp{ a };
	a = b;
	b = temp;
}

void clear_buffer() {
	char c{};
	while(std::cin.get(c) && c != '\n') {}
}

vector<string> get_names()
{
	vector<string> string_v{};
	std::cout << "Enter the names of some people, finish with ';'" << '\n';

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
				clear_buffer();
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

vector<int> get_ages(const vector<string>& names) {
	// assumes names is not empty
	vector<int> int_v{};
	if (names.size()==1) {
		std::cout << "How old is " << names.front() << '?' << '\n';
	} else {
		std::cout
			<< "How old are they? Let's start with " << names.front() << '\n';
	}

	int age{};
	char c{};
	while (std::cin >> c)
	try {
		if (!isdigit(c)) {
			error("Bad input");
		} else {
			std::cin.putback(c);
			std::cin >> age;
		}

		if (age <= 0) {
			error("Invalid age");
		}

		int_v.push_back(age);

		if (int_v.size() < names.size()) {
			std::cout
				<< "So " << names.at(int_v.size() - 1) << " is " << age
				<< ", what about " << names.at(int_v.size()) << '?'
				<< '\n';
		} else {
			break;
		}
	}
	catch (std::exception e) {
		std::cerr << "Error: " << e.what() << '\n';
		clear_buffer();
	}
	catch (...) {
		error("Unknown error");
	}

	std::cout << "All ages were registered." << '\n';
	return int_v;
}

int find_element(const string& s,
                 const vector<string>& unsorted,
                 const vector<string>& sorted) {
	int idx{ -1 }; // no match
	for (int i = 0; i < sorted.size(); ++i) {
		if (unsorted.at(i) != sorted.at(i) && s == unsorted.at(i)) {
			idx = i;
			break;
		}
	}
	return idx;
}

void print(
	// assumes both vectors are the same size
	const std::string& label,
	const vector<string>& string_v,
	const vector<int>& int_v)
{
	std::cout << label << ':' << '\n';
	if (string_v.size() == 0) {
		std::cout << "Empty" << '\n';
		return;
	}
	for (int i = 0; i < string_v.size(); ++i) {
		std::cout << int_v.at(i) << '\t' << '\t' << string_v.at(i) << '\n';
	}
	std::cout << '\n';
}

void sort_by(vector<int>& int_v, vector<string>& str_v)
{
	vector<string> unsorted{ str_v };
	std::sort(str_v.begin(), str_v.end());
	int i{ 0 };
	while (true) {
		// skip to first non-checked or return
		while (unsorted.at(i) == str_v.at(i)) {
			if (i == int_v.size() - 1) {
				return;
			}
			++i;
		}
		int match{ find_element(str_v.at(i), unsorted, str_v) };
		if (match == -1) {
			error("Could not find element of unsorted in sorted");
		}

		if (unsorted.at(match) != str_v.at(match)) {
			if (unsorted.at(i) != str_v.at(i)) {
				swap(int_v.at(i), int_v.at(match));
				swap(unsorted.at(i), unsorted.at(match));
				i = match;
				continue;
			}
		}

		i = 0;
	}
}

int main()
try
{
	std::cout
		<< "Name-age pairs (Sort vectors with shared indexes)" << '\n';

	vector<string> names{ get_names() };

	vector<int> ages{ get_ages(names) };

	// Test A
	// vector<string> names{ "Bill", "Bill", "Albert", "Jim", "Albert", "Jim" };
	// vector<int> ages{ 12, 20, 5, 30, 7, 8 };

	// Test B
	// vector<string> names{
	// 	"May", "Jane", "Lubor", "Steve", "Steve", "Noah", "Lane", "Prospero" };
	// vector<int> ages{ 12, 32, 44, 22, 53, 65, 76, 87 };

	print("Unsorted", names, ages);

	sort_by(ages, names);

	print("Sorted by name", names, ages);

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
