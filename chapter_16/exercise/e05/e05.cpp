#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 5:

int e05()
{
	fl_color(0);
	My_window win{
	    {10, 10},
	    480,
	    320,
	    "Good Luck",
	};

	return Graph_lib::gui_main();
}

int main()
try {
	return e05();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
