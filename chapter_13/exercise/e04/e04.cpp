#include "../../lib/Graph.h"
#include "../../lib/Simple_window.h"
#include <exception>
#include <iostream>
#include <vector>
#include "e04_helpers.h"

/* Exercise 4.
 * Define helper functions that return connection Points for a given Rectangle:
 *		+ n(), s(), e(), w() - Returns points north, south, etc.
 *		+ center()
 *		+ nw(), ne(), se(), sw() - North-east, north-west, etc.
 */

namespace GL = Graph_lib;

void e04()
{
	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Simple_window win{ {10, 10}, win_w, win_h, "Rectangle connection points"};

	GL::Rectangle r{ {25, 25}, win_w - 50, win_h - 50};
	r.set_color(GL::Color::black);
	win.attach(r);

	// Top row
	GL::Mark mark_nw{ E04::nw(r), 'w' };
	mark_nw.set_color(GL::Color::red);
	win.attach(mark_nw);

	GL::Mark mark_n{ E04::n(r), 'n' };
	mark_n.set_color(GL::Color::red);
	win.attach(mark_n);

	GL::Mark mark_ne{ E04::ne(r), 'e' };
	mark_ne.set_color(GL::Color::red);
	win.attach(mark_ne);

	// Middle
	GL::Mark mark_w{ E04::w(r), 'W' };
	mark_w.set_color(GL::Color::red);
	win.attach(mark_w);

	GL::Mark mark_c{ E04::center(r), 'c' };
	mark_c.set_color(GL::Color::red);
	win.attach(mark_c);

	GL::Mark mark_e{ E04::e(r), 'E' };
	mark_e.set_color(GL::Color::red);
	win.attach(mark_e);

	// Bottom
	GL::Mark mark_sw{ E04::sw(r), 'w' };
	mark_sw.set_color(GL::Color::red);
	win.attach(mark_sw);

	GL::Mark mark_s{ E04::s(r), 's' };
	mark_s.set_color(GL::Color::red);
	win.attach(mark_s);

	GL::Mark mark_se{ E04::se(r), 'e' };
	mark_se.set_color(GL::Color::red);
	win.attach(mark_se);

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


