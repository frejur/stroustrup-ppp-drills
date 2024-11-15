#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 10: Create a program that plots a couple of single
//                          parameter functions (sin, log, etc.).
//                          Provide a GUI that allows the user choose which
//                          function(s) to graph and adjust their parameters.
//------------------------------------------------------------------------------
// Design notes:
// - Set the 'canvas' coordinate space to values 0 to 1 on both the x and y axes.
//   All plotted points will fall withing this bounded space.
// - Stack multiple plotted functions ontop of each other and allow the user to
//   toggle individual functions on or off.
// - Plot the following functions with parameter controls:
//     1. Variations of `log`: log(b, x)
//         Parameter 'b' - Determines the base of the logarithm, e.g.:
//                         > `log(2, x)` plots a base-2 logarithm.
//                         > `log(10, x)` plots a base-10 logarithm.
//     2. `sin(x * f)`
//         Parameter 'f' - The frequency.
//     3. `superellipse(x, n, m) - Fitted to the canvas space.
//         Parameter 'n' and 'm' - Exponents controlling the shape of the super-
//                                 ellipse in the expression:
//                                 > `|x|^n + |y|^m`
//     4. `perlin_noise(x, o, p)` - A basic implementation of Perlin noise using
//                                  linear interpolation.
//         Parameter 'o' - Number of octaves.
//         Parameter 'p' - Persistence.
//   (Some of these are not really single parameter functions, but chosen for
//    for their visual characteristics)
// - Each function has been slightly adjusted to have its characteristic portion
//   fit within the range of the canvas space.
// - Add a 'Seed' button for generating a new sequence of random values to use
//   when calculating the perlin noise.
// - Implement an Shape_button that toggles on/off when clicked.
// - Implement an In_box that validates integer or floating point values after
//   each edit. If the value is invalid, use the default value and mark the
//   input field with a red border.
// - Implement a Widget that combines the above In_box with '+' and '-'
//   buttons that can be used to tweak the value in increments. Disable either
//   button when the minimum or maximum value has been reached.

int e10()
{
	fl_color(0);
	My_window win{
	    {10, 10},
	    640,
	    544,
	    "Disturbing the peace",
	};

	return Graph_lib::gui_main();
}

int main()
try {
	return e10();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
	return 1;
} catch (...) {
	std::cerr << "Unknown error" << '\n';
	return 2;
}
