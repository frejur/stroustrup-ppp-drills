#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 3:
// Create an Image_button class, a Button covered by an image.
// Move the button to a random position when clicked.
// Ensure that the image moves along with the underlying button.

int e03()
{
	fl_color(0);
	My_window win{
	    {10, 10},
	    640,
	    480,
	    "Risky business",
	};

	return Graph_lib::gui_main();
}

int main()
try {
	return e03();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
