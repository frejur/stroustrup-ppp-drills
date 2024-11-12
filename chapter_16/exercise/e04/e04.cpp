#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 4:
// Create a custom Window class that has:
// - Two <Input_box>'s, where one can enter X and Y coordinates.
// - A menu with 4 buttons, that create the following shapes:
//     1. Circle
//     2. Hexagon
//     3. Square
//     4. Triangle
// The above widgets should enable the user to create the desired shape
// at the desired position.
//------------------------------------------------------------------------------
// Additions:
// - A 'Select' button next to the Input boxes:
//     > When pressed it brings up the shape menu near the given coordinate.
//     > An arrow points from the menu to the position (center) where the shape
//       will be created.
// - A 'Random' button next to the select button, sets the Input boxes to a
//   random pair of coordinates and 'selects' them.
//------------------------------------------------------------------------------

int e04()
{
	fl_color(0);
	My_window win{
	    {10, 10},
	    640,
	    480,
	    "Complacent placement",
	};

	// Select a random initial position
	win.random();

	return Graph_lib::gui_main();
}

int main()
try {
	return e04();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
