#include "e01.h"
#include "../../lib/help.h"

// Chapter 11, Exercise 1: Convert the contents of a text file into lowercase
//                         and save as a new file.

void e01::convert_file_to_lowercase(const std::string& source,
                                    const std::string& output)
{
	std::ifstream is{source};
	if (!is) {
		throw std::runtime_error("Could not load '" + source + "'");
	}
	is.exceptions(is.exceptions() | std::ios_base::badbit);

	std::ofstream os{output};
	if (!os) {
		throw std::runtime_error("Could not load '" + output + "' for writing");
	}
	os.exceptions(os.exceptions() | std::ios_base::badbit);

	char ch = 0;
	while (is.get(ch)) {
		if (help::isupper(ch)) {
			ch = tolower(ch);
		}
		os << ch;
	}
}

int main()
try {
	std::cout << "Enter any key to convert the contents of '"
	          << e01::file_path_source() << "' into lowercase." << '\n';
	help::wait_for_enter();

	std::cout << "Writing converted output to: '" << e01::file_path_output()
	          << "'...";
	e01::convert_file_to_lowercase(e01::file_path_source(),
	                               e01::file_path_output());
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
