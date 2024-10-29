#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 7: Animated/Moving object with 'Start' and 'End' buttons
//------------------------------------------------------------------------------
// Design Notes:
// 1. Implemented a very basic form of spritesheet functionality.
// 2. Used the above to animate the rotation of the truck.
// 3. Implemented and animated a Progress_bar to provide some visual feedback
//    for elapsed / remaining time of the current animation.
//------------------------------------------------------------------------------

int e07()
{
	fl_color(0);
	My_window win{{10, 10}, 400, 400, "A lot of vroom", 100};

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
