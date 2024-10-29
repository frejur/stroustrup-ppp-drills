#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 6: Make an animated analog clock, use clock(), sleep().
//------------------------------------------------------------------------------
// Since there's animation involved in exercise 7 as well, a more generic
// Animated_window was implemented.

int e06()
{
	fl_color(0);
	My_window win{{10, 10}, 400, 400, "All things must pass", 100};

	return Graph_lib::gui_main();
}

int main()
try {
	return e06();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
