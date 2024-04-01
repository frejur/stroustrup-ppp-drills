#include "../../lib/help.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

/* Chapter 11, exercise 12 and 13. Reverse order.
 * 
 *          Two programs:
 *              e12. Produce a copy of a text file with the order of all
 *                   characters reversed, without storing all contents
 *                   in memory first.
 *              e13. Produce a copy of a text file with the order of all
 *                   words reversed, by first storing all contents in memory.
 *
 *          Prompts the user to 'run' either exercise.
 *          
 *          For each exercise:
 *              Reverses the original, then the copy.
 *              Compares the original to the reversed copy.
 */
//------------------------------------------------------------------------------

const std::string& quit_word()
{
	const static std::string q{"q"};
	return q;
}

const std::string& file_chars_original()
{
	const static std::string f{"data/abc.txt"};
	return f;
}

const std::string& file_words_original()
{
	const static std::string f{"data/count.txt"};
	return f;
}

const std::string& file_chars_reversed()
{
	const static std::string f{"data/abc_rev.txt"};
	return f;
}

const std::string& file_words_reversed()
{
	const static std::string f{"data/count_rev.txt"};
	return f;
}

const std::string& file_chars_reversed_copy()
{
	const static std::string f{"data/abc_rev_copy.txt"};
	return f;
}

const std::string& file_words_reversed_copy()
{
	const static std::string f{"data/count_rev_copy.txt"};
	return f;
}

//------------------------------------------------------------------------------

template<class T>
char* as_bytes(T& i)
{
	void* addr = &i;
	return static_cast<char*>(addr);
}

//------------------------------------------------------------------------------

