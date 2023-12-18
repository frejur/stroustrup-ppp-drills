#include <exception>
#include <iostream>
#include "money/money.h"

/* Chapter 9, Exercise 14 - 16. Money class.
 *
 * Design and implement a Money class (Merged exercises 14 to 16)
 *
 * The monetary amount should be:
 *   Represented as the number of centesimal monetary units.
 *   Stored in a variable of type <long>.
 *
 * The result of any calculation is accurate to the last centesimal unit,
 * through the use of rounding ( x < 0.5 = 0, x >= 0.5 = 1).
 *
 * Input and output should be represented as the 'cents' divided by 100
 * followed by the currency:
 *   <Floating-point-literal><CURRENCY>
 *   e.g. '123.45USD' or '67.89EUR'
 *
 * The currency (Class enum) is supplied on intialization.
 * Implement the ostream '<<' and istream '>>' operators accordingly.
 *
 * Only allow initialization by floating-point value if the given number can
 * be exactly represented as a number of centesimal units.
 *
 * Implement a conversion table for the included Currencies.
 *
 * When implementing the arithmetic operators, and comparison operators:
 *   Money * Money is not allowed.
 *   Convert the operands to the same currency before calculating.
 */

using namespace Money_lib;

int main()
try {
	std::cout
		<< "Money class" << '\n' << '\n'
		<< "Press <ENTER> to run a series of tests" << '\n';
	std::cin.get();

	Monetary_math_session s{};
	s.add_currency({ Currency_ID::EUR, "Euros", "EUR" });
	s.add_currency({ Currency_ID::JPY, "Japanese Yen", "JPY" });
	s.add_exchange_rate(Currency_ID::USD, Currency_ID::EUR, 0.91756953);
	s.add_exchange_rate(Currency_ID::JPY, Currency_ID::USD, 0.0070300116);
	while (s == true) {
		std::cout << "m" << '\n';
		Money m{ s.new_money(Currency_ID::USD, 1.0) };
		std::cout << "m2" << '\n';
		Money m2{ s.new_money(Currency_ID::JPY, (long)5000) };
		std::cout << "m3" << '\n';
		Money m3{ (m + m2) };
		std::cout << "result" << '\n';
		std::cout << m3.amount();
		break;
	}

	std::cout << '\n'
		<< "All tests passed without terminating the program pre-maturely!"
		<< '\n' << '\n';

	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
	return 0;
}
catch (std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
	return 1;
}
catch (...) {
	std::cerr << "Error: Unknown error" << '\n';
	std::cout << "Enter any key to exit" << '\n';
	std::cin.get();
	return 2;
}
