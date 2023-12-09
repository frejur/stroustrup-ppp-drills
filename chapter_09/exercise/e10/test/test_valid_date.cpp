#include "test_date.h"
#include <string>

void test_is_valid_date(int y, Month m, int d, bool invert) {
	if (!is_date(y, m, d) * !invert) {
		std::cout
			<< "Checking if " << '(' << y << ", "
			<< m << ", " << d <<  ") is "
			<< (invert ? "NOT" : "indeed") << " a valid date..." << '\n';
		throw std::runtime_error(std::string((invert ? "Did not expect"
		                                             : "Expected"))
		                        + " a valid date");
	}
	std::cout << '(' << y << ", " << m << ", " << d << ") is "
	          << (invert ? "NOT" : "indeed")
	          << " a valid date" << '\n';
}
