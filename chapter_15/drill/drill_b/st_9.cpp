#include "drill_b.h"
#include <sstream>

namespace step_9 {

std::istream& operator>>(std::istream& is, Person& p)
{
	char l_par{};
	char r_par{};
	std::string fname;
	std::string lname;
	int age{};

	if (is >> l_par >> fname >> lname >> age >> r_par) {
		if (l_par != '(' || r_par != ')') {
			is.clear(std::ios_base::failbit);
		} else {
			p = {fname, lname, age};
		}
	}
	return is;
};

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	return os << "Name: \"" << p.first_name() << ' ' << p.last_name()
	          << "\", Age: " << p.age();
}

//------------------------------------------------------------------------------

void run()
{
	std::string inp;
	for (int count = 0;; ++count) {
		if (count == 0) {
			std::cout << info() << '\n';
			Person test{"Mickey", "Mouse", 39};
			std::cout << "Example: (" << test.first_name() << ' '
			          << test.last_name() << ' ' << test.age()
			          << ") gives:" << '\n';
			std::cout << "= " << test << '\n';
		}

		std::cout << drill::prompt << ' ';
		std::getline(std::cin, inp);
		if (inp == drill::quit_word()) {
			break;
		}
		std::stringstream ss{};
		ss.str(inp);
		while (ss)
			try {
				Person p;
				while (ss >> p) {
					std::cout << "= " << p << '\n';
				}
			} catch (const std::runtime_error& e) {
				std::cout << "Invalid input: " << e.what() << '\n';
				ss.str("");
				ss.clear();
				ss.ignore();
			} catch (...) {
				throw;
			}
		drill::print_quit_info();
		std::cout << '\n';
	}
}

} // namespace step_9
