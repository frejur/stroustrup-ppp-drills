#include "e05.h"
#include "help/helpers.h"
#include <exception>
#include <iostream>

/* Chapter 10, Exercise 5: Write the function print_year() mentioned in 10.11.2
 * 
 * Note: The Book does not define exactly what print_year() should do.
 *
 * This program groups the temperature readings by month > day > hour before
 * printing them.
 *
 * It also generates random testing data before printing and stores it in a
 * text file.
 *
 * The following classes described in the Book had to be (re-)implemented:
 * - Reading
 * - Day
 * - Month
 * - Year
 *
 * Then print functions had to be implemented not only for Year, but also for:
 * - Month
 * - Day
 * 
 * The Date class from Chapter 9 exercise 11 is used for generating,
 * validating and formatting data.
 */

int main()
try {
	print_hello(std::cout);

	for (;;) {
		print_generate(std::cout);
		help::wait_for_enter();

		std::cout << "Generating values... ";
		Year_range y{1970, 2000};
		Freq_range fy{0.2, 0.3};
		Freq_range fm{0.5, 1};
		Freq_range fd{0.1, 0.4};
		Freq_range fh{0.1, 0.2};
		Temperature_range tr{-20, 30};
		std::vector<tmpr::Year> out_years{
		    generate_random_readings(y, fy, fm, fd, fh, tr)};
		std::cout << "DONE!" << '\n';

		std::cout << "Writing to '" << file_path() << "'... ";
		write_readings_to_file(file_path(), out_years);
		std::cout << "DONE!" << '\n' << '\n';

		print_read(std::cout);
		help::wait_for_enter();

		std::cout << "Reading from '" << file_path() << "'... ";
		std::vector<tmpr::Year> in_years{load_readings_from_file(file_path())};
		std::cout << "DONE!" << '\n' << '\n';

		print_compare(std::cout);
		help::wait_for_enter();

		std::cout << "Comparing generated vs. extracted values..." << '\n';
		std::cout << "Number of years: " << out_years.size()
		          << " == " << in_years.size() << "... ";
		if (out_years.size() != in_years.size()) {
			throw std::runtime_error("Year vector size mismatch");
		}
		std::cout << "DONE!" << '\n';

		for (int y = 0; y < out_years.size(); ++y) {
			std::cout << "Year '" << out_years[y].year << "' == Year '"
			          << in_years[y].year << "'... ";
			if (out_years[y] != in_years[y]) {
				years_are_eq(out_years[y], in_years[y], true);
			}
			std::cout << "DONE!" << '\n';
		}
		std::cout << '\n';

		print_display(std::cout);
		help::wait_for_enter();

		// Add empty year for testing
		tmpr::Year empty_y;
		empty_y.year = out_years.back().year + 1;
		out_years.push_back(empty_y);

		for (const tmpr::Year& py : out_years) {
			tmpr::print_year(std::cout, py);
		}
		std::cout << '\n' << "DONE!" << '\n' << '\n';

		print_save(std::cout);
		help::wait_for_enter();

		std::cout << "Saving to '" << file_path_formatted() << "'... ";
		write_formatted_readings_to_file(file_path_formatted(), out_years);
		std::cout << "DONE!" << '\n' << '\n';
	}

	print_goodbye(std::cout);
	std::cin.get();

	return 0;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
