#include <exception>
#include <iostream>
#include "../../lib/Window.h"
#include "../../lib/Graph.h"

void e02()
{
	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	Graph_lib::Point c{static_cast<int>(win_w * 0.5),
	                   static_cast<int>(win_h * 0.5)};
	Graph_lib::Window win{{10, 10}, win_w, win_h, "Reset?"};

	fl_color(0);

	Graph_lib::gui_main();	
}


int main() {
	try {
		e02();
		return 0;
	} catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
