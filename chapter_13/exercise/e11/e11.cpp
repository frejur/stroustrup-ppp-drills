#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"

// Exercise 11
// 1. Draw a 300x200 ellipse.
// 2. Draw an X and a Y axis through the center, 400x300.
// 3. Mark the foci.
// 4. Mark a point anywhere along the perimeter of the ellipse.
// 5. Connect the foci and the perimeter point with lines.

namespace GL = Graph_lib;

void e11()
{
	constexpr bool ENABLE_DEBUG{ false };

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	Debug_window win{ {10, 10}, win_w, win_h, "Folk Eye", ENABLE_DEBUG };

	win.wait_for_button();
}

int main() {
	try {
          e11();
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


