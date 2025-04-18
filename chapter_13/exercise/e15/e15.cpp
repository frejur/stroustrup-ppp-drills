#include <exception>
#include <iostream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/tiler/dyntile.h"
#include "../share/help/inters.h"
#include "triangletiler.h"

// Exercise 15.
// Use the RightTriangle class to tile the entire window with triangles.

namespace GL = Graph_lib;

//------------------------------------------------------------------------------

const std::string& info_click()
{
	static const std::string s{
	    "Click anywhere to start placing the initial triangle tile"};
	return s;
}

const std::string& info_transform()
{
	static const std::string s{
	    "Move the cursor to transform and place the triangle on "
	    "the canvas. Click to confirm"};
	return s;
}

//------------------------------------------------------------------------------

void e15()
{
	constexpr bool ENABLE_DEBUG{false};
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
	const GL::Point o{32, 64};
	const int t_w{win_w - 64};
	const int t_h{win_h - 96};
	Tile_lib::Triangle_tiler tiles{o, t_w, t_h, 64, 0};
	if (ENABLE_DEBUG) {
		tiles.enable_debug();
	}
	win.attach(tiles);

	dyntile::Dynamic_tile dyn_t{dyntile::Tile_type::Right_triangle, o, 64, 0};
	win.attach(dyn_t);

    dyntile::Window_and_tile pass_to_callback{win, dyn_t};

	GL::Text info{{64, 32}, info_click()};
	win.attach(info);

	int count_logged = 0;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!dyn_t.is_transforming()) {
				tiles.pause_drawing();
				dyn_t.enable_transform();
                hacky_redraw_tile(pass_to_callback); // transform by moving mouse
				info.set_label(info_transform());
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
				}
			} else {
				tiles.resume_drawing();
				dyn_t.apply_transform();
				dyn_t.disable_transform();
				tiles.update_transform(dyn_t.origin(),
				                       dyn_t.side_length(),
				                       dyn_t.angle());
				if (count_logged > 4) {
					win.clear_logs();
					count_logged = 0;
				}
				win.log("Angle: " + std::to_string(tiles.angle()) + "\n");
				int sub_quadrant = static_cast<int>(tiles.angle()
				                                    / (M_PI * 0.25));
				win.log("Sub-Quadrant: " + std::to_string(sub_quadrant) + "\n");
				++count_logged;

				win.log(
				    "Tiles bbox bounds: "
				    + std::to_string(tiles.debug_rotates_bounds().min.x) + ", "
				    + std::to_string(tiles.debug_rotates_bounds().min.y) + " | "
				    + std::to_string(tiles.debug_rotates_bounds().max.x) + ", "
				    + std::to_string(tiles.debug_rotates_bounds().max.y) + "\n");

				info.set_label(info_click());
			}
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


