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
	    , new_s(side_len)
	    , new_a(angle)
	    , new_o(origin)
	    , t(type)
	{
		if (!valid_min_max(min_side_len, max_side_len)) {
			throw std::runtime_error("Invalid parameters");
		}
		cap_parms(side_len, angle);
		tile = new_tile(type);
		tile->set_color(GL::Color::black);
	};
	void draw_lines() const { tile->draw(); };
	bool is_transforming() const { return is_xform; };
	void cue_transform(GL::Point new_origin, int new_side_len, float new_angle)
	// Register new transform values
	{
		if (!is_transforming()) {
			return;
		}
		if (new_origin != o) {
			o = new_origin;
		}
		cap_parms(new_s, new_a);
		s = new_s;
		a = new_a;
	}
	void apply_transform()
	// Replace current tile with a newly transformed tile
	{
		if (s == new_s && a == new_a && o == new_o) {
			return;
		}
		tile = new_tile(t);
	};
	void enable_transform() { is_xform = true; };
	void disable_transform() { is_xform = false; };
	GL::Point origin() const { return o; };
	int side_length() const { return s; };
	float angle() const { return a; };

private:
	bool is_xform = false;
	const int min_s;
	const int max_s;
	int s;
	float a;
	GL::Point o;
	int new_s;
	float new_a;
	GL::Point new_o;
	Tile_type t;
	bool valid_min_max(int min_side_len, int max_side_len) const
	{
		return !(min_side_len >= max_side_len || s < min_side_len
		         || s > max_side_len);
	}
	void cap_parms(int side_len, float angle)
	{
		if (side_len < min_s) {
			s = min_s;
		} else if (side_len > max_s) {
			s = max_s;
		}
		// TODO: Implement wrap-around
		if (angle < 0) {
			a = 0;
		} else if (angle > 360) {
			a = 360;
		}
	}
	std::unique_ptr<GL::Closed_polyline> tile;
	std::unique_ptr<GL::Closed_polyline> new_tile(Tile_type type)
	{
		if (type == Tile_type::Right_triangle) {
			GL::Point in_end{static_cast<int>(std::round(o.x + cos(a) * s)),
			                 static_cast<int>(std::round(o.y + sin(a) * s))};
			return std::make_unique<RTRI::RightTriangle>(o, in_end);
		} else {
			throw std::runtime_error("Not implemented yet");
		}
	};
};

struct Tile_and_window
{
	Debug_window& win;
	Dynamic_tile& tile;
};

static void transform_tile_cb(void* data)
{
	static float time = 0;
	time += refresh_rate;
	Tile_and_window* tw = static_cast<Tile_and_window*>(data);
	if (!tw->tile.is_transforming() || time >= refresh_time_out) {
		tw->tile.disable_transform();
		// TODO: Force click window to snap out of it
		Fl::remove_timeout(transform_tile_cb, data);
	} else {
		tw->tile.cue_transform(tw->win.mouse_position(),
		                       tw->tile.side_length(),
		                       tw->tile.angle());
		tw->tile.apply_transform();
		Fl::repeat_timeout(refresh_rate, transform_tile_cb, data);
	}
}
void hacky_redraw_tile(Tile_and_window& tw)
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

	Dynamic_tile dyn_t{Tile_type::Right_triangle, o, 64, 0};
	win.attach(dyn_t);

	Tile_and_window pass_to_callback{win, dyn_t};

	GL::Text info{{64, 32}, info_click()};
	win.attach(info);

	while (true) {
		if (win.click_has_been_registered()) {
			if (!dyn_t.is_transforming()) {
				dyn_t.enable_transform();
				hacky_redraw_tile(pass_to_callback);
				dyn_t.enable_transform();
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
				dyn_t.disable_transform();
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


