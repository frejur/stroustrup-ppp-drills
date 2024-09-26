#include "drill_b.h"
#include <sstream>

namespace step_5_to_7 {

static const std::string& banned_chars()
{
	static const std::string s{";:\"';[]*&^%$#@!"};
	return s;
}

void print_valid_parms()
{
	std::cout << "(!) The name may not contain the following chars:  "
	          << banned_chars() << '\n'
	          << "(!) The age must be a value between " << min_age << " and "
	          << max_age << '\n';
}

//------------------------------------------------------------------------------

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
			p = {name, age};
		}
	}
	return is;
};

std::ostream& operator<<(std::ostream& os, const Person& p)
{
	return os << "Name: \"" << p.name() << "\", Age: " << p.age();
}

//------------------------------------------------------------------------------

const std::string& Person::valid_name(const std::string& n)
{
	for (const char c : n) {
		for (const char banned : banned_chars()) {
			if (c == banned) {
				throw std::runtime_error("Invalid char '" + std::string{c}
				                         + "' in name");
			}
		}
	}
	return n;
};

int Person::valid_age(const int a)
{
	if (min_age > a || a > max_age) {
		throw std::runtime_error("Age must be in range: "
		                         + std::to_string(min_age) + " - "
		                         + std::to_string(max_age));
	}
	return a;
}

//------------------------------------------------------------------------------

void run()
{
	std::string inp;
	for (int count = 0;; ++count) {
		if (count == 0) {
			std::cout << step_1_to_4::info() << '\n';
			print_valid_parms();
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

} // namespace step_5_to_7
