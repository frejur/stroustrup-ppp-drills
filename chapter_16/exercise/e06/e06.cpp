#include "my_win.h"
#include <iostream>

// Chapter 16, exercise 5:

int e06()
{
	fl_color(0);
	My_window win{{10, 10}, 480, 480, "All things must pass", 500};
	win.start_polling(15);

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
