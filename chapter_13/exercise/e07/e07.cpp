#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"

/* Exercise 5.
 * Define helper functions that return connection Points for a given
 * Circle or Ellipse:
 *		+ n(), s(), e(), w() - Returns points north, south, etc.
 *		+ center()
 *		+ nw(), ne(), se(), sw() - North-east, north-west, etc.
 */

namespace GL = Graph_lib;

void e07()
{
	constexpr bool ENABLE_DEBUG{ false };

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	Debug_window win{ {10, 10}, win_w, win_h, "RGB swatches", ENABLE_DEBUG };
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


