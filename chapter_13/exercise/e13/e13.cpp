#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include "swatchgrid.h"

// Exercise 13. Draw the color matrix from 13.10 but without black borders.

namespace GL = Graph_lib;

void e13()
{
	constexpr bool ENABLE_DEBUG{ false };

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	Debug_window win{ {32, 32}, win_w, win_h, "Matrix", ENABLE_DEBUG };

	SWGR::SwatchGrid sg{ {64,32}, 416, 416, 16, 16, 0 };
	win.attach(sg);

	win.wait_for_button();
}

int main() {
	try {
          e13();
          return 0;
	}
	catch (std::exception &e) {
		std::cerr<<e.what()<<'\n';
		return 1;
	}
	catch (...) {
		std::cerr<<"Unknown error\n";
		return 2;
	}
}


