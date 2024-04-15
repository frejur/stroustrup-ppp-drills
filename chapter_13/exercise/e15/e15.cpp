#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include "righttriangle.h"
#include "triangletiler.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

// Exercise 15.
// Use the RightTriangle class to tile the entire window with triangles.

namespace GL = Graph_lib;

void e15()
{
	constexpr bool ENABLE_DEBUG{true};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{ {10, 10}, win_w, win_h, "Tri Harder",
		ENABLE_DEBUG};

	fl_color(0);
	TRITI::TriangleTiler tiles{{64, 64}, 540, 400, 100, 0};
	win.attach(tiles);

	win.wait_for_button();
}

int main() {
	try {
          e15();
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


