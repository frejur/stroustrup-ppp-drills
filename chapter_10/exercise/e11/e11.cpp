#include "e11.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdexcept>

// Chapter 10, Exercise 11. The sum of whitespace-separated integers

int main()
try {
	std::cout << "Enter any character to sum up the numbers in the file: '"
	          << e11::file_path_numbers() << "'" << '\n';
	char c = 0;
	while (std::cin.get(c) && c != '\n') {
		/* clear buffer */
	}

	std::vector<int> numbers{e11::ints_from_file(e11::file_path_numbers())};
	int sum = 0;
	for (int n : numbers) {
		sum += n;
	}

	std::cout << "The sum is: " << sum << '\n';

	std::cout << '\n' << "Press <ENTER> to exit" << '\n';
	std::cin.get();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
} catch (...) {
	std::cerr << "Unknown error" << '\n';
}

std::vector<int> e11::ints_from_file(const std::string& file_path)
{
	std::ifstream ifs{file_path};
	if (!ifs) {
		throw std::runtime_error("Could not load file: '" + file_path + "'");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::vector<int> numbers;
	char c = 0;
	int n;
	while (ifs >> c) {
		if (help::isdigit(c) || c == '-') {
			ifs.putback(c);
			if (ifs >> n) {
				if (ifs.get(c)) {
					if (help::isspace(c)) {
						numbers.push_back(n);
					}
					ifs.putback(c);
				}
			} else {
				ifs.clear();
				ifs.ignore();
			}
		}
	}
	return numbers;
}
