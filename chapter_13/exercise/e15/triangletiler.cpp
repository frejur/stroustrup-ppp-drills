#include "triangletiler.h"

TRITI::TriangleTiler::TriangleTiler(
    Graph_lib::Point o, int w, int h, int tri_side, double angle)
    : GL::Shape()
    , bg(o, w, h)
    , bbox({o, {o.x + w, o.y}, {o.x + w, o.y + h}, {o.x, o.y + h}})
    , bg_min(o)
    , bg_max({o.x + w, o.y + h})
    , s(tri_side)
    , a(angle)
{
	bg.set_color(GL::Color::black);
	bbox.set_color(GL::Color::red);

	// Add first tile
	GL::Point in_end{static_cast<int>(std::round(o.x + cos(a) * s)),
	                 static_cast<int>(std::round(o.y + sin(a) * s))};
	tris.push_back(std::make_unique<RTRI::RightTriangle>(o, in_end));
	tris.back()->set_color(GL::Color::blue);
}

void TRITI::TriangleTiler::draw_lines() const
{
	bg.draw();
	bbox.draw();
	for (const auto& t : tris) {
		t->draw();
	}
}

void TRITI::TriangleTiler::update_transform(Graph_lib::Point new_pos,
                                            int new_side_len,
                                            float new_angle)
{
	s = new_side_len;
	a = new_angle;
	GL::Point in_end{static_cast<int>(std::round(new_pos.x + cos(a) * s)),
	                 static_cast<int>(std::round(new_pos.y + sin(a) * s))};
	tris.clear();
	tris.push_back(std::make_unique<RTRI::RightTriangle>(new_pos, in_end));
	new_bbox();
}

Graph_lib::Point TRITI::TriangleTiler::point(int p) const
{
	int count = 0;
	for (const auto& t : tris) {
		for (int i = 0; i < t->number_of_points(); ++i) {
			if (count == p) {
				return t->point(i);
			}
			++count;
		}
	}
	throw std::runtime_error("No point with that index");
}

void TRITI::TriangleTiler::new_bbox()
{
	GL::Point c = {(bg_min.x + bg_max.x) / 2, (bg_min.y + bg_max.y) / 2};

	std::vector<GL::Point> pts{{bg_min.x, bg_min.y},
	                           {bg_max.x, bg_min.y},
	                           {bg_max.x, bg_max.y},
	                           {bg_min.x, bg_max.y}};
	GL::Point rot_bg_min;
	GL::Point rot_bg_max;
	bool first_iter = true;
	for (GL::Point& pt : pts) {
		// Rotate bg area
		float x = (pt.x - c.x);
		float y = pt.y - c.y;
		pt.x = c.x
		       + static_cast<int>(((x * std::cos(a) - y * std::sin(a)) * 10 + 5)
		                          / 10);
		pt.y = c.y
		       + static_cast<int>(((x * std::sin(a) + y * std::cos(a)) * 10 + 5)
		                          / 10);
		if (first_iter) {
			rot_bg_min = {pt.x, pt.y};
			rot_bg_max = rot_bg_min;
			first_iter = false;
			continue;
		}

		// Update bounds
		if (pt.x < rot_bg_min.x) {
			rot_bg_min.x = pt.x;
		} else if (pt.x > rot_bg_max.x) {
			rot_bg_max.x = pt.x;
		}

		if (pt.y < rot_bg_min.y) {
			rot_bg_min.y = pt.y;
		} else if (pt.y > rot_bg_max.y) {
			rot_bg_max.y = pt.y;
		}
	}

	// Padded bbox of rotated bg
	int pad = 4;
	pts = {{rot_bg_min.x - pad, rot_bg_min.y - pad},
	       {rot_bg_max.x + pad, rot_bg_min.y - pad},
	       {rot_bg_max.x + pad, rot_bg_max.y + pad},
	       {rot_bg_min.x - pad, rot_bg_max.y + pad}};

	for (int i = 0; i < pts.size(); ++i) {
		// Rotate bbox of rotated bg
		float x = (pts[i].x - c.x);
		float y = pts[i].y - c.y;
		pts[i].x = c.x
		           + static_cast<int>(
		               ((x * std::cos(a) - y * std::sin(a)) * 10 + 5) / 10);
		pts[i].y = c.y
		           + static_cast<int>(
		               ((x * std::sin(a) + y * std::cos(a)) * 10 + 5) / 10);
		bbox.set_point(i, pts[i]);
	}
}

// bool TRITI::TriangleTiler::is_oob(const Graph_lib::Point p_0,
//                                   const Graph_lib::Point p_1) const
// {
// 	/*
// 	 * Returns true if out of bounds
// 	 */
// 	if (p_0.x <= bg_min.x) {
// 		return (p_1.x <= bg_min.x) || (p_1.x == p_0.x && p_1.y < p_0.y);
// 	}
// 	// bool check_b = ((p_0.x == bg_max.x && p_1.x > p_0.x)
// 	//     || (p_0.y == bg_min.y && p_1.y < p_0.y)
// 	//     || (p_0.y == bg_max.y && p_1.y > p_0.y)) {
// 	// 	return true;
// 	// }
// }

// bool TRITI::TriangleTiler::p_fits_bbox(const Graph_lib::Point p) const
// {
// 	return (p.x >= bg_min.x && p.x <= bg_max.x)
// 	       && (p.y >= bg_min.y && p.y <= bg_max.y);
// }

// TRITI::TriCoords TRITI::TriangleTiler::get_tri(const Graph_lib::Point p_0,
//                                                const Graph_lib::Point p_1) const
// {
// 	if (!p_fits_bbox(p_0) || !p_fits_bbox(p_1)) {
// 		return {TriType::ObliqueTriangle, get_oblique(p_0, p_1)};
// 	}
// }

TRITI::Bary_coords TRITI::bary(Graph_lib::Point p,
                               Graph_lib::Point a,
                               Graph_lib::Point b,
                               Graph_lib::Point c)
{
	GL::Point v0 = {b.x - a.x, b.y - a.y};
	GL::Point v1 = {c.x - a.x, c.y - a.y};
	GL::Point v2 = {p.x - a.x, p.y - a.y};

	double d00 = dot(v0, v0);
	double d01 = dot(v0, v1);
	double d11 = dot(v1, v1);
	double d20 = dot(v2, v0);
	double d21 = dot(v2, v1);

	double denom = d00 * d11 - d01 * d01;
	if (denom == 0) {
		return {0, 0, 0};
	}

	double v = (d11 * d20 - d01 * d21) / denom;
	double w = (d00 * d21 - d01 * d20) / denom;
	return {v, w, (1.0 - v - w)};
}

void TRITI::Bbox::draw_lines() const
{
	Shape::draw_lines();
	// then draw closing line:
	if (2 < number_of_points() && color().visibility())
		fl_line(point(number_of_points() - 1).x,
		        point(number_of_points() - 1).y,
		        point(0).x,
		        point(0).y);
}
