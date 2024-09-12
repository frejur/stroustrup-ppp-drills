#ifndef E10_ANIM_H
#define E10_ANIM_H
#include "../share/anim/anim_shp.h"
#include "e10_pac.h"

namespace ch14_e10 {

//------------------------------------------------------------------------------
// Moves Pacman in its current direction, turns Pacman when passing a pill
// defined in the moves vector.

class Pacman_animator : public anim::Shape_animator
{
public:
	using anim::Shape_animator::Shape_animator;
	void add_move(int pill_index, Pacman_dir dir);
	;

private:
	std::pair<int, Pacman_dir> get_move(int pill_index);
	int pill_count;
	bool jaw_open;
	std::vector<std::pair<int, Pacman_dir>> moves;
	void animate() override;
	void finish() override;
};

//------------------------------------------------------------------------------
// Moves window to target in 'x' number of steps / frames.

class Window_animator : public anim::Shape_animator
{
public:
	Window_animator(Debug_window& win,
	                Graph_lib::Shape& shape,
	                Graph_lib::Point target,
	                int num_steps,
	                double ref_rate = anim::refresh_rate,
	                double ref_time_out = anim::refresh_time_out)
	    : anim::Shape_animator(win, shape, ref_rate, ref_time_out)
	    , o(shape.point(0))
	    , tgt(target)
	    , curr_step(1)
	    , steps(num_steps){};

private:
	Graph_lib::Point o;
	Graph_lib::Point tgt;
	int curr_step;
	int steps;
	void animate() override;
	void finish() override;
};

} // namespace ch14_e10

#endif // E10_ANIM_H
