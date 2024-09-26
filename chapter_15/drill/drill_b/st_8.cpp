#include "drill_b.h"
#include <sstream>
#include <vector>

namespace step_8 {

void print_persons(const std::vector<step_5_to_7::Person>& v)
{
	if (v.size() == 0) {
		std::cout << "No Persons on record." << '\n' << '\n';
		return;
	}

	std::cout << "Persons:" << '\n';
	for (const step_5_to_7::Person& p : v) {
		std::cout << '\t' << p << '\n';
	}
	std::cout << '\n';
}

void run()
{
	std::string inp;
	std::vector<step_5_to_7::Person> persons;
	for (int count = 0;; ++count) {
		if (count == 0) {
			std::cout << step_1_to_4::info() << '\n';
			step_5_to_7::print_valid_parms();
		}
		std::cout << drill::prompt << ' ';
		std::getline(std::cin, inp);
		if (inp == drill::quit_word()) {
			break;
		} else if (inp == drill::done_word()) {
			print_persons(persons);
		}
		std::stringstream ss{};
		ss.str(inp);
		while (ss)
			try {
				step_5_to_7::Person p;
				while (ss >> p) {
					std::cout << "= " << p << '\n';
					persons.push_back(p);
				}
			} catch (const std::runtime_error& e) {
				std::cout << "Invalid input: " << e.what() << '\n';
				ss.str("");
				ss.clear();
				ss.ignore();
			} catch (...) {
				throw;
			}
		if (persons.size() == 0) {
			drill::print_quit_info();
		} else {
			drill::print_done_or_quit_info();
		}
		std::cout << '\n';
	}
}
} // namespace step_8
