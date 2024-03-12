#ifndef E06_E07_E10_MAIN_H
#define E06_E07_E10_MAIN_H
#include "help/help.h"
#include <iostream>
#include <string>
#include <vector>

namespace e6_7_10 {

constexpr char symbol_prompt{'>'};
constexpr char select_quit{'q'};
constexpr char select_test_roman{'a'};
constexpr char select_calc_decimal{'b'};
constexpr char select_calc_roman{'c'};
constexpr char select_test_calc_decimal{'d'};
constexpr char select_test_calc_roman{'e'};
constexpr char select_unknown{0};

inline const std::vector<std::string> program_options()
{
	static std::vector<std::string> options{
	    help::prepend_char(". Roman_int tests.", select_test_roman),
	    help::prepend_char(". Run the Calculator, decimal version.",
	                       select_calc_decimal),
	    help::prepend_char(". Run the Calculator, Roman numerals version.",
	                       select_calc_roman),
	    help::prepend_char(". Calculator tests, decimal version.",
	                       select_test_calc_decimal),
	    help::prepend_char(". Calculator tests, roman numerals version.",
	                       select_test_calc_roman),
	    help::prepend_char(". Quit", select_quit)};
	return options;
}

inline void print_hello()
{
	std::cout << "Roman numerals" << '\n' << '\n';
}

inline void print_goodbye()
{
	std::cout << "Bye!" << '\n';
}

inline void print_options()
{
	std::cout << "Enter one of the characters below to proceed:" << '\n';
	for (const std::string& o : program_options()) {
		std::cout << "  " << o << '\n';
	}
}
char get_selection();

} // namespace e6_7_10

#endif // E06_E07_E10_MAIN_H
