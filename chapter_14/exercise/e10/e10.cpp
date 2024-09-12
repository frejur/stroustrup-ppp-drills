#define _USE_MATH_DEFINES
#include "../../lib/Debug_window.h"
#include "../../lib/Graph.h"
#include "e10.h"

// Exercise 10. Define class 'Pseudo_window', a group of shapes that mimics the
//              appearance of a Window with the following features:
//              - Rounded corners.
//              - A title.
//              - Buttons: Minimize, maximize, close.
//              - Some kind of fake content.
//
//              The window "need not do anything" and should appear within a
//              'Simple_window'.
// Additions:
// - Clip content to window.
// - Animate Pseudo_window movement (And some more stuff).
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

	Graph_lib::Text info{{256, 64}, info_start()};
	win.attach(info);

	// Content visible in the background ---------------------------------------
	Pac_and_pills pnp_bg{{c.x - ps_win_w / 6 * 4, c.y - ps_win_w},
	                     64,
	                     1,
	                     Pacman_dir::Down,
	                     inactive_color(),
	                     inactive_color()};
	for (int i = 0; i < 4; ++i) {
		pnp_bg.add_pill({pnp_bg.pacman_position().x,
		                 pnp_bg.pacman_position().y + ps_win_w / 3 * (i + 1)});
	}
	for (int j = 0; j < 4; ++j) {
		pnp_bg.add_pill({pnp_bg.pill_position(3).x + ps_win_w / 6 * 8,
		                 pnp_bg.pill_position(3).y - ps_win_w / 3 * j});
	}
	win.attach(pnp_bg);

	Pacman_animator anim_pac{win, pnp_bg};
	anim_pac.add_move(3, Pacman_dir::Right);
	anim_pac.add_move(4, Pacman_dir::Up);

	// Content visible in the Pseudo_window ------------------------------------
	Pac_and_pills pnp_win{{c.x - ps_win_w / 6 * 4, c.y - ps_win_w},
	                      64,
	                      1,
	                      Pacman_dir::Down,
	                      Graph_lib::Color::yellow,
	                      Graph_lib::Color::white};
	pnp_win.add_pill(pnp_bg.pill_position(3));
	for (int k = 0; k < 3; ++k) {
		pnp_win.add_pill({pnp_bg.pill_position(3).x + ps_win_w / 3 * (k + 1),
		                  pnp_bg.pill_position(3).y});
	}
	pnp_win.add_pill(pnp_bg.pill_position(4));

	pnp_win.detach_pacman(); // Only move pills when the container moves

	Pacman_animator anim_pills{win, pnp_win};
	anim_pills.add_move(0, Pacman_dir::Right);
	anim_pills.add_move(4, Pacman_dir::Up);

	// Pseudo_window -----------------------------------------------------------
	Graph_lib::Point ps_o{c.x - ps_win_w / 2, c.y - ps_win_h / 2 + ps_win_w / 3};
	Pseudo_window ps{ps_o, ps_win_w, ps_win_h};
	win.attach(ps);
	ps.attach(pnp_win); // Note: Attached to Pseudo_window

	// Pseudo_window has been created at the end / target position:
	// -> Move to starting position
	ps.move(50, c.y - pnp_bg.pill_position(3).y - 50);

	Window_animator anim_win{win, ps, ps_o, 10};

	// Event loop --------------------------------------------------------------
	int is_animating = false;
	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (!is_animating) {
				// Start
				info.set_label(info_stop());
				is_animating = true;
				anim_pac.start();
				anim_pills.start();
				anim_win.start();
			} else {
				// Stop
				info.set_label(info_start());
				is_animating = false;
				anim_pac.stop();
				anim_pills.stop();
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
