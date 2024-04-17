#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include "righttriangle.h"
#include "triangletiler.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <sstream>

// Exercise 15.
// Use the RightTriangle class to tile the entire window with triangles.

namespace GL = Graph_lib;

//------------------------------------------------------------------------------

const std::string& info_click()
{
	static const std::string s{
	    "Click anywhere to place the initial triangle tile"};
	return s;
}

const std::string& info_drag()
{
	static const std::string s{
	    "Move the cursor along the X-axis to rotate, move it along the Y-axis "
	    "to scale. Click to confirm"};
	return s;
}

//------------------------------------------------------------------------------

void e15()
{
	constexpr bool ENABLE_DEBUG{true};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Tri Harder",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);
	const GL::Point o{64, 64};
	const int t_w{540};
	const int t_h{400};
	TRITI::TriangleTiler tiles{o, t_w, t_h, 64, 0};
	win.attach(tiles);

	GL::Text info{{64, 32}, info_click()};
	win.attach(info);

	while (true) {
		if (win.click_has_been_registered()) {
			tiles.move_to(win.click_position());
			std::stringstream ss;
			for (int i = 0; i < 4; ++i) {
				Point corner = o;
				if (i == 1) {
					corner.x += t_w;
				} else if (i == 2) {
					corner.x += t_w;
					corner.y += t_h;
				} else if (i == 3) {
					corner.y += t_h;
				}
				TRITI::Bary_coords b{TRITI::bary(corner,
				                                 tiles.point(0),
				                                 tiles.point(1),
				                                 tiles.point(2))};
				ss << "Corner " << i << ": "
				   << (is_inside_tri(b) ? "IN" : "OUT") << ' ';
			}
			win.log(ss.str() + "\n");
			// win.log("New pos: " + std::to_string(tiles.point(0).x) + ", "
			//         + std::to_string(tiles.point(0).y) + "\n");
		}
		win.wait_for_click();
	}
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


