#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include "righttriangle.h"
#include "triangle.h"
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
	constexpr double oct_angle{ 45 * M_PI / 180 };
	double iter_angle { 0 };
	for (int i = 0; i < 8; ++i) {
		GL::Point p0, p1;
		if (i == 0) {
			p0 = {
			static_cast<int>(std::round(
				center.x + cos(start_angle) * radius)),
			static_cast<int>(std::round(
				center.y + sin(start_angle) * radius))
			};
		} else {
			p0 = tris.back()->point(1);
		}
		if (i < 7) {
			iter_angle = start_angle + oct_angle * (i+1);
			p1 = {
			static_cast<int>(std::round(
				center.x + cos(iter_angle) * radius)),
			static_cast<int>(std::round(
				center.y + sin(iter_angle) * radius))
			};
		} else {
			p1 = tris.front()->point(0);
		}
		tris.push_back(
			std::make_unique<RTRI::RightTriangle>(p0, p1)
		);
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
	Debug_window win{ {10, 10}, win_w, win_h, "At least i tri'd",
		ENABLE_DEBUG};

	auto oct_tris{ draw_octagon(win, c, 32 * 5, 45 * M_PI / 360) };

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


