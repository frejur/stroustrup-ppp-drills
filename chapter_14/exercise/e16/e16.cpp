#define _USE_MATH_DEFINES
#include "../../lib/Debug_window.h"
#include "controller.h"
#include "maze.h"
#include "maze_anim.h"

// Chapter 14, Exercise 16
// Define class 'Controller' with 4 virtual functions:
// 1. on()
// 2. off()
// 3. set_level(int)
// 4. show()
//
// Derive 2 classes from 'Controller':
// - A test class that upon running show() prints out:
//     + The on / off status
//     + The current level
// - Another class that controls the line color of a a 'Shape'
//
// Lastly, find a third aspect that can be controlled by a 'Controller'.
//------------------------------------------------------------------------------

void toggle_controller(std::initializer_list<ch14_e16::Toggle*> ctrl)
{
	for (ch14_e16::Toggle* c : ctrl) {
		if (c->is_on()) {
			c->off();
		} else {
			c->on();
		}
	}
}

void switch_level(std::initializer_list<ch14_e16::Controller*> ctrl, int max)
{
	for (ch14_e16::Controller* c : ctrl) {
		c->set_level((c->level() + 1) % max);
	}
}

void show_controller(std::initializer_list<ch14_e16::Controller*> ctrl)
{
	for (ch14_e16::Controller* c : ctrl) {
		c->show();
	}
}

//------------------------------------------------------------------------------

void e16()
{
	using namespace ch14_e16;
	constexpr bool ENABLE_DEBUG{false};
	constexpr bool ENABLE_CLICK{true};

	constexpr int win_w{640};
	constexpr int win_h{480};
	Debug_window win{{10, 10},
	                 win_w,
	                 win_h,
	                 "In da face",
	                 ENABLE_DEBUG,
	                 ENABLE_CLICK};

	fl_color(0);

	// Maze
	const Graph_lib::Point maze_pt{150, 76};
	constexpr int tile_count{16};
	constexpr int tile_sz{24};

	Maze m_01{maze_pt, tile_count, tile_count, tile_sz};
	m_01.load_level(read_maze_from_file("lvl_01.txt"));
	win.attach(m_01);
	Maze_animator anim_m_01{win, m_01};

	Maze m_02{maze_pt, tile_count, tile_count, tile_sz};
	m_02.load_level(read_maze_from_file("lvl_02.txt"));
	win.attach(m_02);
	Maze_animator anim_m_02{win, m_02};

	Maze m_03{maze_pt, tile_count, tile_count, tile_sz};
	m_03.load_level(read_maze_from_file("lvl_03.txt"));
	win.attach(m_03);
	Maze_animator anim_m_03{win, m_03, 0.05, 20};

	Maze m_04{maze_pt, tile_count, tile_count, tile_sz};
	m_04.load_level(read_maze_from_file("lvl_04.txt"));
	win.attach(m_04);
	Maze_animator anim_m_04{win, m_04, 0.05, 20};

	Anim_controller ctrl_anim;
	ctrl_anim.add(anim_m_01);
	ctrl_anim.add(anim_m_02);
	ctrl_anim.add(anim_m_03);
	ctrl_anim.add(anim_m_04);

	// Info graphics and buttons
	Level_indicator ind_level{{32, 34}, 25};
	ind_level.set_style(Graph_lib::Line_style(Graph_lib::Line_style::solid, 4));
	Level_controller ctrl_ind_level{ind_level};
	ctrl_ind_level.show();
	win.attach(ind_level);

	Action_button btn_on_off{{64, 8}, 32, 16, 0.5};
	Action_controller ctrl_on_off{btn_on_off};
	btn_on_off.set_label("Play");
	btn_on_off.set_inactive_color(Graph_lib::Color::white);
	ctrl_on_off.off();
	win.attach(btn_on_off);

	Action_button btn_level{{64, 28}, 32, 16, 0.5};
	Action_controller ctrl_btn_level{btn_level};
	btn_level.set_label("Change level");
	btn_level.set_active_color(Graph_lib::Color::white);
	btn_level.set_inactive_color(Graph_lib::Color::invisible);
	ctrl_btn_level.on();
	win.attach(btn_level);

	Graph_lib::Text txt_status{{64, 58}, ""};
	txt_status.set_font(Graph_lib::Font::screen_bold);
	txt_status.set_font_size(8);
	Test_controller ctrl_status{txt_status};
	ctrl_status.show();
	win.attach(txt_status);

	while (win.shown()) {
		if (win.click_has_been_registered()) {
			if (ctrl_anim.has_reached_end()
			    || btn_on_off.point_is_on_button(win.click_position())) {
				toggle_controller({&ctrl_status,
				                   &ctrl_ind_level,
				                   &ctrl_on_off,
				                   &ctrl_btn_level});
				std::string new_lb = ctrl_on_off.is_on() ? "Stop" : "Play";
				btn_on_off.set_label(new_lb);
				if (ctrl_anim.has_reached_end() || !ctrl_on_off.is_on()) {
					ctrl_anim.off();
					ctrl_anim.reset();
				} else {
					ctrl_anim.on();
				}
			} else if (btn_level.point_is_on_button(win.click_position())
			           && ctrl_btn_level.is_on()) {
				switch_level({&ctrl_status, &ctrl_ind_level, &ctrl_anim},
				             ctrl_anim.number_of_animators());
			}
			show_controller({&ctrl_status, &ctrl_ind_level});
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
