#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 8:
// Pipe the contents of an In_box into the Calculator / Expression parser
// from chapter 7. Display the results in an Out_box.
//------------------------------------------------------------------------------
// Design notes:
// Create a basic Calculator GUI for building and evaluating expressions.
// - Buttons for numbers, arithmetic operators and a decimal point.
// - Edit button: Toggles the visibility of an Input field containing the
//   current expression. Can be used for manual editing as described in the
//   original exercise description.
// - Clear button: Clears the current expression.
// - Undo Button: Reverts expression to the last valid state registered.
// Also:
// - Structure the GUI in a class, add support for multiple instances of said
//   class to be instantiated and attached to the same window.
// - Allow the user to select which (if any) default callbacks for the
//   Calculator's various widgets to override upon initialization.

int e08()
{
	fl_color(0);
	My_window win{
	    {10, 10},
	    640,
	    480,
	    "80085",
	};

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
