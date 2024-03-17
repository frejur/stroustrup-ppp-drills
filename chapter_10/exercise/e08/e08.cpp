#include "e08.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

/* Chapter 10, Exercise 8. Concatenate files
 * 
 * Write a program that merges two files into one by appending the contents of
 * the first file to that of the second */

void e08::concat_files(const std::string& file_a,
                       const std::string& file_b,
                       const std::string& file_merged)
{
	std::ofstream ofs{file_merged};
	if (!ofs) {
		throw std::runtime_error("Could not create ostream for path: '"
		                         + file_merged + "'");
	}

	std::ifstream ifs_a{file_a};
	if (!ifs_a) {
		throw std::runtime_error("Could not load file: '" + file_a + "'");
	}
	ifs_a.exceptions(ifs_a.exceptions() | std::ios_base::badbit);

	std::ifstream ifs_b{file_b};
	if (!ifs_b) {
		throw std::runtime_error("Could not load file: '" + file_b + "'");
	}
	ifs_b.exceptions(ifs_b.exceptions() | std::ios_base::badbit);

	char c = 0;
	while (ifs_a.get(c)) {
		ofs << c;
	}

	c = 0;
	while (ifs_b.get(c)) {
		ofs << c;
	}
}

int main()
{
	std::cout << "Press any key to concatenate '" << e08::file_path_start()
	          << "' with '" << e08::file_path_end() << "'" << '\n';
	std::cin.get();
	char c = 0;
	while (std::cin.get(c) && c != '\n') {
		/* clear buffer */
	}

	e08::concat_files(e08::file_path_start(),
	                  e08::file_path_end(),
	                  e08::file_path_final());

	std::cout << '\n'
	          << "The contents of both files were joined and saved into '"
	          << e08::file_path_final() << "'" << '\n';

	std::cout << '\n' << "Press <ENTER> to exit" << '\n';
	std::cin.get();
}
