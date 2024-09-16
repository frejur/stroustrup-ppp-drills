#define _USE_MATH_DEFINES
#include "e10_anim.h"
#include "e10_pnp.h"
#include "e10_pswin.h"
#include <cmath>

//------------------------------------------------------------------------------

void ch14_e10::Pacman_animator::add_move(int pill_index, pac::Pacman_dir dir)
{
	moves.push_back({pill_index, dir});
}

std::pair<int, pac::Pacman_dir> ch14_e10::Pacman_animator::get_move(
    int pill_index)
{
	int idx = -1; // Returns {-1, dir} if no move is found
	pac::Pacman_dir dir = static_cast<pac::Pacman_dir>(0);
	for (int i = 0; i < moves.size(); ++i) {
		if (moves[i].first == pill_index) {
			idx = i;
			dir = moves[i].second;
			break;
		}
	}
	return {idx, dir};
}

//------------------------------------------------------------------------------

void ch14_e10::Pacman_animator::animate()
{
	Pac_and_pills& p = dynamic_cast<Pac_and_pills&>(ws.shape);
	bool has_pills = pill_count <= p.number_of_pills() - 1;

	if (time() < refresh_rate() * 1.5) {
		// First frame
		pill_count = 0;
		jaw_open = true;
	}

	float jaw_speed = jaw_open ? -0.4 : 0.4;
	p.set_jaw_state(p.jaw_state() + jaw_speed);
	if (p.jaw_state() == 1 || p.jaw_state() == 0) {
		jaw_open = !jaw_open;
	}

	int pac_speed = 30;
	Graph_lib::Point move_v = p.direction_vector();
	move_v.x *= pac_speed;
	move_v.y *= pac_speed;

	Graph_lib::Point curr_pos = p.pacman_position();
	Graph_lib::Point pill_pos = !has_pills ? Graph_lib::Point{0, 0}
	                                       : p.pill_position(pill_count);

	// Check if new position is on top of, or moves past pill
	Graph_lib::Point new_pos{curr_pos.x + move_v.x, curr_pos.y + move_v.y};
	bool ontop_of_pill = has_pills
	                     && (new_pos.x == pill_pos.x && new_pos.y == pill_pos.y);
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
		passes_pill = (dot_a >= 0 && dot_b < 0) || (dot_a < 0 && dot_b >= 0);
	}

	if (ontop_of_pill || passes_pill) {
		std::pair<int, pac::Pacman_dir> m = get_move(pill_count);
		if (m.first > -1) {
			p.set_pacman_direction(m.second);
			new_pos.x = pill_pos.x;
			new_pos.y = pill_pos.y;
		}
		p.hide_pill(pill_count);
		++pill_count;
	}
	int offs_x = new_pos.x - curr_pos.x;
	int offs_y = new_pos.y - curr_pos.y;
	p.move_pacman(offs_x, offs_y);
};

void ch14_e10::Pacman_animator::finish()
{
	pill_count = 0;
	jaw_open = true;
	ch14_e10::Pac_and_pills& p = dynamic_cast<Pac_and_pills&>(ws.shape);
	p.reset();
}

//------------------------------------------------------------------------------

void ch14_e10::Window_animator::animate()
{
	ch14_e10::Pseudo_window& p = dynamic_cast<Pseudo_window&>(ws.shape);
	if (time() < refresh_rate() * 1.5) {
		// First frame
		curr_step = 0;
	}
	if (curr_step > steps) {
		return;
	}
	if (curr_step == steps) {
		p.move(tgt.x - p.origin().x, tgt.y - p.origin().y);
	} else {
		int step_x = static_cast<int>(std::round((tgt.x - o.x) / steps));
		int step_y = static_cast<int>(std::round((tgt.y - o.y) / steps));
		p.move(step_x, step_y);
	}
	++curr_step;
};

void ch14_e10::Window_animator::finish()
{
	ch14_e10::Pseudo_window& p = dynamic_cast<Pseudo_window&>(ws.shape);
	p.move(o.x - p.origin().x, o.y - p.origin().y);
}
