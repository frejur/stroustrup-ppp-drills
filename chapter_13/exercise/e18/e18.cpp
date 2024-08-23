#include <exception>
#include <iostream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/help/inters.h"
#include "dynpoly.h"
#include "poly.h"

// Exercise 18.
// Create an extension of the 'Polygon' class called 'Poly', where all points
// must be supplied to its constructor, and an exception is thrown if any
// of the resulting lines intersect.

// Additions:
// - Allow the user to interactively draw 'Closed_polyline's by clicking.
// - Attempt to convert drawn polylines into 'Poly's as outlined above.

namespace GL = Graph_lib;

//------------------------------------------------------------------------------

const std::string& info_click()
{
	static const std::string s{
	    "Click anywhere to start drawing a polygon"};
	return s;
}

const std::string& info_transform()
{
	static const std::string s{
	    "Keep clicking to add segments, finish by clicking the starting point."};
	return s;
}

//------------------------------------------------------------------------------
namespace e18draw {

class Draw_poly : public Shape
{
public:
	Draw_poly(){};
	void add_poly(const std::vector<GL::Point>& pts)
	{
		poly_v.push_back(std::make_unique<Graph_lib::Poly>(pts));
		poly_v.back()->set_color(Graph_lib::Color::green);
		poly_v.back()->set_fill_color(Graph_lib::Color::green);
	};
	void draw_lines() const
	{
		for (int i = 0; i < poly_v.size(); ++i) {
			poly_v[i]->draw();
		}
	};

private:
	std::vector<std::unique_ptr<GL::Poly>> poly_v;
};
} // namespace e18draw

//------------------------------------------------------------------------------

void e18()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Want a cracker",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);
	const GL::Point o{32, 64};
	const int t_w{win_w - 64};
	const int t_h{win_h - 96};

	dynpoly::Dynamic_poly dyn_p{o, {o.x + 1, o.y + 1}};
	win.attach(dyn_p);

	dynpoly::Window_and_poly pass_to_callback{win, dyn_p};

	GL::Text info{{64, 32}, info_click()};
	win.attach(info);

	// Store and draw polys
	e18draw::Draw_poly dp{};
	win.attach(dp);

	int count_logged = 0;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!dyn_p.is_transforming()) {
				// tiles.pause_drawing();
				dyn_p.enable_transform();
				hacky_redraw_poly(pass_to_callback); // transform by moving mouse
				info.set_label(info_transform());
			} else {
				// tiles.resume_drawing();
				dyn_p.apply_transform();
				// dyn_p.disable_transform();
				// tiles.update_transform(dyn_t.origin(),
				//                        dyn_t.side_length(),
				//                        dyn_t.angle());
				win.log("Test" + '\n');
				++count_logged;
				if (count_logged > 10) {
					win.clear_logs();
					count_logged = 0;
				}
				if (!dyn_p.is_transforming()) {
					dp.add_poly(dyn_p.points());
					info.set_label(info_click());
				}
			}
		}
		win.wait_for_click();
	}
}

int main() {
	try {
		e18();
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


