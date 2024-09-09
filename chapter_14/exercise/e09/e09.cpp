#include "e09_board.h"
#define _USE_MATH_DEFINES
#include "e09.h"
#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "../share/grp/grp_rpoly.h"
#include <cmath>

// Exercise 9. Define class "Group" that stores 'Shape's in a Vector_ref and
//             provides 'suitable operations' for its objects.
//             Use this to draw a checkers board where game pieces can be moved.
//             (Read 'e09_notes.md' for more details)
//------------------------------------------------------------------------------

void ch14_e09::e09()
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

	ch14_e09::Board b{c, 32};

	win.attach(b);

	Board_animator anim{win, b, 0.05, 20};

	int count_clicks = 0;
	int is_animating = false;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!is_animating) {
				// Start
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
		ch14_e09::e09();
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