void save_rev_ch_copy(const std::string& file_in, const std::string& file_out)
/*    Surely this is the most asinine way to reverse chars in a text file?
 *    Would it not be simpler and more performant to just chuck all the chars
 *    into a string?
 *    
 *    Well yes, only the book seems to imply there should be a way to solve
 *    this problem without first storing the entire contents of the text file
 *    in memory.
 *    
 *    At the same time, the book tells you to stay away from "clever" file open
 *    modes, and to only use binary when absolutely necessary. ¯\_(ツ)_/¯
 *    
 *    Why binary? Because linebreaks.
 */
{
	std::ifstream ifs{file_in, std::ios_base::binary};
	if (!ifs) {
		throw std::runtime_error("Could not open '" + file_in + "' for reading");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	// Truncate and insert each character at the start of the file,
	// shifting pre-existing characters by overwriting.
	std::fstream iofs{file_out,
	                  std::ios_base::binary | std::ios_base::trunc
	                      | std::ios_base::out | std::ios_base::in};
	if (!iofs) {
		throw std::runtime_error("Could not open '" + file_out
		                         + "' for writing");
	}
	iofs.exceptions(iofs.exceptions() | std::ios_base::badbit);

	char c;
	if (ifs.read(as_bytes(c), sizeof(char))) {
		iofs.write(as_bytes(c), sizeof(char));
	}

	int count = 1;
	while (ifs.read(as_bytes(c), sizeof(char))) {
		char temp;
		for (int i = count; i > 0; --i) {
			iofs.seekg(i - 1);
			iofs.read(as_bytes(temp), sizeof(char));
			iofs.seekp(i);
			iofs.write(as_bytes(temp), sizeof(char));
		}
		iofs.seekp(0);
		iofs.write(as_bytes(c), sizeof(char));

		++count;
	}
	iofs.close();
}
//------------------------------------------------------------------------------

void save_rev_w_copy(const std::string& file_in, const std::string& file_out)
{
	std::ifstream ifs{file_in};
	if (!ifs) {
		throw std::runtime_error("Could not open '" + file_in + "' for reading");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	char c;
	std::string chunk; // stores word / whitespace
	std::vector<std::string> contents;
	while (ifs.get(c), ifs) {
		if (help::isspace(c) || help::iscntrl(c)) {
			chunk = c;
			while (ifs.get(c), ifs) {
				if (!help::isspace(c) && !help::iscntrl(c)) {
					ifs.putback(c);
					break;
				}
				chunk.push_back(c);
			}
		} else {
			ifs.putback(c);
			ifs >> chunk;
		}
		contents.push_back(chunk);
	}

	if (contents.size() == 0) {
		throw std::runtime_error("The file '" + file_in + "' is empty.");
	}

	std::ofstream ofs{file_out};
	if (!ofs) {
		throw std::runtime_error("Could not open '" + file_out
		                         + "' for writing");
	}
	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

	for (int i = contents.size() - 1; i >= 0; --i) {
		ofs << contents[i];
	}
}

//------------------------------------------------------------------------------

void compare_files(const std::string& file_a, const std::string& file_b)
{
	std::ifstream ifs_a{file_a};
	if (!ifs_a) {
		throw std::runtime_error("Could not open '" + file_a + "' for reading");
	}
	ifs_a.exceptions(ifs_a.exceptions() | std::ios_base::badbit);

	std::ifstream ifs_b{file_b};
	if (!ifs_b) {
		throw std::runtime_error("Could not open '" + file_b + "' for reading");
	}
	ifs_b.exceptions(ifs_b.exceptions() | std::ios_base::badbit);

	char c_a, c_b;
	while (ifs_a.get(c_a), ifs_b.get(c_b), (ifs_a || ifs_b)) {
		if (!ifs_a || !ifs_b) {
			throw std::runtime_error("The stream for '"
			                         + (!ifs_a ? file_a : file_b)
			                         + "' ended prematurely.");
		}
		if (c_a != c_b) {
			std::stringstream ss;
			ss << "Read '" << c_a << "' from '" << file_a << "' but got '"
			   << c_b << "' from '" << file_b << "'";
			throw std::runtime_error("Read '" + ss.str());
		}
	}
}

//------------------------------------------------------------------------------

void run_reverse_chars()
{
	std::cout << "Reversing order of '" << file_chars_original() << "', saving"
	          << " copy to '" << file_chars_reversed() << "'...";
	save_rev_ch_copy(file_chars_original(), file_chars_reversed());
	std::cout << " DONE!" << '\n';

	std::cout << "Reversing order of '" << file_chars_reversed() << "', saving"
	          << " copy to '" << file_chars_reversed_copy() << "'...";
	save_rev_ch_copy(file_chars_reversed(), file_chars_reversed_copy());
	std::cout << " DONE!" << '\n';

	std::cout << "Comparing contents of '" << file_chars_original()
	          << "' with contents of '" << file_chars_reversed_copy() << "'...";
	compare_files(file_chars_original(), file_chars_reversed_copy());
	std::cout << " DONE!" << '\n';

	std::cout << '\n'
	          << "All clear!" << '\n'
	          << '\n'
	          << "Press <ENTER> to return to the main loop" << '\n';
	help::wait_for_enter();
}

void run_reverse_words()
{
	std::cout << "Reversing order of '" << file_words_original() << "', saving"
	          << " copy to '" << file_words_reversed() << "'...";
	save_rev_w_copy(file_words_original(), file_words_reversed());
	std::cout << " DONE!" << '\n';

	std::cout << "Reversing order of '" << file_words_reversed() << "', saving"
	          << " copy to '" << file_words_reversed_copy() << "'...";
	save_rev_w_copy(file_words_reversed(), file_words_reversed_copy());
	std::cout << " DONE!" << '\n';

	std::cout << "Comparing contents of '" << file_words_original()
	          << "' with contents of '" << file_words_reversed_copy() << "'...";
	compare_files(file_words_original(), file_words_reversed_copy());
	std::cout << " DONE!" << '\n';

	std::cout << '\n'
	          << "All clear!" << '\n'
	          << '\n'
	          << "Press <ENTER> to return to the main loop" << '\n';
	help::wait_for_enter();
}

//------------------------------------------------------------------------------

void print_options()
{
	std::cout << 'a' << '\t' << "Reverse the order of characters in a text file"
	          << '\n'
	          << 'b' << '\t' << "Reverse the order of words in a text file"
	          << '\n'
	          << quit_word() << '\t' << "Exit" << '\n';
}

//------------------------------------------------------------------------------

int main()
try {
	std::cout << "Reverse order of text files" << '\n' << '\n';

	std::string ln;
	while (ln != quit_word()) {
		std::cout << "Enter one of the characters listed below to continue:"
		          << '\n';
		print_options();
		std::getline(std::cin, ln);
		if (ln == "a") {
			run_reverse_chars();
		} else if (ln == "b") {
			run_reverse_words();
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
