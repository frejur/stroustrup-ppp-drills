#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
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

const std::string& info_click()
{
	static const std::string s{"Click anywhere to start the animation."};
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

	Graph_lib::Text info{{64, 32}, info_click()};
	win.attach(info);

	RPOL::RegularPolygon rp{{win_w / 2, win_h / 2}, 64, 8};
	win.attach(rp);

	RPOL::RegularPolygon rp2{{win_w / 2, win_h / 2}, 64, 8};
	rp2.rotate(-362.5);
	win.attach(rp2);

	int count_logged = 0;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			win.log("Let's boogey!");
			++count_logged;
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
