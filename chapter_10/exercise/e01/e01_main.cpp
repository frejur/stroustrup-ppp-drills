#include "e01.h"
#include <exception>
#include <iostream>

/* Chapter 10, Exercise 1: Write a program that reads in numbers from a
 * whitespace-separated text file and calculates the sum of said values
 * 
 * Differences from the exercise described in the book:
 *     - Reads in floating-point values instead of integers
 */

int main()
try {
	print_hello(std::cout);
	std::cin.get();

	std::vector<double> values{ read_values_from_ifstream(input_file_path()) };
	double sum{ sum_of_values(values) };

	print_sum(std::cout, sum, values.size());
	print_expected(std::cout, expected_sum, expected_count);

	std::cout << '\n';
	if (sum == expected_sum && values.size() == expected_count) {
		print_success(std::cout);
	} else {
		print_failure(std::cout);
	}

	std::cout << '\n';
	print_goodbye(std::cout);
	std::cin.get();

	return 1;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 0;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
