#include "box.h"
#include <algorithm>

using namespace E02;

Box::Box(
    Graph_lib::Point o, Graph_lib::Point e, double ratio,
    CrvMethod m
    ) : crv_method{ m }, crv_ratio{ ratio },
        crv_radius { 0 }, w{ 0 }, h{ 0 }
{
    errorIfZeroArea(o, e);

    setSize(o, e);
    updateCornerPoints(o, e);

    int radius_max{ getMaxRadius() };
    initRadius(m, crv_ratio, radius_max);
}

Box::Box(
    Graph_lib::Point o, int w, int h, double ratio,
    CrvMethod m
    ) : crv_method{ m }, crv_ratio{ ratio },
        crv_radius { 0 }, w{ 0 }, h { 0 }
{
    errorIfZeroArea(w, h);

    setSize(w, h);

    updateCornerPoints(o, { o.x + w, o.y + h });

    int radius_max{ getMaxRadius() };
    initRadius(m, crv_ratio, radius_max);
}

void Box::initRadius(
    CrvMethod m, double ratio_or_radius, double radius_max)
{
    if (m == CrvMethod::Ratio) {
        crv_ratio = (std::max)(
            (std::min)(1.0, ratio_or_radius), 0.0
        );
        setRadius(
            getRadiusFromRatio(crv_ratio, radius_max),
            radius_max
        );
    } else {
        setRadius(ratio_or_radius, radius_max);
    }
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
    if (number_of_points() < 4) return;
    if (color().visibility()) {
        // Offset iterator to start drawing at NW corner
        int i_dist {
            getIterDistToNW_Corner(
                point(0),
                point(2)
            )
        };

        int i{ 0 };
        double start_a{ 90 };
        for (const auto& d : dir_to_next_pt) {
            int j { i + i_dist };
            int dir_x{ d.second.first};
            int dir_y{ d.second.second};

            fl_line(
                point(j%4).x + dir_x * crv_radius,
                point(j%4).y + dir_y * crv_radius,
                point((j+1)%4).x - dir_x * crv_radius,
                point((j+1)%4).y - dir_y * crv_radius
            );

            if (crv_radius > 0) {
                fl_arc(
                    point(j%4).x - crv_radius +
                        crv_radius * dir_x -
                        crv_radius * dir_y,
                    point(j%4).y - crv_radius +
                        crv_radius * dir_y +
                        crv_radius * dir_x,
                    crv_radius * 2, crv_radius * 2,
                    start_a - i * 90, start_a - (i-1) * 90
                );
            }
            ++i;
        }
    }
}

Corner Box::getCorner(
    const Graph_lib::Point& p1,
    const Graph_lib::Point& p2
) const
{
    if (p1.x < p2.x) {
        if (p1.y < p2.y) { return Corner::NW; }
        if (p1.y > p2.y) { return Corner::SW; }
    } else if (p1.y < p2.y) { return Corner::NE; }
    return Corner::SE;
}

int Box::getIterDistToNW_Corner(
    const Graph_lib::Point& o, const Graph_lib::Point& e
) const {
    return(
        (std::max)(
            0,
            (4 -
            (int)std::distance(
                dir_to_next_pt.begin(),
                dir_to_next_pt.find(getCorner(o, e))
            )) % 4
        )
    );
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
    for (int i = 0; i < 3; ++i) {
        if (it == dir_to_next_pt.end()) {
            it = dir_to_next_pt.begin();
        }
        std::pair<int, int> dir { it->second };
        p.x += w * dir.first;
        p.y += h * dir.second;
        if ((i+1) >= number_of_points()) {
            add({ p });
        } else {
            set_point(number_of_points(), { p });
        }
        ++it;
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
