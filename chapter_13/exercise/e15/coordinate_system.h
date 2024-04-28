#ifndef COORDINATE_SYSTEM_H
#define COORDINATE_SYSTEM_H

#include "../../lib/Graph.h"
#include <cmath>
#define _USE_MATH_DEFINES

namespace Coord_sys {

class Coordinate_system
{
public:
	Coordinate_system(Graph_lib::Point origin, float rotation = 0)
	    : o(origin)
	    , r(rotation){};
	Graph_lib::Point to_screen(Graph_lib::Point point) const;
	Graph_lib::Point to_local(Graph_lib::Point point) const;
	Graph_lib::Point origin() const { return o; };
	void flip_y_axis() { flip_y = !flip_y; };
private:
	Graph_lib::Point o;
	float r;
	bool flip_y = true;
};

inline Graph_lib::Point Coordinate_system::to_screen(Graph_lib::Point point) const
{
	float x = point.x * cos(r) - point.y * sin(r);
	float y = point.x * sin(r) + point.y * cos(r);

	x += o.x;
	y += o.y;

	if (flip_y) y = -y;

	return Graph_lib::Point{static_cast<int>(x), static_cast<int>(y)};
}

inline Graph_lib::Point Coordinate_system::to_local(Graph_lib::Point point) const
{
	float y = point.y;
	if (flip_y) y = -y;

	float x = point.x - o.x;
	y -= o.y;

	x = x * cos(-r) - y * sin(-r);
	y = x * sin(-r) + y * cos(-r);

	return Graph_lib::Point{static_cast<int>(x), static_cast<int>(y)};
}

struct Bounds
{
	Graph_lib::Point min;
	Graph_lib::Point max;
};

inline bool is_inside(Graph_lib::Point p, Bounds bounds)
{
	return (p.x >= bounds.min.x) && (p.x <= bounds.max.x)
		&& (p.y >= bounds.min.y) && (p.y <= bounds.max.y);
}

inline bool is_inside(Graph_lib::Point p,
                      Bounds bounds,
                      const Coordinate_system& cs)
{
	return is_inside(cs.to_local(p), bounds);
}

} // namespace Coord_sys
#endif // COORDINATE_SYSTEM_H
