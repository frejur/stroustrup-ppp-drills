#include "../../lib/help.h"
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/* Chapter 11, exercise 15 and 16. Print numbers
 * 
 *          Two programs:
 *              e15. Reads whitespace-separated numbers from a text file and
 *                   outputs them in this format:
 *                       <field><field><field><field>
 *                       
 *                   Where each field contains a number in scientific notation,
 *                   and with a precision of 8.
 *                   Each field is 20 characters wide, and there's a maximum
 *                   of 4 fields per line.
 *                   
 *              e16. Reads whitespace-separated numbers from a text file and
 *                   outputs them on separate lines in ascending order.
 *                   If a number occurs multiple times, it is only output once
 *                   and the total count is written out next to it.
 *                   
 *                   For example:
 *                       6 3 5 7 4 3 3 4 6
 *                   
 *                   Would output:
 *                       3    3
 *                       4    2
 *                       5
 *                       6    2
 *                       7
 *
 *          Prompts the user to 'run' either exercise.
 */
//------------------------------------------------------------------------------

const std::string& quit_word()
{
	const static std::string q{"q"};
	return q;
}

const std::string& file_floating_point()
{
	const static std::string f{"data_e15/random_numbers.txt"};
	return f;
}

const std::string& file_formatted_copy()
{
	const static std::string f{"data_e15/format_numbers.txt"};
	return f;
}

const std::string& file_integers()
{
	const static std::string f{"data_e15/random_ints.txt"};
	return f;
}

const std::string& file_count_unique()
{
	const static std::string f{"data_e15/count_unique.txt"};
	return f;
}

//------------------------------------------------------------------------------

void save_numbers_in_cols(const std::string& file_in,
                          const std::string& file_out,
                          int num_cols,
                          int col_width,
                          int precision)
{
	if (num_cols < 1 || col_width < 1 || precision < 0) {
		throw std::runtime_error("Invalid arguments");
	}

	std::ifstream ifs{file_in};
	if (!ifs) {
		throw std::runtime_error("Could not open '" + file_in + "' for reading");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::ofstream ofs{file_out};
	if (!ofs) {
		throw std::runtime_error("Could not open '" + file_out
		                         + "' for writing");
	}
	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

	double n;
	int count = 0;
	bool add_trailing_endl = true;
	while (ifs >> n) {
		if (count == 0) {
			ofs << std::scientific << std::setprecision(precision);
		}
		ofs << std::setw(col_width) << n;
		if (count % num_cols == num_cols - 1) {
			ofs << '\n';
			add_trailing_endl = false;
		} else if (!add_trailing_endl) {
			add_trailing_endl = true;
		}
		++count;
	}
	if (add_trailing_endl) {
		ofs << '\n';
	}
}

void save_unique_numbers(const std::string& file_in,
                         const std::string& file_out,
                         int col_width)
{
	if (col_width < 1) {
		throw std::runtime_error("Invalid column width");
	}

	std::ifstream ifs{file_in};
	if (!ifs) {
		throw std::runtime_error("Could not open '" + file_in + "' for reading");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::ofstream ofs{file_out};
	if (!ofs) {
		throw std::runtime_error("Could not open '" + file_out
		                         + "' for writing");
	}
	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

	double n;
	std::vector<double> numbers;
	while (ifs >> n) {
		numbers.push_back(n);
	}

	if (numbers.size() == 0) {
		throw std::runtime_error("No numbers found in '" + file_in + "'.");
	}

	std::sort(numbers.begin(), numbers.end());

	int count = 0;
	std::stringstream ss;
	for (int i = 0; i <= numbers.size(); ++i) {
		if (i == numbers.size() || (i > 0 && numbers[i] != numbers[i - 1])) {
			ss.str("");
			ss << (numbers[i - 1] >= 0 ? " " : "") << numbers[i - 1];
			if (count > 1) {
				ss << std::setw((col_width >= ss.str().size()
				                     ? col_width - ss.str().size()
				                     : 0))
				   << "" << count;
			}
			ofs << ss.str() << '\n';
			count = 0;
		}
		++count;
	}
}

//------------------------------------------------------------------------------

void print_file_to_console(const std::string& file_name)
{
	std::ifstream ifs{file_name};
	if (!ifs) {
		throw std::runtime_error("Could not open '" + file_name
		                         + "' for reading");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	char c;
	while (ifs.get(c), ifs) {
		std::cout << c;
	}
}

//------------------------------------------------------------------------------

void run_format_numbers()
{
	std::cout << "Loading numbers from '" << file_floating_point()
	          << "', saving formatted copy to '" << file_formatted_copy()
	          << "'...";
	save_numbers_in_cols(file_floating_point(), file_formatted_copy(), 4, 20, 8);
	std::cout << " DONE!" << '\n';

	std::cout
	    << '\n'
	    << "Press <ENTER> to print out the contents of the generated file."
	    << '\n';
	help::wait_for_enter();

	std::cout << "Printing the contents of '" << file_formatted_copy()
	          << "' to console." << '\n'
	          << '\n';

	print_file_to_console(file_formatted_copy());
	std::cout << '\n' << "--- End of file --" << '\n';

	std::cout << '\n' << "Press <ENTER> to return to the main loop" << '\n';
	help::wait_for_enter();
}

void run_count_unique()
{
	std::cout << "Loading numbers from '" << file_integers() << "'...";

	std::cout << "Loading numbers from '" << file_integers()
	          << "', saving formatted copy to '" << file_count_unique()
	          << "'...";
	save_unique_numbers(file_integers(), file_count_unique(), 8);
	std::cout << " DONE!" << '\n';

	std::cout
	    << '\n'
	    << "Press <ENTER> to print out the contents of the generated file."
	    << '\n';
	help::wait_for_enter();

	std::cout << "Printing the contents of '" << file_count_unique()
	          << "' to console." << '\n'
	          << '\n';
	print_file_to_console(file_count_unique());
	std::cout << '\n' << "--- End of file --" << '\n';

	std::cout << '\n' << "Press <ENTER> to return to the main loop" << '\n';
	help::wait_for_enter();
}

//------------------------------------------------------------------------------

void print_options()
{
	std::cout << 'a' << '\t' << "Format numbers in columns" << '\n'
	          << 'b' << '\t' << "Count unique numbers" << '\n'
	          << quit_word() << '\t' << "Exit" << '\n';
}

//------------------------------------------------------------------------------

int main()
try {
	std::cout << "Presenting numbers" << '\n';

	std::string ln;
	while (ln != quit_word()) {
		std::cout << "Enter one of the characters listed below to continue:"
		          << '\n';
		print_options();
		std::getline(std::cin, ln);
		if (ln == "a") {
			run_format_numbers();
		} else if (ln == "b") {
			run_count_unique();
		} else if (ln != quit_word()) {
			std::cout << "Unknown command, please try again." << '\n' << '\n';
		}
	}

	std::cout << "Bye!" << '\n';
	return 0;
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cin.get();
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	std::cin.get();
	return 2;
}
