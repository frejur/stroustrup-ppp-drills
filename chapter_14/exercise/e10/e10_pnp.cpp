#include "e10_pnp.h"

ch14_e10::Pac_and_pills::Pac_and_pills(Graph_lib::Point start_pos,
                                       int radius,
                                       int jaw_state,
                                       pac::Pacman_dir direction,
                                       Graph_lib::Color pacman_color,
                                       Graph_lib::Color pill_color)
    : Graph_lib::Shape()
    , start_p(start_pos)
    , start_jaw(jaw_state)
    , start_dir(direction)
    , pac(start_pos, radius, jaw_state, direction)
    , pills(start_pos)
{
	set_color(pacman_color);
	set_fill_color(pill_color);
	pac.set_color(Graph_lib::Color::invisible);
	pills.set_color(Graph_lib::Color::invisible);
	reset_colors();
}

//------------------------------------------------------------------------------

void ch14_e10::Pac_and_pills::move(int offset_x, int offset_y)
{
	if (pacman_is_attached()) {
		pac.move(offset_x, offset_y); // Only move the pills
	}
	pills.move(offset_x, offset_y);
}

void ch14_e10::Pac_and_pills::reset()
{
	pac.move(start_p.x - pac.center().x, start_p.y - pac.center().y);
	pac.set_jaw_state(start_jaw);
	pac.set_direction(start_dir);
	reset_colors();
}

void ch14_e10::Pac_and_pills::reset_colors()
{
	pac.set_fill_color(color());
	pills.set_fill_color(fill_color());
}

void ch14_e10::Pac_and_pills::draw_lines() const
{
	pac.draw();
	pills.draw();
}

void ch14_e10::Pac_and_pills::add_pill(Graph_lib::Point pos)
{
	pills.add(new Graph_lib::Circle{pos, static_cast<int>(pac.radius() / 8)});
	pills.set_color(Graph_lib::Color::invisible, pills.number_of_elements() - 1);
	pills.set_fill_color(fill_color(), pills.number_of_elements() - 1);
}

Graph_lib::Point ch14_e10::Pac_and_pills::direction_vector() const
{
	switch (pac.direction()) {
	case pac::Pacman_dir::Up:
		return {0, -1};
	case pac::Pacman_dir::Right:
		return {1, 0};
	case pac::Pacman_dir::Down:
		return {0, 1};
	case pac::Pacman_dir::Left:
	default:
		return {-1, 0};
	}
}
