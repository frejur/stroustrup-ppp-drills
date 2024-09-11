#include "e10_pac.h"
#include "e10_pswin.h"
#define _USE_MATH_DEFINES
#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
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
	constexpr int ps_win_h{200};
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "See(m)",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);

	Graph_lib::Text info{{64, 32}, info_start()};
	win.attach(info);

	Pac_and_pills pnp{{c.x - ps_win_w / 6 * 4, c.y - ps_win_w},
	                  64,
	                  1,
	                  Pacman_dir::Down,
	                  inactive_color()};
	for (int i = 0; i < 4; ++i) {
		pnp.add_pill({pnp.pacman_position().x,
		              pnp.pacman_position().y + ps_win_w / 3 * (i + 1)});
	}
	for (int j = 0; j < 4; ++j) {
		pnp.add_pill({pnp.pill_position(3).x + ps_win_w / 6 * 8,
		              pnp.pill_position(3).y - ps_win_w / 3 * j});
	}
	Pacman_animator anim_pac{win, pnp};

	Pac_and_pills pnp_win{{c.x - ps_win_w / 6 * 4, c.y - ps_win_w},
	                      64,
	                      1,
	                      Pacman_dir::Down,
	                      Graph_lib::Color::yellow};
	pnp_win.add_pill(
	    {pnp.pacman_position().x, pnp.pacman_position().y + ps_win_w / 3 * 5});
	for (int k = 0; k < 3; ++k) {
		pnp_win.add_pill(
		    {c.x - ps_win_w / 3 + ps_win_w / 3 * k, c.y + ps_win_w / 3});
	}
	pnp_win.add_pill({pnp.pill_position(3).x + ps_win_w / 6 * 8,
	                  pnp.pill_position(3).y - ps_win_w / 3});
	Pacman_animator anim_win{win, pnp_win};

	Pseudo_window ps{{c.x - ps_win_w / 2, c.y - ps_win_h / 2 + ps_win_w / 3},
	                 ps_win_w,
	                 ps_win_h};
	win.attach(pnp);
	win.attach(ps);
	ps.attach(pnp_win);

	int is_animating = false;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!is_animating) {
				// Start
				info.set_label(info_stop());
				is_animating = true;
				anim_pac.start();
				anim_win.start();
			} else {
				// Stop
				info.set_label(info_start());
				is_animating = false;
				anim_pac.stop();
				anim_win.stop();
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
