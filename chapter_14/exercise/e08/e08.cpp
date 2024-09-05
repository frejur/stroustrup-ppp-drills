#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/anim/anim_shp.h"
#include "../share/geo/regularpoly.h"

// Exercise 8. Create a (Regular) 'Octagon' Shape class and test its functions.

// Notes:
// - Reused Regular_polygon code from the previous chapters as the base class.
// - Changed Regular_polygon class, implemented the following methods:
//   + move(int offset_x, int offset_y)
//   + scale(double scale_factor)
//   + rotate(double offset_degrees)
// - Changes to some of Regular_poly's interface and implementation logic,
//   (e.g. Initial placement is now based on the center point)
// - Test the above methods by creating an Octagon object and animating it.

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

void e08()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{ 640 };
	constexpr int win_h{ 480 };
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "Playpen",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);

	Graph_lib::Text info{{64, 32}, info_start()};
	win.attach(info);

	RPOL::RegularPolygon rp{c, 64, 8};
	rp.set_fill_color(Graph_lib::Color::invisible);

	win.attach(rp);

	anim::Window_and_shape pass_to_callback{win, rp};

	int count_clicks = 0;
	int is_animating = false;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!is_animating) {
				// Start
				rp.set_fill_color(colors()[count_clicks++ % colors().size()]);
				rp.set_color(colors()[count_clicks % colors().size()]);
				rp.set_style(styles()[(count_clicks + 1) % styles().size()]);
				info.set_label(info_stop());
				is_animating = true;
				anim::hacky_redraw_shape(pass_to_callback);
			} else {
				// Stop
				info.set_label(info_start());
				is_animating = false;
				anim::hacky_redraw_shape(pass_to_callback, true);
			}
		}
		win.wait_for_click();
	}
}

int main() {
	try {
		e08();
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
