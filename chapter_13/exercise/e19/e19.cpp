#include <exception>
#include <iostream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"

// Exercise 19.
// Create class 'Star', initialized with x number of points.
// Draw a few stars with differing colors.

namespace GL = Graph_lib;

//------------------------------------------------------------------------------

void e19()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{false};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Twinkle",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};
}

int main() {
	try {
		e19();
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


