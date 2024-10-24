#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 2:
// Implement 'My_window', a window with a 4x4 grid of square buttons,
// clicking each button should perform a single action, such as printing its
// coordinates in an output box, or changing its color.
//------------------------------------------------------------------------------
// Limitations of Button / Widget:
// Because the only mutable attrib. of a Widget are its Position and Visibility,
// even changing the color, or label of a Button is 'tricky'.
// The book alludes to the fact that a Shape can be put on top of a Button
// without blocking any of its functionality.
// Still, changing its size would not be possible, as even though the Shape
// may shrink or grow, the underlying 'capture area' remains unchanged.
//------------------------------------------------------------------------------
// A custom Shape_button class, derived from Graph_lib::Button:
// Can be in a state of: Normal, Active, Disabled
// It may or may not be Visible (True | False)
// Contains three components:
// 1. A rectangular Shape drawn unless NOT Visible.
// 1. A Button visible when Normal, but covered by the Shape above.
// 2. A Button visible when Active, but also covered.
//------------------------------------------------------------------------------
// Actions:
// 1. Print coordinates    (Print)
// 2. Change color         (Light)
// 3. Change line style    (Dots)
// 4. Change size          (Grow)
// 5. Change text          (Caps)
// 6. Change size          (Tiny)
// 7. Change color         (Dark)
// 8. Move                 (Right)
// 9. Change line style    (Dash)
// 10. Hide                (Hide)
// 11. Change size         (Wide)
// 12. Change text         (Empty)
// 13. Move                (Down)
// 14. Change size         (Long)
// 15. Print               (Time)
// 16. Change BG color.    (BG)
//------------------------------------------------------------------------------

int e02()
{
	fl_color(0);
	My_window win{
	    {10, 10},
	    640,
	    480,
	    "Seize the seize!",
	};

	return Graph_lib::gui_main();
}

int main()
try {
	return e02();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
