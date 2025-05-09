#include <exception>
#include <iostream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/help/inters.h"
#include "../share/tiler/dyntile.h"
#include "hexagontiler.h"

// Exercise 16 and 17.
// Use the RegularHexagon class to tile the entire window with different colored hexagons.

namespace GL = Graph_lib;

//------------------------------------------------------------------------------

const std::string& info_click()
{
	static const std::string s{
	    "Click anywhere to  start placing the initial hexagon tile"};
	return s;
}

const std::string& info_transform()
{
	static const std::string s{
	    "Move the cursor to transform and place the hexagon on "
	    "the canvas. Click to confirm"};
	return s;
}

//------------------------------------------------------------------------------

void e16()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Hexagon fishing",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);
	const GL::Point o{32, 64};
	const int t_w{win_w - 64};
	const int t_h{win_h - 96};
	Tile_lib::Hexagon_tiler tiles{o, t_w, t_h, 64, 0};
	if (ENABLE_DEBUG) {
		tiles.enable_debug();
	}
	win.attach(tiles);

	dyntile::Dynamic_tile dyn_t{dyntile::Tile_type::Regular_hexagon, o, 64, 0};
	win.attach(dyn_t);

    dyntile::Window_and_tile pass_to_callback{win, dyn_t};

	GL::Text info{{64, 32}, info_click()};
	win.attach(info);

	Graph_lib::Closed_polyline marker{{-1, -1}, {1, -1}, {1, 1}, {-1, 1}};

	if (ENABLE_DEBUG) {
		marker.set_color(Graph_lib::Color::cyan);
		win.attach(marker);
	}

	int count_logged = 0;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!dyn_t.is_transforming()) {
				tiles.pause_drawing();
				dyn_t.enable_transform();
                hacky_redraw_tile(pass_to_callback); // transform by moving mouse
				info.set_label(info_transform());
			} else {
				tiles.resume_drawing();
				dyn_t.apply_transform();
				dyn_t.disable_transform();
				tiles.update_transform(dyn_t.origin(),
				                       dyn_t.side_length(),
				                       dyn_t.angle());
				double deg_conv{180.0 / M_PI};
				if (ENABLE_DEBUG) {
					marker.move(dyn_t.origin().x - marker.point(0).x + 1,
					            dyn_t.origin().y - marker.point(0).y + 1);
				}
				win.log("Angle: " + std::to_string(dyn_t.angle() * deg_conv)
				        + " degrees.\n");
				++count_logged;
				win.log(
				    "CS-angle: "
				    + std::to_string(tiles.coordinate_system_angle() * deg_conv)
				    + " degrees.\n");
				++count_logged;
				win.log("Dodecant: "
				        + std::to_string(
				            static_cast<int>(dyn_t.angle() / (M_PI / 6)))
				        + ".\n");
				++count_logged;
				if (count_logged > 10) {
					win.clear_logs();
					count_logged = 0;
				}
				info.set_label(info_click());
			}
		}
		win.wait_for_click();
	}
}

int main() {
	try {
		e16();
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


