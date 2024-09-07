#define _USE_MATH_DEFINES
#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/anim/anim_shp.h"
#include "../share/geo/regularpoly.h"
#include "../share/grp/grp_rpoly.h"
#include <cmath>

// Exercise 9. Define class "Group" that stores 'Shape's in a Vector_ref and
//             provides 'suitable operations' for its objects.
//             Use this to draw a checkers board where game pieces can be moved.

// Notes:
// - Define class 'Shape_group', derive 'R_poly_group' and use this instead.
// - Interpret 'Suitable operations' as:
//     + Global operations (Acts on all contained shapes):
//         > move(int offset_x, int offset_y)
//         > set_color(Graph_lib::Color col)
//         > set_style(Graph_lib::Line_style sty)
//         > set_fill_color(Graph_lib::Color col)
//     + Container operations (Wrapper methods for Vector_ref):
//         > add(Graph_lib::Shape& shape)
//         > add(Graph_lib::Shape* shape)
//         > number_of_elements()
//     + Individual element operations:
//         > (All of the global operations with the addition of an 'index' parameter)
//     + Uniquely for 'R_poly_group':
//         > add(Graph_lib::Point center, int radius, int number_of_sides, double angle_degrees)
//         > (Redefine the add() methods defined in 'Shape_group' as empty private methods to prevent their use)
//     + Also uniquely for 'R_poly_group':
//         > scale(double scale_factor)
//         > rotate(double offset_degrees)
//         > scale(double scale_factor, int element_index)
//         > rotate(double offset_degrees, int element_index)
//         > radius(int element_index)
//         > center(int element_index)
// - Define class 'Checker_board' that contains
//     + A single 4-sided Regular_polygon 'frame'.
//     + Four 'R_poly_groups':
//         1. Light tiles x 50
//         2. Dark tiles x 50
//         3. Light pieces x 20
//         4. Dark pieces x 20
// - Implement 'Checker_board' wrapper methods for:
//     + Global operations:
//         > move(int offset_x, int offset_y)
//         > scale(double scale_factor)
//         > rotate(double offset_degrees)
//     + Individual operation for the tiles:
//         > center(int tile_num)
//     + Individual operations for the pieces:
//         > move_light_piece(int piece_num, int target_tile_num)
//         > move_dark_piece(int piece_num, int target_tile_num)
//         > move_light_piece(int piece_num, int offset_x, int offset_y)
//         > move_dark_piece(int piece_num, int offset_x, int offset_y)
//         > light_piece_center(int piece_num)
//         > dark_piece_center(int piece_num)
//         > light_piece_radius(int piece_num)
//         > dark_piece_radius(int piece_num)
//         > light_piece_angle(int piece_num)
//         > dark_piece_angle(int piece_num)
// - Implement 'Checker_board' getter functions related to the board as a whole:
//     + width()
//     + height()
//     + center()
//     + angle()
// - Implement operations for the individual 'parts' of the board:
//     + set_frame_color(Graph_lib::Color col)
//     + set_dark_tile_color(Graph_lib::Color col)
//     + set_light_tile_color(Graph_lib::Color col)
//     + set_dark_piece_color(Graph_lib::Color col)
//     + set_light_piece_color(Graph_lib::Color col)

const std::string& info_start()
{
	static const std::string s{"Click to start the animation."};
	return s;
}

const std::string& info_stop()
{
	static const std::string s{"Click to STOP."};
	return s;
}
const std::vector<Graph_lib::Color>& colors()
{
	static const std::vector<Graph_lib::Color>& c{Graph_lib::Color::dark_magenta,
	                                              Graph_lib::Color::yellow,
	                                              Graph_lib::Color::dark_green,
	                                              Graph_lib::Color::white};
	return c;
}

const std::vector<Graph_lib::Line_style>& styles()
{
	static const std::vector<Graph_lib::Line_style>
	    s{Graph_lib::Line_style(Graph_lib::Line_style::dash, 5),
	      Graph_lib::Line_style(Graph_lib::Line_style::solid, 10),
	      Graph_lib::Line_style(Graph_lib::Line_style::dot, 3)};
	return s;
}

//------------------------------------------------------------------------------

class Board_animator : public anim::Shape_animator
{
public:
	using anim::Shape_animator::Shape_animator;

private:
	void animate() override
	{
		grp_shp::R_poly_group& p = dynamic_cast<grp_shp::R_poly_group&>(
		    ws.shape);
		p.move(1, 1);
		// p.rotate(10);
		p.rotate_around_origin(1);
		if (std::fmod(time(), 0.5) <= refresh_rate()) {
			// p.add(p.center(0), 10, 8);
		}
		// p.rotate(-10, 1);
	};
};

//------------------------------------------------------------------------------

void e09()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{640};
	constexpr int win_h{640};
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Older than J-Dawg",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);

	Graph_lib::Text info{{64, 32}, info_start()};
	win.attach(info);

	grp_shp::R_poly_group grp{c};
	grp.add({c.x - 100, c.y}, static_cast<int>(win_w * 0.25), 4);
	grp.add({c.x + 100, c.y}, static_cast<int>(win_w * 0.25), 4);

	win.attach(grp);

	Board_animator anim{win, grp};

	int count_clicks = 0;
	int is_animating = false;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!is_animating) {
				// Start
				grp.set_fill_color(colors()[count_clicks++ % colors().size()]);
				grp.set_color(colors()[count_clicks % colors().size()]);
				info.set_label(info_stop());
				is_animating = true;
				anim.start();
			} else {
				// Stop
				info.set_label(info_start());
				is_animating = false;
				anim.stop();
			}
		}
		win.wait_for_click();
	}
}

int main() {
	try {
		e09();
		return 0;
	} catch (exception& e) {
		std::cerr << "Error: " << e.what() << '\n';
		return 1;
	} catch (...) {
		std::cerr << "Unknown error\n";
		return 2;
	}
	return 0;
}
