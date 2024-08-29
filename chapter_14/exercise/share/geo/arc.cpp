#include "arc.h"
#include <exception>
#include <algorithm>
#include <cmath>

using namespace Arc_geo;

Arc::Arc(Graph_lib::Point o, Graph_lib::Point e, bool flip)
    : w{ 0 }, h{ 0 }, ox{ o.x }, oy{ o.y }
{
    if (o.x == e.x || o.y == e.y) {
        throw std::logic_error(
            "Trying to create a zero area Arc");
    }
    ArcDir dir = getDirection(o, e);
    setSize(o, e);
    setOrigin(o, e);
    setEnd(o, e);
    setOffset(dir, flip);
    setAngles(dir, flip);
}

bool Arc::areaIsZero() { return w*h==0; }

ArcDir Arc::getDirection(
    const Graph_lib::Point& o, const Graph_lib::Point& e)
{
    if (e.x > o.x && o.y > e.y) { return ArcDir::NE; }
    if (e.x > o.x && e.y > o.y) { return ArcDir::SE; }
    if (o.x > e.x && e.y > o.y) { return ArcDir::SW; }
    return ArcDir::NW;
}
void Arc::setOrigin(
    const Graph_lib::Point& o, const Graph_lib::Point& e)
{
    if (areaIsZero()) {
        throw std::logic_error(
            "Cannot set origin of Arc, area is zero");
    }
    ox = (std::min)(o.x, e.x);
    oy = (std::min)(o.y, e.y);
}
void Arc::setOffset(ArcDir dir, bool flip)
{
    if (areaIsZero()) {
        throw std::logic_error(
            "Cannot set origin of Arc, area is zero");
    }
    switch (dir) {
        case ArcDir::SE:
            offs_x = !flip ? 0 : w;
            offs_y = !flip ? h : 0;
            break;
        case ArcDir::SW:
            offs_x = !flip ? w : 0;
            offs_y = !flip ? h : 0;
            break;
        case ArcDir::NW:
            offs_x = !flip ? w : 0;
            offs_y = !flip ? 0 : h;
            break;
        default:
            offs_x = !flip ? 0 : w;
            offs_y = !flip ? 0 : h;
    }
}

void Arc::setEnd(
    const Graph_lib::Point& o, const Graph_lib::Point& e)
{
    if (areaIsZero()) {
        throw std::logic_error(
            "Cannot set end point of Arc, area is zero");
    }
    ex = (std::max)(o.x, e.x);
    ey = (std::max)(o.y, e.y);
}

void Arc::setSize(
    const Graph_lib::Point& o, const Graph_lib::Point& e)
{
    w = std::abs(o.x - e.x);
    h = std::abs(o.y - e.y);
}


void Arc::setAngles(ArcDir dir, bool flip)
{
    switch ( dir ) {
        case ArcDir::NE:
            a1 = !flip ? 90 : 270;
            break;
        case ArcDir::SE:
            a1 = !flip ? 180 : 0;
            break;
        case ArcDir::SW:
            a1 = !flip ? 270 : 90;
            break;
        default:
            a1 = !flip ? 0 : 180;
    }
    a2 = a1 + 90;
}

void Arc::draw_lines() const {
    if (color().visibility()) {
        fl_arc(
            ox - offs_x, oy - offs_y,
            w * 2, h * 2, a1, a2);
    }
}
