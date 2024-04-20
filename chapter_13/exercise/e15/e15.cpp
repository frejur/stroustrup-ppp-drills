#include <exception>
#include <iostream>
#include <sstream>

#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>

#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "dyntile.h"
#include "triangletiler.h"

// Exercise 15.
// Use the RightTriangle class to tile the entire window with triangles.

namespace GL = Graph_lib;

//------------------------------------------------------------------------------

const std::string& info_click()
{
	static const std::string s{
	    "Click anywhere to place the initial triangle tile"};
	return s;
}

const std::string& info_transform()
{
	static const std::string s{
	    "Move the cursor along the X-axis to rotate, along the Y-axis "
	    "to scale. Click to confirm"};
	return s;
}

//------------------------------------------------------------------------------
// Interactively transforming the initial tile, hacky, but improves debugging.

constexpr float refresh_rate{0.01};
constexpr float refresh_time_out{10};

struct Window_and_tile
/* The callback needs to access and modify:
 * - The window: The cursor / mouse
 * - The tile: Transformation
 */
{
	Debug_window& win;
	dyntile::Dynamic_tile& tile;
};

static void transform_tile_cb(void* data)
{
	static float time = 0;
	Window_and_tile* tw = static_cast<Window_and_tile*>(data);
	time += refresh_rate;
	if (!tw->tile.is_transforming() || time >= refresh_time_out) {
		if (time >= refresh_time_out) {
			tw->win.log("Tile is "
			            + std::string(tw->tile.is_transforming()
			                              ? "transforming"
			                              : "NOT transforming")
			            + "\n");
			tw->tile.reset_transform();
			tw->win.log("!");
			tw->win.force_click();
		}
		time = 0;
		Fl::remove_timeout(transform_tile_cb, data);
	} else {
		bool preview = true;
		GL::Point clk{tw->win.click_position()};
		GL::Point m{tw->win.mouse_position()};
		int x_dist = m.x - clk.x;
		int y_dist = m.y - clk.y;

		int side = sqrt(x_dist * x_dist + y_dist * y_dist);
		float angle = atan2(static_cast<float>(y_dist),
		                    static_cast<float>(x_dist))
		              - (M_PI * 0.25);
		angle = fmod(angle, 2 * M_PI);
		if (angle < 0) {
			angle += 2 * M_PI;
		}
		tw->win.log(std::to_string(angle) + ", ");

		tw->tile.cue_transform(tw->win.click_position(), side, angle);
		tw->win.log(".");
		tw->tile.apply_transform(preview);
		Fl::repeat_timeout(refresh_rate, transform_tile_cb, data);
	}
	tw->win.redraw();
}

void hacky_redraw_tile(Window_and_tile& tw)
{
	Fl::add_timeout(refresh_rate, transform_tile_cb, (void*) &tw);
}

//------------------------------------------------------------------------------

void e15()
{
	constexpr bool ENABLE_DEBUG{true};
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
	const GL::Point o{64, 64};
	const int t_w{540};
	const int t_h{400};
	TRITI::TriangleTiler tiles{o, t_w, t_h, 64, 0};
	win.attach(tiles);

	dyntile::Dynamic_tile dyn_t{dyntile::Tile_type::Right_triangle, o, 64, 0};
	win.attach(dyn_t);

	Window_and_tile pass_to_callback{win, dyn_t};

	GL::Text info{{64, 32}, info_click()};
	win.attach(info);

	while (true) {
		if (win.click_has_been_registered()) {
			if (!dyn_t.is_transforming()) {
				dyn_t.enable_transform();
				hacky_redraw_tile(pass_to_callback);
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
					TRITI::Bary_coords b{TRITI::bary(corner,
					                                 tiles.point(0),
					                                 tiles.point(1),
					                                 tiles.point(2))};
					// ss << "Corner " << i << ": "
					//    << (is_inside_tri(b) ? "IN" : "OUT") << ' ';
				}
				win.log(ss.str());
				// win.log("TRANSFORMING?: "
				//         + std::string(dyn_t.is_transforming() ? "TRUE" : "FALSE")
				//         + "\n");
				// win.log(ss.str() + "\n");
				// win.log("New pos: " + std::to_string(tiles.point(0).x) + ", "
				//         + std::to_string(tiles.point(0).y) + "\n");
			} else {
				dyn_t.apply_transform();
				dyn_t.disable_transform();
				tiles.update_transform(win.click_position(),
				                       dyn_t.side_length(),
				                       dyn_t.angle());
				info.set_label(info_click());
			}
		}
		win.wait_for_click();
		win.log("CLICK!\n");
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


