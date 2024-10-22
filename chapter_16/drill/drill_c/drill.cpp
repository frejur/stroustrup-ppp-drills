#include "ln_win.h"
#include <iostream>

// Drill C: Modify the program from 16.7, add a menu for changing the Line style

int drill()
{
	fl_color(0);
	Lines_window win{
	    {10, 10},
	    640,
	    480,
	    "Drill C",
	};
	return Graph_lib::gui_main();
}

int main()
try {
	drill();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
} catch (...) {
	std::cerr << "Unknown error" << '\n';
}
