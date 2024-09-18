#ifndef MAZE_ANIM_H
#define MAZE_ANIM_H
#include "../share/anim/anim_shp.h"
#include "maze.h"

namespace ch14_e16 {

class Maze_animator : public anim::Shape_animator
{
public:
	Maze_animator(Debug_window& win,
	              Maze& m,
	              double ref_rate = anim::refresh_rate,
	              double ref_time_out = anim::refresh_time_out)
	    : anim::Shape_animator::Shape_animator(win, m, ref_rate, ref_time_out)
	    , eof_anim(false)
	    , jaw_open(true)
	    , pill_count(0){};
	bool has_reached_end() const { return eof_anim; };
	void reset() { eof_anim = false; }
	void hide() { dynamic_cast<Maze&>(ws.shape).hide(); };
	void show() { dynamic_cast<Maze&>(ws.shape).show(); };

private:
	bool eof_anim;
	bool jaw_open;
	int pill_count;
	void animate() override;
	void finish() override;
};

} // namespace ch14_e16

#endif // MAZE_ANIM_H
