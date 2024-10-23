#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 1:
// Implement 'My_window', a window that has a 'Next' button just like in a
// 'Simple_window', but also a 'Quit' button.

int e01()
{
	fl_color(0);
	My_window win{
	    {10, 10},
	    640,
	    480,
	    "My widdle widget",
	};

	Graph_lib::Text info{{32, 32}, "Keep pressing 'Next' to move the rectangle"};
	win.attach(info);

	Graph_lib::Rectangle r{{64, 64}, 64, 64};
	r.set_color(Graph_lib::Color::blue);
	win.attach(r);

	for (int i = 0; i < 5; ++i) {
		win.wait_for_button();
		r.move(96, 64);
	}
	win.hide_next_button();
	win.detach(info);

	return Graph_lib::gui_main();
}

int main()
try {
	e01();
} catch (const std::exception& e) {
	std::cerr << "Error: " << e.what() << '\n';
} catch (...) {
	std::cerr << "Unknown error" << '\n';
}
