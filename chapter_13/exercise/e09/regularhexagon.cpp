#include "regularhexagon.h"
#define _USE_MATH_DEFINES
#include <math.h>

RegularHexagon::RegularHexagon(Graph_lib::Point xy, int radius)
	: RegularPolygon({ xy.x + radius, xy.y }, radius, num_sides, 90 * M_PI/180),
	side_states( std::vector<bool>(num_sides, true))
{
	Graph_lib::Shape::set_color(Graph_lib::Color::black);
}

void RegularHexagon::close_side(int n)
{
	side_states[n%num_sides] = false;
}

bool RegularHexagon::side_is_open(int n) const
{
	return side_states[n%num_sides];
}
