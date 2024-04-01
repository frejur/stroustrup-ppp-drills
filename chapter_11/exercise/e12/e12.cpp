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

void run_reverse_chars()
{
	std::cout << file_chars_original() << '\n';
	save_rev_ch_copy(file_chars_original(), file_chars_reversed());
	save_rev_ch_copy(file_chars_reversed(), file_chars_reversed_copy());
}

void run_reverse_words()
{
	std::cout << file_words_original() << '\n';
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
