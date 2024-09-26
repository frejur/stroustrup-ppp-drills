#include "drill_b.h"
#include <sstream>

namespace step_1_to_4 {

std::istream& operator>>(std::istream& is, Person& p)
{
	char l_par{};
	char r_par{};
	std::string name;
	int age{};

	if (is >> l_par >> name >> age >> r_par) {
		if (l_par != '(' || r_par != ')') {
			is.clear(std::ios_base::failbit);
		} else {
			p.name = name;
			p.age = age;
		}
	}
	return is;
};

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	return os << "Name: \"" << p.name << "\", Age: " << p.age;
}

//------------------------------------------------------------------------------

void run()
{
	std::string inp;
	for (int count = 0;; ++count) {
		if (count == 0) {
			std::cout << info() << '\n';
			Person test{"Goofy", 63};
			std::cout << "Example: (" << test.name << ' ' << test.age
			          << ") gives:" << '\n';
			std::cout << "= " << test << '\n';
		}

		std::cout << drill::prompt << ' ';
		std::getline(std::cin, inp);
		if (inp == drill::quit_word()) {
			break;
		}
		Person p;
		std::stringstream ss{};
		ss.str(inp);
		while (ss >> p) {
			std::cout << "= " << p << '\n';
		}
		drill::print_quit_info();
		std::cout << '\n';
	}
}

} // namespace step_1_to_4
