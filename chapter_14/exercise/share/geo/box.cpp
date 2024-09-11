#include "box.h"
#include <algorithm>
#include <stdexcept>
#include <iostream>

using namespace BOX;

Box::Box(Graph_lib::Point o,
         Graph_lib::Point e,
         double ratio,
         CrvMethod m,
         Flatten_side fl)
    : crv_method{m}
    , crv_ratio{ratio}
    , crv_radius{0}
    , w{0}
    , h{0}
    , flat_s{fl}
{
    errorIfZeroArea(o, e);

    setSize(o, e);
    updateCornerPoints(o, e);

    int radius_max{ getMaxRadius() };
    initRadius(m, crv_ratio, radius_max);
}

Box::Box(
    Graph_lib::Point o, int w, int h, double ratio, CrvMethod m, Flatten_side fl)
    : crv_method{m}
    , crv_ratio{ratio}
    , crv_radius{0}
    , w{0}
    , h{0}
    , flat_s{fl}
{
    errorIfZeroArea(w, h);

    setSize(w, h);

    updateCornerPoints(o, { o.x + w, o.y + h });

    int radius_max{ getMaxRadius() };
    initRadius(m, crv_ratio, radius_max);
}

void Box::initRadius(CrvMethod m, double ratio_or_radius, double radius_max)
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
Graph_lib::Point Box::bbox_origin() const
{
	return point(getIterDistToNW_Corner(point(0), point(2)));
}

void Box::draw_box(Box::Drawing_mode mode) const
{
	// Offset iterator to start drawing at NW corner
	int i_dist {
		getIterDistToNW_Corner(
			point(0),
			point(2)
		)
	};
	if (mode==DRAW_FILL) {
		fl_begin_complex_polygon();
	} else {
		fl_begin_loop();
	}

	double start_a{ 90 };
	std::vector<std::pair<int, int>> temp;
	for (int i = 0; i < dir_to_next_pt.size(); ++i) {
		int j{static_cast<int>((i + i_dist) % dir_to_next_pt.size())};
		int dir_x{dir_to_next_pt[i].second.first};
		int dir_y{dir_to_next_pt[i].second.second};

		int mid_x = static_cast<int>(
		    0.5 * (point((j + 3) % 4).x + point((j + 0) % 4).x));
		int mid_y = static_cast<int>(
		    0.5 * (point((j + 3) % 4).y + point((j + 0) % 4).y));
		temp.push_back({mid_x, mid_y});

		// Pixel fuckery -------------------------------------------------------
		using CR = Corner;
		const CR dir = dir_to_next_pt[i].first;
		float r_nudge = (dir == CR::NE || dir == CR::SE || dir == CR::SW)
		                    ? -0.01
		                    : 0;
		int x_nudge = (dir == CR::NE || dir == CR::SE) ? -1 : 0;
		int y_nudge = (dir == CR::SE || dir == CR::SW) ? -1 : 0;
		// ---------------------------------------------------------------------

		fl_vertex(mid_x + x_nudge, mid_y + y_nudge);

		if (crv_radius > 0 && !corner_is_flat(dir)) {
			fl_arc(point(j % 4).x + crv_radius * dir_x - crv_radius * dir_y,
			       point(j % 4).y + crv_radius * dir_y + crv_radius * dir_x,
			       crv_radius + r_nudge,
			       start_a - (i - 1) * 90,
			       start_a - i * 90);
		} else {
			fl_vertex(point(j % 4).x + x_nudge, point(j % 4).y + y_nudge);
		}
	}
	if (mode==DRAW_FILL) {
		fl_end_complex_polygon();
	} else {
		fl_end_loop();
	}
	fl_end_loop();
}

void Box::draw_lines() const
{
    if (number_of_points() < 4) return;

    if (fill_color().visibility()) {
        fl_color(fill_color().as_int());
    	draw_box(Box::DRAW_FILL);
    	fl_color(color().as_int());    // reset color
    }

    if (color().visibility()) {
    	draw_box();
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

int BOX::Box::dir_idx(const Graph_lib::Point& o, const Graph_lib::Point& e) const
{
	int idx = -1;
	for (int i = 0; i < dir_to_next_pt.size(); ++i) {
		if (dir_to_next_pt[i].first == getCorner(o, e)) {
			idx = i;
			break;
		}
	}

	if (idx == -1) {
		throw std::runtime_error("No direction found");
	}

	return idx;
}

int Box::getIterDistToNW_Corner(const Graph_lib::Point& o,
                                const Graph_lib::Point& e) const
{
	int idx = dir_idx(o, e);

	return ((std::max)(0, (4 - idx) % 4));
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
	int idx{dir_idx(o, e)};

	for (int i = 0; i < 3; ++i) {
		std::pair<int, int> dir = dir_to_next_pt[idx].second;

		p.x += w * dir.first;
		p.y += h * dir.second;

		if ((i + 1) >= number_of_points()) {
			add({p});
		} else {
			set_point(i + 1, {p});
		}
		idx = (idx + 1) % dir_to_next_pt.size();
	}
}

bool Box::areaIsZero() const {
	return (w <= 0 || h <= 0);
}

bool Box::corner_is_flat(Corner c) const
{
	switch (flat_s) {
	case Flatten_side::Top:
		return (c == Corner::NE || c == Corner::NW);
	case Flatten_side::Right:
		return (c == Corner::NE || c == Corner::SE);
	case Flatten_side::Bottom:
		return (c == Corner::SE || c == Corner::SW);
	case Flatten_side::Left:
		return (c == Corner::NW || c == Corner::SW);
	case Flatten_side::None:
	default:
		return false;
	}
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
