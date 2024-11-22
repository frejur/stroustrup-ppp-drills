#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

/* Chapter 11, exercise 9. Text <-> Binary conversion
 * 
 *          Two programs:
 *              1. Convert text file to binary
 *              2. Convert binary file to text
 *
 *          Test by comparing a text file converted to binary
 *          and back to text with the original.
 *
 *          Size of <int> is NOT equal to size of <char>.
 *          That's really the only aspect that's been changed
 *          from the example outlined in the book."
 */

//------------------------------------------------------------------------------

const std::string& file_original()
{
	static const std::string f{"data_e09/abc.txt"};
	return f;
}
const std::string& file_to_bin()
{
	static const std::string f{"data_e09/abc_bin.txt"};
	return f;
}

const std::string& file_to_txt()
{
	static const std::string f{"data_e09/abc_txt.txt"};
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

void txt_to_bin(const std::string& file_in, const std::string& file_out)
{
	std::ifstream ifs{file_in};
	if (!ifs) {
		throw std::runtime_error("Could not open '" + file_in + "' for reading");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::ofstream ofs{file_out, std::ios_base::binary};
	if (!ofs) {
		throw std::runtime_error("Could not open '" + file_out
		                         + "' for reading");
	}
	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

	for (char c; ifs.get(c), ifs;) {
		if (!ofs.write(as_bytes(c), sizeof(char))) {
			throw std::runtime_error("Write error");
		}
	}
}
void bin_to_txt(const std::string& file_in, const std::string& file_out)
{
	std::ifstream ifs{file_in, std::ios_base::binary};
	if (!ifs) {
		throw std::runtime_error("Could not open '" + file_in + "' for reading");
	}
	ifs.exceptions(ifs.exceptions() | std::ios_base::badbit);

	std::ofstream ofs{file_out};
	if (!ofs) {
		throw std::runtime_error("Could not open '" + file_out
		                         + "' for reading");
	}
	ofs.exceptions(ofs.exceptions() | std::ios_base::badbit);

	for (char c; ifs.read(as_bytes(c), sizeof(char));) {
		if (ofs << c) {
			std::runtime_error("Write error");
		}
	}
}
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

int main()
try {
	std::cout << "Convert text to binary, and back to text" << '\n'
	          << '\n'
	          << "Press any key to continue." << '\n';
	for (char c; std::cin.get(c), c != '\n';) {
		/* wakka wakka */
	}

	std::cout << "Converting '" << file_original() << "' to binary, saving to '"
	          << file_to_bin() << "'...";
	txt_to_bin(file_original(), file_to_bin());
	std::cout << " DONE!" << '\n';

	std::cout << "Converting '" << file_to_bin() << "' to text, saving to '"
	          << file_to_txt() << "'...";
	bin_to_txt(file_to_bin(), file_to_txt());
	std::cout << " DONE!" << '\n';

	std::cout << "Comparing contents of '" << file_original()
	          << "' with contents of '" << file_to_txt() << "'...";
	compare_files(file_original(), file_to_txt());
	std::cout << " DONE!" << '\n';

	std::cout << '\n'
	          << "All clear!" << '\n'
	          << '\n'
	          << "Press any key to exit." << '\n';
	std::cin.get();
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
