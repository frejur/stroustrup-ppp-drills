#include "../../lib/Graph.h"
#include "../../lib/GUI.h"
#include "../../lib/Simple_window.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "e05_helpers.h"
#include <FL/Fl_Text_Display.H>
#include "../../lib/Debug_window.h"

/* Exercise 5.
 * Define helper functions that return connection Points for a given
 * Circle or Ellipse:
 *		+ n(), s(), e(), w() - Returns points north, south, etc.
 *		+ center()
 *		+ nw(), ne(), se(), sw() - North-east, north-west, etc.
 */

namespace GL = Graph_lib;

void e04()
{
	constexpr bool ENABLE_DEBUG = true;
	constexpr int debug_win_mult{ ENABLE_DEBUG ? 2 : 1};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{ {10, 10}, win_w, win_h, "Ellipse connection points",
		ENABLE_DEBUG};

	// Ellipse -----------------------------------------------------------------
	GL::Ellipse e{ c, c.x -25, c.y - 150};
	e.set_color(GL::Color::black);
	win.attach(e);

	win.log("Hello");
	win.log("World");

	// Top row
	GL::Mark mark_nw{ E05::nw(e), 'w' };
	mark_nw.set_color(GL::Color::red);
	win.attach(mark_nw);

	GL::Mark mark_n{ E05::n(e), 'n' };
	mark_n.set_color(GL::Color::red);
	win.attach(mark_n);

	GL::Mark mark_ne{ E05::ne(e), 'e' };
	mark_ne.set_color(GL::Color::red);
	win.attach(mark_ne);

	// Middle
	GL::Mark mark_w{ E05::w(e), 'W' };
	mark_w.set_color(GL::Color::red);
	win.attach(mark_w);

	GL::Mark mark_c{ E05::center(e), 'c' };
	mark_c.set_color(GL::Color::red);
	win.attach(mark_c);

	GL::Mark mark_e{ E05::e(e), 'E' };
	mark_e.set_color(GL::Color::red);
	win.attach(mark_e);

	// Bottom
	GL::Mark mark_sw{ E05::sw(e), 'w' };
	mark_sw.set_color(GL::Color::red);
	win.attach(mark_sw);

	GL::Mark mark_s{ E05::s(e), 's' };
	mark_s.set_color(GL::Color::red);
	win.attach(mark_s);

	GL::Mark mark_se{ E05::se(e), 'e' };
	mark_se.set_color(GL::Color::red);
	win.attach(mark_se);

	// Circle ------------------------------------------------------------------
	GL::Circle ci{ { c.x + 25, c.y - 25 }, 120};
	ci.set_color(GL::Color::blue);
	win.attach(ci);

	// Top row
	GL::Mark mark_nw2{ E05::nw(ci), 'w' };
	mark_nw2.set_color(GL::Color::green);
	win.attach(mark_nw2);

	GL::Mark mark_n2{ E05::n(ci), 'n' };
	mark_n2.set_color(GL::Color::green);
	win.attach(mark_n2);

	GL::Mark mark_ne2{ E05::ne(ci), 'e' };
	mark_ne2.set_color(GL::Color::green);
	win.attach(mark_ne2);

	// Middle
	GL::Mark mark_w2{ E05::w(ci), 'W' };
	mark_w2.set_color(GL::Color::green);
	win.attach(mark_w2);

	GL::Mark mark_c2{ E05::center(ci), 'c' };
	mark_c2.set_color(GL::Color::green);
	win.attach(mark_c2);

	GL::Mark mark_e2{ E05::e(ci), 'E' };
	mark_e2.set_color(GL::Color::green);
	win.attach(mark_e2);

	// Bottom
	GL::Mark mark_sw2{ E05::sw(ci), 'w' };
	mark_sw2.set_color(GL::Color::green);
	win.attach(mark_sw2);

	GL::Mark mark_s2{ E05::s(ci), 's' };
	mark_s2.set_color(GL::Color::green);
	win.attach(mark_s2);

	GL::Mark mark_se2{ E05::se(ci), 'e' };
	mark_se2.set_color(GL::Color::green);
	win.attach(mark_se2);


	win.wait_for_button();
}

int main() {
	try {
		e04();
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


