#include "std_lib_facilities.h"

namespace ch04_tt_p105
{
	int main()
	{
		constexpr double usd_rate{ 1.00 };
		constexpr double sek_rate{ 8.3033 };
		constexpr double gbp_rate{ 0.72213 };
		double amount = 1;
		char currency = ' ';
		cout << "Please enter an amount followed by a currency code ('u' for USD, 's' for SEK or, 'g' for GBP):\n";
		cin >> amount >> currency;
		string amount_str = to_string(amount) + " " + currency;
		if (currency == 'u') {
			cout << amount_str << " == " << 1 / usd_rate * sek_rate * amount << " sek\n";
			cout << amount_str << " == " << 1 / usd_rate * gbp_rate * amount << " gbp\n";
		} else if (currency == 's') {
			cout << amount_str << " == " << 1 / sek_rate * usd_rate * amount << " usd\n";
			cout << amount_str << " == " << 1 / sek_rate * gbp_rate * amount << " gbp\n";
		} else if (currency == 'g' ) {
			cout << amount_str << " == " << 1 / gbp_rate * usd_rate * amount << " usd\n";
			cout << amount_str << " == " << 1 / gbp_rate * sek_rate * amount << " sek\n";
		} else {
			cout << "Sorry, I'm not familiar with a currency called '" << currency << "'\n";
		}
		return 0;
	}
}