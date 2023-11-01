#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include <cmath>
#include <initializer_list>
#define _USE_MATH_DEFINES
#include <math.h>

// Exercise 11 (and 12)
// 1. Draw a 300x200 ellipse.
// 2. Draw an X and a Y axis through the center, 400x300.
// 3. Mark the foci.
// 4. Mark a point anywhere along the perimeter of the ellipse.
// 5. Connect the foci and the perimeter point with lines.
// 6. Make the point move along the perimeter as you click 'Next' (Exercise 12)

namespace GL = Graph_lib;

void draw_foci(Debug_window& win, GL::Mark& f1, GL::Mark& f2) {
	win.attach(f1);
	win.attach(f2);
}

GL::Point ellipse_perimeter_pt(const GL::Ellipse& e, double angle) {
	angle *= M_PI / 180;
	return(
		GL::Point{
			static_cast<int>(round(e.center().x + e.major() * std::cos(angle))),
			static_cast<int>(round(e.center().y + e.minor() * std::sin(angle)))
		}
	);
}

struct Connect_foci : GL::Open_polyline {         // open sequence of lines
	using GL::Open_polyline::Open_polyline;
    void set_point(int i,Point p) { GL::Shape::set_point(i ,p); };
};

void e11()
{
	constexpr bool ENABLE_DEBUG{ false };

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	constexpr GL::Point c{
		static_cast<int>(win_w * 0.5), static_cast<int>(win_h * 0.5)
	};
	Debug_window win{ {10, 10}, win_w, win_h, "Folk Eye", ENABLE_DEBUG };

	// Ellipse
	constexpr int e_w{ 300 };
	constexpr int e_h{ 200 };
	constexpr int e_maj{ static_cast<int>(e_w * 0.5) };
	constexpr int e_min{ static_cast<int>(e_h * 0.5) };
	GL::Ellipse e{ c, e_maj, e_min };

	e.set_color(FL_BLACK);
	win.attach(e);

	// Axes
	constexpr int ax_w{ e_w + static_cast<int>(e_w / 3.0) };
	constexpr int ax_h{ e_h + static_cast<int>(e_h * 0.5) };
	constexpr int ax_div_len{ static_cast<int>((ax_w - e_w) * 0.25) };
	constexpr int ax_div_x{ static_cast<int>( ax_w / ax_div_len ) };
	constexpr int ax_div_y{ static_cast<int>( ax_h / ax_div_len ) };
	GL::Axis ax_x{
		GL::Axis::x,
		{ c.x - static_cast<int>(ax_w * 0.5), c.y },
		ax_w, ax_div_x, "X"
	};
	GL::Axis ax_y{
		GL::Axis::y,
		{ c.x, c.y + static_cast<int>(ax_h * 0.5)},
		ax_h, ax_div_y, "Y"
	};
	ax_x.set_color(45);
	ax_y.set_color(45);
	win.attach(ax_x);
	win.attach(ax_y);

	// Foci
	GL::Mark f1{ e.focus1(), '+' };
	GL::Mark f2{ e.focus2(), '+' };
	f1.set_color(FL_BLUE);
	f2.set_color(FL_RED);
	// Draw foci last

	// Perimeter point
	constexpr double peri_pt_angle{ 33 };
	GL::Mark peri_m{ ellipse_perimeter_pt(e, peri_pt_angle), '+' };
	peri_m.set_color(FL_GREEN);
	// Draw perimeter point last

	// Connect foci and perimeter
	Connect_foci l{ f1.point(0), peri_m.point(0), f2.point(0) };
	l.set_color(FL_YELLOW);
	win.attach(l);

	draw_foci(win, f1, f2);
	win.attach(peri_m);

	win.wait_for_button();

	// Move point
	int i{ 0 };
	constexpr int angle_incr{ 5 };
	constexpr int max_incr{ 100 };
	do {

		GL::Point new_pt{
			ellipse_perimeter_pt(
				e,
				static_cast<int>((peri_pt_angle + angle_incr * (i+1)))%360) };
		peri_m.move(
			new_pt.x - peri_m.point(0).x,
			new_pt.y - peri_m.point(0).y
		);
		l.set_point(1, peri_m.point(0));

		++i;
		win.wait_for_button();
	} while (i < max_incr);
}

int main() {
	try {
          e11();
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


