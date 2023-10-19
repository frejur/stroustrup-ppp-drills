#include "../../lib/Graph.h"
#include "../../lib/GUI.h"
#include "../../lib/Debug_window.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>

/* Exercise 6.
 * Draw the class diagram from 12.6 using rounded boxes and arrows.
 * (Let's throw an ellipse in there too!)
 */

namespace GL = Graph_lib;

void e06()
{
	constexpr bool ENABLE_DEBUG{ true };

	constexpr int win_w{ 960 };
	constexpr int win_h{ 520 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{ {10, 10}, win_w, win_h, "Classy diagramme",
		ENABLE_DEBUG};

	// TODO: Add shapes

	win.wait_for_button();
}

int main() {
	try {
		e06();
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


