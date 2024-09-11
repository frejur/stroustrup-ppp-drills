#define NOMINMAX
#ifndef PACMAN_H
#define PACMAN_H
#include "../share/grp/grp_shp.h"
#include "e10.h"
#include <algorithm>

constexpr float pacman_open_jaw_angle{75};

namespace ch14_e10 {

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
		return std::min(1.0f, std::max(j, 0.0f));
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

class Pac_and_pills : public Graph_lib::Shape
{
public:
	Pac_and_pills(Graph_lib::Point start_pos,
	              int radius,
	              int jaw_state,
	              Pacman_dir direction,
	              Graph_lib::Color color)
	    : Graph_lib::Shape()
	    , start_p(start_pos)
	    , start_jaw(jaw_state)
	    , start_dir(direction)
	    , pac(start_pos, radius, jaw_state, direction)
	    , pills(start_pos)
	{
		set_color(color);
		pac.set_color(Graph_lib::Color::invisible);
		pills.set_color(Graph_lib::Color::invisible);
		reset_colors();
	};
	int number_of_pills() const { return pills.number_of_elements(); };
	void move_pacman(int offset_x, int offset_y)
	{
		pac.move(offset_x, offset_y);
	};
	void set_pacman_direction(Pacman_dir new_direction)
	{
		pac.set_direction(new_direction);
	}
	void set_jaw_state(float jaw_state) { pac.set_jaw_state(jaw_state); };
	float jaw_state() const { return pac.jaw_state(); }

	Graph_lib::Point pacman_position() const { return pac.center(); };
	Graph_lib::Point pill_position(int pill_index) const
	{
		return pills.center(pill_index);
	};

	void hide_pill(int index)
	{
		pills.set_fill_color(Graph_lib::Color::invisible, index);
	};
	void reset()
	{
		pac.move(start_p.x - pac.center().x, start_p.y - pac.center().y);
		pac.set_jaw_state(start_jaw);
		pac.set_direction(start_dir);
		reset_colors();
	}
	void reset_colors()
	{
		pac.set_fill_color(color());
		pills.set_fill_color(color());
	}

	void draw_lines() const override
	{
		pac.draw();
		pills.draw();
	};
	void add_pill(Graph_lib::Point pos)
	{
		pills.add(
		    new Graph_lib::Circle{pos, static_cast<int>(pac.radius() / 8)});
		pills.set_color(Graph_lib::Color::invisible,
		                pills.number_of_elements() - 1);
		pills.set_fill_color(color(), pills.number_of_elements() - 1);
	}
	Graph_lib::Point direction_vector() const
	{
		switch (pac.direction()) {
		case Pacman_dir::Up:
			return {0, -1};
		case Pacman_dir::Right:
			return {1, 0};
		case Pacman_dir::Down:
			return {0, 1};
		case Pacman_dir::Left:
		default:
			return {-1, 0};
		}
	}

private:
	Graph_lib::Point start_p;
	float start_jaw;
	Pacman_dir start_dir;
	Pacman pac;
	Pills pills;
};

//------------------------------------------------------------------------------

} // namespace ch14_e10

#endif // PACMAN_H
