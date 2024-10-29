#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 5:
//------------------------------------------------------------------------------
// Design Notes:
// 1. Expanded on the previous exercise by creating a Ouija board interface,
//    the 'planchette' moves around to spell out characters read from text files.
// 2. Each character (A-Z, 0-9) has a mapped coordinate, stored in a text file.
// 3. Added a "Remap" mode, where users can assign new character positions
//    by clicking on the board and typing the desired character.
//        > This is (Hackily) managed by drawing a grid of <In_box> inputs.
//        > This was used to create the default mappings.
// 4. Implemented a state management system to switch between:
//        > Normal, Remap, and Ouija modes.
// 5. Added various helper functions and classes.
//------------------------------------------------------------------------------

int e05()
{
	fl_color(0);
	My_window win{
	    {10, 10},
	    480,
	    320,
	    "Yes, yes. Good Luck",
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
