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

double dot(GL::Point a, GL::Point b)
{
	return static_cast<double>(a.x * b.x + a.y * b.y);
}

struct Bary_coords
{
	double v;
	double w;
	double u;
};

Bary_coords bary(GL::Point p, GL::Point a, GL::Point b, GL::Point c)
{
	GL::Point v0 = {b.x - a.x, b.y - a.y};
	GL::Point v1 = {c.x - a.x, c.y - a.y};
	GL::Point v2 = {p.x - a.x, p.y - a.y};

	double d00 = dot(v0, v0);
	double d01 = dot(v0, v1);
	double d11 = dot(v1, v1);
	double d20 = dot(v2, v0);
	double d21 = dot(v2, v1);

	double denom = d00 * d11 - d01 * d01;
	if (denom == 0) {
		return {0, 0, 0};
	}

	double v = (d11 * d20 - d01 * d21) / denom;
	double w = (d00 * d21 - d01 * d20) / denom;
	return {v, w, (1.0 - v - w)};
}

bool is_inside_tri(const Bary_coords& c)
{
	return 0 <= c.v && c.v <= 1 && 0 <= c.w && c.w <= 1;
}

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
	TRITI::TriangleTiler tiles{o, t_w, t_h, 64, 47};
	win.attach(tiles);

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
				Bary_coords b{bary(corner,
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


