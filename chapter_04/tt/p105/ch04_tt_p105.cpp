#include "../../lib/std_lib_facilities.h"

int main()
{
	constexpr double usd_rate{ 1.00 };
	constexpr double sek_rate{ 8.3033 };
	constexpr double gbp_rate{ 0.72213 };
	double amount = 1;
	char currency = ' ';
	std::cout << "Please enter an amount followed by a" <<
		" currency code ('u' for USD, 's' for SEK or, 'g' for GBP):\n";
	std::cin >> amount >> currency;
	std::string amount_str = to_string(amount) + " " + currency;
	if (currency == 'u') {
		std::cout << amount_str << " == " <<
			1 / usd_rate * sek_rate * amount << " sek\n";
		std::cout << amount_str << " == " <<
			1 / usd_rate * gbp_rate * amount << " gbp\n";
	} else if (currency == 's') {
		std::cout << amount_str << " == " <<
			1 / sek_rate * usd_rate * amount << " usd\n";
		std::cout << amount_str << " == " <<
			1 / sek_rate * gbp_rate * amount << " gbp\n";
	} else if (currency == 'g' ) {
		std::cout << amount_str << " == " <<
			1 / gbp_rate * usd_rate * amount << " usd\n";
		std::cout << amount_str << " == " <<
			1 / gbp_rate * sek_rate * amount << " sek\n";
	} else {
		std::cout << "Sorry, I'm not familiar with any currency called '" <<
			currency << "'\n";
	}

	keep_window_open();

	return 0;
}
