#include "ln_win.h"
#include <iostream>

// Drill A: Get the line-drawing program from 16.7 and get it to run (Add menu)

int drill()
{
	fl_color(0);
	Lines_window win{
	    {10, 10},
	    640,
	    480,
	    "Drill B",
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
