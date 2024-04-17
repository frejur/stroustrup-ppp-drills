#include "../../lib/Graph.h"
#include <exception>
#include <iostream>
#include <vector>
#include <memory>
#include "../../lib/Debug_window.h"
#include "righttriangle.h"
#include "triangletiler.h"
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <sstream>

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

static void transform_tile_cb(void* data)
{
	static float time = 0;
	time += refresh_rate;
	Debug_window* win = static_cast<Debug_window*>(data);
	if (time >= refresh_time_out) {
		Fl::remove_timeout(transform_tile_cb, data);
		win->log("Aborted\n");
	} else {
		Fl::repeat_timeout(refresh_rate, transform_tile_cb, data);
	}
}
void hacky_redraw_tile(Debug_window& win)
{
	Fl::add_timeout(refresh_rate, transform_tile_cb, (void*) &win);
}

constexpr int default_min_side_len{10};
constexpr int default_max_side_len{200};
enum class Tile_type { Right_triangle, Regular_hexagon };

class Dynamic_tile : public GL::Shape
{
public:
	Dynamic_tile(Tile_type type,
	             GL::Point origin,
	             int side_len,
	             float angle,
	             int min_side_len = default_min_side_len,
	             int max_side_len = default_max_side_len)
	    : min_s(min_side_len)
	    , max_s(max_side_len)
	    , s(side_len)
	    , a(angle)
	    , o(origin)
	{
		if (min_side_len < default_min_side_len
		    || max_side_len > default_max_side_len
		    || min_side_len >= max_side_len || s < min_side_len
		    || s > max_side_len) {
			throw std::runtime_error("Invalid parameters");
		}
		if (type == Tile_type::Right_triangle) {
			GL::Point in_end{static_cast<int>(std::round(o.x + cos(s) * s)),
			                 static_cast<int>(std::round(o.y + sin(s) * s))};
			t = std::make_unique<RTRI::RightTriangle>(o, in_end);
		} else {
			throw std::runtime_error("Not implemented yet");
		}
	};

private:
	bool is_transforming = false;
	const int min_s;
	const int max_s;
	int s;
	float a;
	GL::Point o;
	std::unique_ptr<GL::Closed_polyline> t;
};

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

	GL::Text info{{64, 32}, info_click()};
	win.attach(info);

	bool placing_tile = false;
	while (true) {
		if (win.click_has_been_registered()) {
			if (!placing_tile) {
				placing_tile = true;
				info.set_label(info_transform());
				tiles.move_to(win.click_position());
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
					ss << "Corner " << i << ": "
					   << (is_inside_tri(b) ? "IN" : "OUT") << ' ';
				}
				// win.log(ss.str() + "\n");
				// win.log("New pos: " + std::to_string(tiles.point(0).x) + ", "
				//         + std::to_string(tiles.point(0).y) + "\n");
			} else {
				placing_tile = false;
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


