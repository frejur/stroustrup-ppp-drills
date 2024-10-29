#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 7: Animated / Moving object.
//------------------------------------------------------------------------------
// Design Notes:
// 1. Use a pickup instead of a plane.
//------------------------------------------------------------------------------

int e07()
{
	fl_color(0);
	My_window win{{10, 10}, 400, 400, "Vroom", 100};

	return Graph_lib::gui_main();
}

int main()
try {
	return e07();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
