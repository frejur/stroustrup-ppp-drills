#include <exception>
#include <iostream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "star.h"

// Exercise 19.
// Create class 'Star', initialized with x number of points.
// Draw a few stars in different colors.

namespace GL = Graph_lib;

//------------------------------------------------------------------------------

void e19()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{false};

	constexpr int grid_size{128};
	constexpr int win_w{grid_size * 7};
	constexpr int win_h{grid_size * 5};
	constexpr int star_size{static_cast<int>(grid_size * 0.75)};
	GL::Point c{static_cast<int>(win_w * 0.5), static_cast<int>(win_h * 0.5)};
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Twinkle",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	stella::Star s_0{{c.x - grid_size * 2, c.y - grid_size}, 5, star_size};
	stella::Star s_1{{c.x - grid_size * 0, c.y - grid_size}, 6, star_size};
	stella::Star s_2{{c.x + grid_size * 2, c.y - grid_size}, 7, star_size};
	stella::Star s_3{{c.x - grid_size * 2, c.y + grid_size}, 8, star_size};
	stella::Star s_4{{c.x - grid_size * 0, c.y + grid_size}, 9, star_size};
	stella::Star s_5{{c.x + grid_size * 2, c.y + grid_size}, 10, star_size};
	s_0.set_color(Graph_lib::Color::Transparency::invisible);
	s_1.set_color(Graph_lib::Color::Transparency::invisible);
	s_2.set_color(Graph_lib::Color::Transparency::invisible);
	s_3.set_color(Graph_lib::Color::Transparency::invisible);
	s_4.set_color(Graph_lib::Color::Transparency::invisible);
	s_5.set_color(Graph_lib::Color::Transparency::invisible);
	s_0.set_fill_color(Graph_lib::Color::blue);
	s_1.set_fill_color(Graph_lib::Color::dark_yellow);
	s_2.set_fill_color(Graph_lib::Color::green);
	s_3.set_fill_color(Graph_lib::Color::white);
	s_4.set_fill_color(Graph_lib::Color::red);
	s_5.set_fill_color(Graph_lib::Color::cyan);
	win.attach(s_0);
	win.attach(s_1);
	win.attach(s_2);
	win.attach(s_3);
	win.attach(s_4);
	win.attach(s_5);
	win.wait_for_button();
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


