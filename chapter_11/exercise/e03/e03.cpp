#include "e03.h"
#include "../../lib/help.h"

/* Chapter 11, Exercise 3: A program that "disemvowels" a file,
 *             ergo "hello, world" becomes "hll, wrld".
 *
 * The tricky part is modifying the file in place, a topic not thoroughly
 * addressed in the book so far.
 * 
 * There is a section on p. 393 called "11.3.3 Positioning in files" which
 * briefly covers how to to change the read / write position of the fstream
 * using seekg(), but the same section also states that:
 *     "Many times, when you feel that you have to make a change to a file,
 *      the better solution is to produce a new file containing the change."
 *
 * In any case, the seekg() command is not described in detail so it doesn't
 * seem like the right tool for the job.
 *
 * Neither does the book explain how to:
 *   Write to a temporary file
 *     > Delete the original
 *         > Rename the temporary file to replace the original
 * 
 * This program store the entire contents of the original file in a stringstream,
 * then overwrites the former with the 'disemvoweled' version.
 */

//------------------------------------------------------------------------------

void e03::file_to_stringstream(const std::string& file_path,
                               std::stringstream& ss,
                               const std::string& banned_chars)
{
	std::ifstream is{file_path};
	if (!is) {
		throw std::runtime_error("Could not load '" + file_path + "'");
	}
	is.exceptions(is.exceptions() | std::ios_base::badbit);

	bool skip_banned = banned_chars.size() > 0;
	char c = 0;
	while (is.get(c)) {
		if (skip_banned && e03::isbanned(c, banned_chars)) {
			continue;
		}
		ss << c;
	}
}

void e03::stringstream_to_file(std::stringstream& ss,
                               const std::string& file_path,
                               const std::string& banned_chars)
{
	std::ofstream os{file_path};
	if (!os) {
		throw std::runtime_error("Could not load '" + file_path
		                         + "' for writing");
	}
	os.exceptions(os.exceptions() | std::ios_base::badbit);

	bool skip_banned = banned_chars.size() > 0;
	char c = 0;
	while (ss.get(c)) {
		if (skip_banned && e03::isbanned(c, banned_chars)) {
			continue;
		}
		os << c;
	}
}

//------------------------------------------------------------------------------

int main()
try {
	std::cout << "Enter any key to remove all vowels from '"
	          << e03::file_path_source() << "'." << '\n';
	help::wait_for_enter();

	std::cout << "Reading from '" << e03::file_path_source() << "'...";
	std::stringstream ss{};
	// e03::file_to_stringstream(e03::file_path_source(), ss, e03::vowels());
	e03::file_to_stringstream(e03::file_path_source(), ss);
	std::cout << " Done!" << '\n' << '\n';

	std::cout << "Writing changes to '" << e03::file_path_source() << "'...";
	// e03::stringstream_to_file(ss, e03::file_path_source());
	e03::stringstream_to_file(ss, e03::file_path_source(), e03::vowels());
	std::cout << " Done!" << '\n' << '\n';

	std::cout << "Press <ENTER> to exit" << '\n';
	help::wait_for_enter();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	help::wait_for_enter();
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	help::wait_for_enter();
}
