#define _USE_MATH_DEFINES
#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/anim/anim_shp.h"
#include "../share/geo/pac.h"
#include <cmath>

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
	                 "In da face",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);

	bool is_animating{false};
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!is_animating) {
				// Start
				is_animating = true;
			} else {
				// Stop
				is_animating = false;
			}
		}
		win.wait_for_click();
	}
}

int main() {
	try {
		e16();
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
