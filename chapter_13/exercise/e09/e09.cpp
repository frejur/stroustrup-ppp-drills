#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include "regularhexagon.h"
#include "hexagontiler.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

/* Exercise 9.
 * Create a pattern of at least 8 hexagons, tiled. */

namespace GL = Graph_lib;

void e09()
{
	constexpr bool ENABLE_DEBUG{ false };

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{ {10, 10}, win_w, win_h, "Catan",
		ENABLE_DEBUG};

	HXT::HexagonTiler hex{ c, 169, 16 };
	win.attach(hex);

	win.wait_for_button();
}

int main() {
	try {
          e09();
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


