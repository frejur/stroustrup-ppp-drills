#include "std_lib_facilities.h"

namespace ch04_tt_p109
{
	int main()
	{
		constexpr double usd_rate{ 1.00 };
		constexpr double sek_rate{ 8.3033 };
		constexpr double gbp_rate{ 0.72213 };
		constexpr double jpy_rate{ 105.3808519261 };
		double amount = 1;
		char currency = ' ';
		cout << "Please enter an amount followed by a currency code ('u' for USD, 's' for SEK or, 'g' for GBP, 'j' for 'JPY'):\n";
		cin >> amount >> currency;
		string amount_str = to_string(amount) + " " + currency;
		switch (currency) {
		case 'u':
			cout << amount_str << " == " << 1 / usd_rate * sek_rate * amount << " sek (Swedish Kronor)\n";
			cout << amount_str << " == " << 1 / usd_rate * gbp_rate * amount << " gbp (British Pounds)\n";
			cout << amount_str << " == " << 1 / usd_rate * jpy_rate * amount << " jpy (Japanese Yen)\n";
			break;
		case 's':
			cout << amount_str << " == " << 1 / sek_rate * usd_rate * amount << " usd (US Dollars)\n";
			cout << amount_str << " == " << 1 / sek_rate * gbp_rate * amount << " gbp (British Pounds)\n";
			cout << amount_str << " == " << 1 / sek_rate * jpy_rate * amount << " jpy (Japanese Yen)\n";
			break;
		case 'g':
			cout << amount_str << " == " << 1 / gbp_rate * usd_rate * amount << " usd (US Dollars)\n";
			cout << amount_str << " == " << 1 / gbp_rate * sek_rate * amount << " sek (Swedish Kronor)\n";
			cout << amount_str << " == " << 1 / gbp_rate * jpy_rate * amount << " jpy (Japanese Yen)\n";
			break;
		case 'j':
			cout << amount_str << " == " << 1 / jpy_rate * usd_rate * amount << " usd (US Dollars)\n";
			cout << amount_str << " == " << 1 / jpy_rate * sek_rate * amount << " sek (Swedish Kronor)\n";
			cout << amount_str << " == " << 1 / jpy_rate * gbp_rate * amount << " gbp (British Pounds)\n";
			break;
		default:
			cout << "Sorry, I'm not familiar with a currency called '" << currency << "'\n";
		}
        return 0;
	}
}
