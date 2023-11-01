#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include "swatchgrid.h"

/* Exercise 7.
 * Make an RGB color chart.
 */

namespace GL = Graph_lib;

void e07()
{
	constexpr bool ENABLE_DEBUG{ false };

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	Debug_window win{ {10, 10}, win_w, win_h, "RGB swatches", ENABLE_DEBUG };

	SWGR::SwatchGrid sg{ {50,50}, 550, 370, 26, 18 };
	win.attach(sg);

	win.wait_for_button();
}

int main() {
	try {
          e07();
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


