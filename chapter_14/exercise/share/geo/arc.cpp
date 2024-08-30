#include "arc.h"
#include <exception>
#include <algorithm>
#include <cmath>

using namespace Arc_geo;

//------------------------------------------------------------------------------

bool Arc_geo::areaIsZero(int w, int h)
{
	return w * h == 0;
}

//------------------------------------------------------------------------------

Quarter_arc::Quarter_arc(Graph_lib::Point o, Graph_lib::Point e, bool flip)
    : w{0}
    , h{0}
    , ox{o.x}
    , oy{o.y}
{
    if (o.x == e.x || o.y == e.y) {
        throw std::logic_error(
            "Trying to create a zero area Arc");
    }
	Q_arc_dir dir = getDirection(o, e);
	setSize(o, e);
	setOrigin(o, e);
	setEnd(o, e);
	setOffset(dir, flip);
	setAngles(dir, flip);
}

Q_arc_dir Quarter_arc::getDirection(const Graph_lib::Point& o,
                                    const Graph_lib::Point& e)
{
	if (e.x > o.x && o.y > e.y) {
		return Q_arc_dir::NE;
	}
	if (e.x > o.x && e.y > o.y) {
		return Q_arc_dir::SE;
	}
	if (o.x > e.x && e.y > o.y) {
		return Q_arc_dir::SW;
	}
	return Q_arc_dir::NW;
}
void Quarter_arc::setOrigin(const Graph_lib::Point& o, const Graph_lib::Point& e)
{
	if (areaIsZero(w, h)) {
		throw std::logic_error("Cannot set origin of Arc, area is zero");
	}
	ox = (std::min)(o.x, e.x);
	oy = (std::min)(o.y, e.y);
}
void Quarter_arc::setOffset(Q_arc_dir dir, bool flip)
{
	if (areaIsZero(w, h)) {
		throw std::logic_error("Cannot set origin of Arc, area is zero");
	}
	switch (dir) {
	case Q_arc_dir::SE:
		offs_x = !flip ? 0 : w;
		offs_y = !flip ? h : 0;
		break;
	case Q_arc_dir::SW:
		offs_x = !flip ? w : 0;
		offs_y = !flip ? h : 0;
		break;
	case Q_arc_dir::NW:
		offs_x = !flip ? w : 0;
		offs_y = !flip ? 0 : h;
		break;
	default:
		offs_x = !flip ? 0 : w;
		offs_y = !flip ? 0 : h;
	}
}

void Quarter_arc::setEnd(const Graph_lib::Point& o, const Graph_lib::Point& e)
{
	if (areaIsZero(w, h)) {
		throw std::logic_error("Cannot set end point of Arc, area is zero");
	}
	ex = (std::max)(o.x, e.x);
	ey = (std::max)(o.y, e.y);
}

void Quarter_arc::setSize(const Graph_lib::Point& o, const Graph_lib::Point& e)
{
    w = std::abs(o.x - e.x);
    h = std::abs(o.y - e.y);
}

void Quarter_arc::setAngles(Q_arc_dir dir, bool flip)
{
    switch ( dir ) {
	case Q_arc_dir::NE:
		a1 = !flip ? 90 : 270;
		break;
	case Q_arc_dir::SE:
		a1 = !flip ? 180 : 0;
		break;
	case Q_arc_dir::SW:
		a1 = !flip ? 270 : 90;
		break;
	default:
		a1 = !flip ? 0 : 180;
	}
	a2 = a1 + 90;
}

void Quarter_arc::draw_lines() const
{
	if (color().visibility()) {
		fl_arc(ox - offs_x, oy - offs_y, w * 2, h * 2, a1, a2);
	}
}

//------------------------------------------------------------------------------

Semi_arc::Semi_arc(Graph_lib::Point base,
                   int width,
                   int height,
                   S_arc_dir direction)
    : b(base)
    , w(width)
    , h(height)
    , dir(direction)
    , min_pt(bbox_min(b, w, h, dir))
    , max_pt(bbox_max(b, w, h, dir))
    , a1(start_angle(direction))
    , a2(a1 + 180)
{}

Graph_lib::Point Semi_arc::bbox_min(Graph_lib::Point base,
                                    int width,
                                    int height,
                                    S_arc_dir direction) const
{
	int half_w{static_cast<int>(width * 0.5)};
	switch (direction) {
	case S_arc_dir::Up:
	case S_arc_dir::Down: {
		return {b.x - half_w, b.y - height};
	}
	case S_arc_dir::Right:
	case S_arc_dir::Left:
		return {b.x - height, b.y - half_w};
	}

	throw std::runtime_error("Invalid direction");
	return {0, 0};
}

void Semi_arc::draw_lines() const
{
	if (color().visibility()) {
		fl_arc(min_pt.x,
		       min_pt.y,
		       max_pt.x - min_pt.x,
		       max_pt.y - min_pt.y,
		       a1,
		       a2);
	}
}
