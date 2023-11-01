#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include "righttriangle.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include <cmath>

// Exercise 14.
// Create a RightTriangle class and use it to draw a multicolored octagonal.

namespace GL = Graph_lib;

std::vector<std::unique_ptr<RTRI::RightTriangle>> draw_octagon(
	Debug_window& win, GL::Point center, int radius, double start_angle)
{
	std::vector<std::unique_ptr<RTRI::RightTriangle>> tris;
	for (int i = 0; i < 8; ++i) {
		GL::Point p;
		if (i == 0) {
			p = {
			static_cast<int>(std::round(
				center.x + cos(start_angle) * radius)),
			static_cast<int>(std::round(
				center.y + sin(start_angle) * radius))
			};
		} else {
			p = tris.back()->point(2);
		}
		tris.push_back(std::make_unique<RTRI::RightTriangle>(center, p, radius));
		tris.back()->set_color(GL::Color::Transparency::invisible);
		tris.back()->set_fill_color(60 + i*16);
		win.attach(*tris.back());
	}
	return tris;
}

void e14()
{
	constexpr bool ENABLE_DEBUG{ false };

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{ {10, 10}, win_w, win_h, "Nice Tri",
		ENABLE_DEBUG};

	auto oct_tris{ draw_octagon(win, c, 32 * 5, 0.734) };

	win.wait_for_button();
}

int main() {
	try {
          e14();
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


