#include "../share/money/money.h"
#include "my_win.h"
#include "parse_xrate.h"
#include <iostream>

// Chapter 16, exercise 8:
// Create an application that loads exchange rates from a text file and provides
// a GUI for converting a given amount of a selected currency 'A' to the
// corresponding amount in another selected currency 'B'.
//------------------------------------------------------------------------------

int e08()
{
	fl_color(0);

	std::vector<Money_lib::Currency> cur_v = read_currencies_from_file(
	    "txt_e08/currencies.txt");

	std::vector<Money_lib::Currency_pair> cur_p_v
	    = read_exchange_rates_from_file("txt_e08/xrates.txt");

	My_window win{{10, 10}, 640, 480, "I can do a thousand now", cur_v, cur_p_v};

	return Graph_lib::gui_main();
}

int main()
try {
	return e08();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
