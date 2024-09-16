#ifndef PACMAN_H
#define PACMAN_H
#include "../grp/grp_shp.h"
#include <algorithm>

constexpr float pacman_open_jaw_angle{75};

namespace pac {

enum class Pacman_dir { Up = -1, Right, Down, Left };

class Pacman : public Graph_lib::Circle
{
public:
	Pacman(Graph_lib::Point center,
	       int radius,
	       float jaw_state = 1,
	       Pacman_dir start_dir = Pacman_dir::Right)
	    : Circle(center, radius)
	    , jaw(valid_jaw(jaw_state))
	    , dir(start_dir){};
	void set_jaw_state(float jaw_state) { jaw = valid_jaw(jaw_state); };
	float jaw_state() const { return jaw; };
	Pacman_dir direction() const { return dir; };
	void set_direction(Pacman_dir new_dir) { dir = new_dir; };

protected:
	void draw_lines() const override;

private:
	float jaw; // 0 = closed, 1 = open
	Pacman_dir dir;
	float valid_jaw(float j) const
	{
		return (std::min)(1.0f, (std::max)(j, 0.0f));
	};
};

//------------------------------------------------------------------------------

class Pills : public grp_shp::Shape_group
{
public:
	using Shape_group::move;
	using Shape_group::Shape_group;
	Graph_lib::Point center(int element_index) const
	{
		const Graph_lib::Circle& p{dynamic_cast<const Graph_lib::Circle&>(
		    elem[valid_index(element_index)])};
		return p.center();
	};
};

//------------------------------------------------------------------------------

} // namespace pac

#endif // PACMAN_H
