#include "../../lib/Graph.h"
#include "../../lib/Simple_window.h"
#include "arrow.h"
#include <exception>
#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#define _USE_MATH_DEFINES
#include <math.h>

/* Exercise 3. Define an Arrow class. */

namespace GL = Graph_lib;

void e03()
{
	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Simple_window win{ {10, 10}, win_w, win_h, "Arrows"};

	std::vector<std::unique_ptr<Arrow>> arrows{};
	std::vector<Arrow> arrows2{};

	constexpr int len{ 250 };
	constexpr int num_arrows{ 18 };
	constexpr int len_increase{ static_cast<int>(len / (float)num_arrows)};
	constexpr double ang_increase{ 2 * M_PI / num_arrows };

	for (int i=num_arrows; i > 0; --i) {
		Point p = {
			c.x + static_cast<int>(std::sin(ang_increase * i) *
				(num_arrows - i + 1) * len_increase),
			c.y + static_cast<int>(std::cos(ang_increase * i) *
				(num_arrows - i + 1) * len_increase)
		};
		arrows.push_back(
			std::make_unique<Arrow>(c, p)
		);
		arrows.back()->set_color(Color::black);
		win.attach(*arrows.back());
	}

	win.wait_for_button();
}

int main() {
	try {
		e03();
		return 1;
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


