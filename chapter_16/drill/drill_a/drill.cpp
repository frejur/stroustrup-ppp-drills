#include "ln_win.h"
#include <iostream>

// Drill A: Make a completely new project with linker settings for FLTK.
//          Type in the line-drawing program from 16.5 and get it to run.

int drill()
{
	fl_color(0);
	Lines_window win{
	    {10, 10},
	    640,
	    480,
	    "Drill A",
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
