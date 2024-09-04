#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/anim/anim_shp.h"
#include "../share/geo/regularpoly.h"
#include <cmath>

// Exercise 8. Create a (Regular) 'Octagon' Shape class and test its functions.

// Notes:
// - Reused Regular_polygon code from the previous chapters as the base class.
// - Changed Regular_polygon class, implemented the following methods:
//   + move(int offset_x, int offset_y)
//   + scale(double scale_factor)
//   + rotate(double offset_degrees)
// - Changes to some of Regular_poly's interface and implementation logic,
//   (e.g. Initial placement is now based on the center point)
// - Test the above methods by creating an Octagon and animating it.

const std::string& info_start()
{
	static const std::string s{"Click to start the animation."};
	return s;
}

const std::string& info_stop()
{
	static const std::string s{"Click to stop the animation."};
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

	RPOL::RegularPolygon rp{{win_w / 2, win_h / 2}, 64, 8};
	win.attach(rp);

	anim::Window_and_shape pass_to_callback{win, rp};

	int count_logged = 0;
	int is_animating = false;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (is_animating) {
				info.set_label(info_start());
				is_animating = false;
				anim::hacky_redraw_shape(pass_to_callback, true);
			} else {
				info.set_label(info_stop());
				++count_logged;
				is_animating = true;
				anim::hacky_redraw_shape(pass_to_callback);
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
