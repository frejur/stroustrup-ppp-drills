#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 6: Make an animated analog clock, use clock(), sleep().
//------------------------------------------------------------------------------
// Design Notes:
// 1. Created a custom 'Animated_window' class to support future exercises
//    involving animation.
// 2. Replaced 'sleep()' with 'Fl::wait(x)' for portability and to avoid screen
//    lock during waits.
// 3. Limited animation to 60 seconds initially as to not hog resources. It can
//    be resumed with the 'Play' button.
//------------------------------------------------------------------------------

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
