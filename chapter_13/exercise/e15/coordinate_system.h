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
	void set_rotation(float angle) { r = angle; };
	void flip_y_axis() { flip_y = !flip_y; };
private:
	Graph_lib::Point o;
	float r;
	bool flip_y = false;
};

inline Graph_lib::Point Coordinate_system::to_screen(Graph_lib::Point point) const
{
	float cos_r = cos(r);
	float sin_r = sin(r);
	float x = point.x * cos_r - point.y * sin_r;
	float y = point.x * sin_r + point.y * cos_r;

	x += o.x;
	y += o.y;

	if (flip_y) {
		y = -y;
	}

	return Graph_lib::Point{static_cast<int>(x), static_cast<int>(y)};
}

inline Graph_lib::Point Coordinate_system::to_local(Graph_lib::Point point) const
{
	float x = point.x - o.x;
	float y = point.y - o.y;
	if (flip_y) {
		y = -y;
	}

	float cos_r = cos(-r);
	float sin_r = sin(-r);
	float new_x = x * cos_r - y * sin_r;
	float new_y = x * sin_r + y * cos_r;

	return Graph_lib::Point{static_cast<int>(new_x), static_cast<int>(new_y)};
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

inline Bounds bounds_from_points(const std::vector<Graph_lib::Point>& pts)
{
	if (pts.size() == 0) {
		throw std::runtime_error(
		    "Cannot calculate bounds, vector<Point> is empty");
	}
	Coord_sys::Bounds bnds{};
	for (int i = 0; i < pts.size(); ++i) {
		Graph_lib::Point pt = pts[i];
		if (i == 0) {
			bnds = {pt, pt};
			continue;
		}
		if (pt.x < bnds.min.x) {
			bnds.min.x = pt.x;
		}
		if (pt.x > bnds.max.x) {
			bnds.max.x = pt.x;
		}
		if (pt.y < bnds.min.y) {
			bnds.min.y = pt.y;
		}
		if (pt.y > bnds.max.y) {
			bnds.max.y = pt.y;
		}
	}
	return bnds;
}

} // namespace Coord_sys
#endif // COORDINATE_SYSTEM_H
