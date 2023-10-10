#include "box.h"
#include <algorithm>

using namespace E02;

Box::Box(
    Graph_lib::Point o, Graph_lib::Point e, double ratio
    ) : crv_ratio{ ratio }, crv_radius { 0 }, w{ 0 }, h{ 0 }
{
    errorIfZeroArea(o, e);
    crv_method = CrvMethod::Ratio;

    add(o);
    add(e);

    setSize(o, e);

    int radius_max{ getMaxRadius() };
    setRadius(
        getRadiusFromRatio(ratio, radius_max), radius_max);
}

Box::Box(Graph_lib::Point o, int w, int h, double ratio)
    : crv_ratio{ ratio }, crv_radius { 0 }
{
    errorIfZeroArea(w, h);
    crv_method = CrvMethod::Ratio;

    add(o);
    add({ o.x + w, o.y + h });

    setSize(w, h);

    int radius_max{ getMaxRadius() };
    setRadius(
        getRadiusFromRatio(ratio, radius_max), radius_max);
}

void Box::setSize(
    const Graph_lib::Point& o, const Graph_lib::Point& e)
{
    w = std::abs(o.x - e.x);
    h = std::abs(o.y - e.y);
    if (areaIsZero()) {
        throw std::logic_error(
            "After setting the size of Box, area is zero");
    }
}

void Box::setSize(int ww, int hh)
{
    w = ww;
    h = hh;
    if (areaIsZero()) {
        throw std::logic_error(
            "After setting the size of Box, area is zero");
    }
}

int Box::getMaxRadius() const {
    return (
        (std::min)( static_cast<int>(w * 0.5),
                    static_cast<int>(h * 0.5)));
}

int Box::getRadiusFromRatio(double r, int max) const
{
    return (static_cast<int>(r * max));
}

void Box::setRadius(int r, int max)
{
    crv_radius = (
        (std::min)(
            (std::max)(0, r), max));
}

void Box::draw_lines() const
{
    if (color().visibility()) {
            fl_line(
            0,0,0,0
            );
    }
}

Corner Box::getCorner(
    const Graph_lib::Point& p1,
    const Graph_lib::Point& p2
) const
{
    if (p1.x < p2.x) {
        if (p1.y < p2.y)	{ 	return Corner::NW; }
        if (p1.y > p2.y)	{ 	return Corner::SW; }
    } else
        if (p1.y < p2.y)	{ 	return Corner::NE;
    }
    return Corner::SE;
}

void Box::updateCornerPoints(
    const Graph_lib::Point& o, const Graph_lib::Point& e)
{
    if (number_of_points() == 0) {
        add(o);
    } else {
        set_point(0, o);
    }

    Graph_lib::Point p{ o };
    auto it { dir_to_next_pt.find(getCorner(o, e)) };
    if (it == dir_to_next_pt.end()) {
        throw std::runtime_error(
            "No direction linked to given corner");
    }
    for (int i = 0; i < 2; ++i) {
        if (it == dir_to_next_pt.end()) {
            it = dir_to_next_pt.begin();
        }
        std::pair<int, int> dir { it->second };
        p.x += w * dir.first;
        p.y += h * dir.second;
        if ((i+1) > number_of_points()) {
            add(p);
        } else {
            set_point(i+1, p);
        }
        it++;
    }

    if (number_of_points() < 4) {
        add(e);
    } else {
        set_point(3, o);
    }
}

bool Box::areaIsZero() const {
    return (w<=0 || h<=0);
}

void Box::errorIfZeroArea(int ww, int hh) const
{
    if (ww <= 0 || hh<= 0) {
        throw std::logic_error(
            "Trying to create a zero area Box");
    }
}

void Box::errorIfZeroArea(
    Graph_lib::Point o, Graph_lib::Point e
) const {
    if (o.x == e.x || o.y == e.y) {
        throw std::logic_error(
            "Trying to create a zero area Box");
    }
}
