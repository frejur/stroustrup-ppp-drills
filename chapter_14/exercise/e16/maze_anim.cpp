#include "maze_anim.h"
#include "../share/help/helpers.h"

void ch14_e16::Maze_animator::animate()
{
	Maze& m = dynamic_cast<Maze&>(ws.shape);
	if (!m.is_ready()) {
		eof_anim = true;
		ws.win.force_click();
		return;
	}
	bool has_pills = pill_count <= m.number_of_pills() - 1;

	if (time() < refresh_rate() * 1.5) {
		// First frame
		eof_anim = false;
		pill_count = 0;
		jaw_open = true;
	}

	float jaw_speed = jaw_open ? -0.4 : 0.4;
	m.set_jaw_state(m.jaw_state() + jaw_speed);
	if (m.jaw_state() == 1 || m.jaw_state() == 0) {
		jaw_open = !jaw_open;
	}

	int pac_speed = 10;
	Graph_lib::Point move_v = m.direction_vector();
	move_v.x *= pac_speed;
	move_v.y *= pac_speed;

	Graph_lib::Point curr_pos = m.pacman_position();
	Graph_lib::Point new_pos{curr_pos.x + move_v.x, curr_pos.y + move_v.y};

	for (int i = 0; i < m.number_of_pills(); ++i) {
		if (m.pill_has_been_eaten(i)) {
			continue;
		}
		Graph_lib::Point pill_pos{m.pill_position(i)};

		int dist = ch14_hlp::distance_between(new_pos, pill_pos);
		if (dist > pac_speed) {
			continue;
		}

		bool ontop_of_pill = has_pills
		                     && (new_pos.x == pill_pos.x
		                         && new_pos.y == pill_pos.y);
		bool passes_pill = false;
		if (has_pills && !ontop_of_pill) {
			Graph_lib::Point rel_pos_a{curr_pos.x - pill_pos.x,
			                           curr_pos.y - pill_pos.y};
			Graph_lib::Point rel_pos_b{new_pos.x - pill_pos.x,
			                           new_pos.y - pill_pos.y};
			double dot_a{static_cast<double>(rel_pos_a.x * move_v.x
			                                 + rel_pos_a.y * move_v.y)};
			double dot_b{static_cast<double>(rel_pos_b.x * move_v.x
			                                 + rel_pos_b.y * move_v.y)};
			passes_pill = (dot_a >= 0 && dot_b < 0)
			              || (dot_a < 0 && dot_b >= 0);
		}

		if (ontop_of_pill || passes_pill) {
			Pill_dir pill_d = m.pill_direction(i);
			if (pill_d != Pill_dir::No_direction) {
				new_pos = pill_pos;
				pac::Pacman_dir pac_d{};
				if (pill_d == Pill_dir::Up) {
					pac_d = pac::Pacman_dir::Up;
				} else if (pill_d == Pill_dir::Right) {
					pac_d = pac::Pacman_dir::Right;
				} else if (pill_d == Pill_dir::Down) {
					pac_d = pac::Pacman_dir::Down;
				} else if (pill_d == Pill_dir::Left) {
					pac_d = pac::Pacman_dir::Left;
				}
				m.set_direction(pac_d);
			}
			m.consume_pill(i);
			++pill_count;
		}
	}

	int offs_x = new_pos.x - curr_pos.x;
	int offs_y = new_pos.y - curr_pos.y;
	m.move_pacman(offs_x, offs_y);

	if (time() + refresh_rate() >= time_out()) {
		eof_anim = true; // To catch forced click
	}
}

void ch14_e16::Maze_animator::finish()
{
	pill_count = 0;
	jaw_open = true;
	Maze& m = dynamic_cast<Maze&>(ws.shape);
	m.reset();
}
