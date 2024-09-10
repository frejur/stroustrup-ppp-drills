#include "e10_pswin.h"
#define _USE_MATH_DEFINES
#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/geo/box.h"
#include "../share/grp/grp_rpoly.h"
#include "e10.h"
#include <cmath>

// Exercise 10. Define class 'Pseudo_window', a group of shapes that mimics the
//              appearance of a Window with the following features:
//              - Rounded corners.
//              - A title.
//              - Buttons: Minimize, maximize, close.
//              - Some kind of fake content.
//
//              The window "need not do anything" and should appear within a
//              'Simple_window'.
//------------------------------------------------------------------------------

void ch14_e10::e10()
{
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{640};
	constexpr int win_h{480};
	GL::Point c{ static_cast<int>(win_w*0.5), static_cast<int>(win_h*0.5) };
	constexpr int ps_win_w{320};
	constexpr int ps_win_h{240};
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "See(m)",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);

	Graph_lib::Text info{{64, 32}, info_start()};
	win.attach(info);

	BOX::Box b{{c.x - ps_win_w / 2, c.y - ps_win_h / 2},
	           ps_win_w,
	           ps_win_h,
	           6,
	           BOX::CrvMethod::Radius,
	           BOX::Flatten_side::Bottom};
	b.set_fill_color(Graph_lib::Color::blue);

	win.attach(b);

	int is_animating = false;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!is_animating) {
				// Start
				info.set_label(info_stop());
				is_animating = true;
				//anim.start();
			} else {
				// Stop
				info.set_label(info_start());
				is_animating = false;
				//anim.stop();
			}
		}
		win.wait_for_click();
	}
}

int main() {
	try {
		ch14_e10::e10();
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
