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

int TRITI::TriangleTiler::count_tris_until_oob(GL::Point point,
                                               GL::Point offset,
                                               const int max_count)
{
	int count = 0;
	while (count < max_count && pt_inside_bbox(point)) {
		point.x += offset.x;
		point.y += offset.y;
		GL::Point new_end{static_cast<int>(std::round(point.x + cos(a) * s)),
		                  static_cast<int>(std::round(point.y + sin(a) * s))};
		tris.push_back(std::make_unique<RTRI::RightTriangle>(point, new_end));
		tris.back()->set_color(GL::Color::dark_green);
		if (++count == max_count) {
			throw std::runtime_error("Too many triangles in pattern");
		}
	}
	return count;
}

void TRITI::TriangleTiler::update_transform(Graph_lib::Point new_pos,
                                            int new_side_len,
                                            float new_angle)
{
	s = new_side_len;
	a = new_angle;
	tris.clear();
	GL::Point in_end{static_cast<int>(std::round(new_pos.x + cos(a) * s)),
	                 static_cast<int>(std::round(new_pos.y + sin(a) * s))};
	tris.push_back(std::make_unique<RTRI::RightTriangle>(new_pos, in_end));
	RTRI::RightTriangle& og_tri = reinterpret_cast<RTRI::RightTriangle&>(
	    *tris.back());
	new_bbox();
	// float h = s * sqrt(3.0) / 2;
	// float inv_a = a + M_PI;
	// inv_a = fmod(a, 2 * M_PI);
	// if (inv_a < 0) {
	// 	inv_a += 2 * M_PI;
	// }
	constexpr int max_count = 100;
	int count = 0;
	GL::Point test = new_pos;
	GL::Point offs_a{tris.back()->point(1).x - new_pos.x,
	                 tris.back()->point(1).y - new_pos.y};
	GL::Point offs_b{tris.back()->point(2).x - new_pos.x,
	                 tris.back()->point(2).y - new_pos.y};

	int count_a = count_tris_until_oob(new_pos, offs_a);
	int inv_count_a = count_tris_until_oob(new_pos, {-offs_a.x, -offs_a.y});
	count_a = (count_a > 0) ? count_a - 1 : 0;

	int count_b = count_tris_until_oob(new_pos, offs_b);
	int inv_count_b = count_tris_until_oob(new_pos, {-offs_b.x, -offs_b.y});
	count_b = (count_b > 0) ? count_b - 1 : 0;

	std::vector<GL::Point>
	    tri_bnds{{new_pos.x + count_a * offs_a.x + count_b * offs_b.x,
	              new_pos.y + count_a * offs_a.y + count_b * offs_b.y},
	             {new_pos.x + count_a * offs_a.x - inv_count_b * offs_b.x,
	              new_pos.y + count_a * offs_a.y - inv_count_b * offs_b.y},
	             {new_pos.x - inv_count_a * offs_a.x + count_b * offs_b.x,
	              new_pos.y - inv_count_a * offs_a.y + count_b * offs_b.y},
	             {new_pos.x - inv_count_a * offs_a.x - inv_count_b * offs_b.x,
	              new_pos.y - inv_count_a * offs_a.y - inv_count_b * offs_b.y}};

	int mid_x = static_cast<int>(0.5 * (bg_min.x + bg_max.x));
	std::vector<GL::Point> left_pts{};
	for (GL::Point& p : tri_bnds) {
		if (p.x <= mid_x) {
			left_pts.push_back(p);
		}
	}
	tris.push_back(std::make_unique<GL::Closed_polyline>());
	tris.back()->add(tri_bnds[0]);
	tris.back()->add(tri_bnds[1]);
	tris.back()->add(tri_bnds[2]);
	tris.back()->add(tri_bnds[3]);
	tris.back()->set_color(GL::Color::yellow);
	tris.back()->set_style({GL::Line_style::solid, 2});

	GL::Point top_left{};
	for (int i = 0; i < left_pts.size(); ++i) {
		if (i == 0) {
			top_left = left_pts[i];
			continue;
		}
		if (left_pts[i].y < top_left.y) {
			top_left = left_pts[i];
		}
	}
	GL::Point in_end2{static_cast<int>(std::round(top_left.x + cos(a) * s)),
	                  static_cast<int>(std::round(top_left.y + sin(a) * s))};
	tris.push_back(std::make_unique<RTRI::RightTriangle>(top_left, in_end2));
	tris.back()->set_color(GL::Color::cyan);

	GL::Point top_l{};
	int sub_quadrant = static_cast<int>(new_angle / (M_PI * 0.25));
	switch (sub_quadrant) {
	case 0:
		top_l = tri_bnds[3];
		break;
	case 1:
		top_l = tri_bnds[2];
		break;
	case 2:
		top_l = tri_bnds[2];
		break;
	case 3:
		top_l = tri_bnds[0];
		break;
	case 4:
		top_l = tri_bnds[0];
		break;
	case 5:
		top_l = tri_bnds[1];
		break;
	case 6:
		top_l = tri_bnds[1];
		break;
	case 7:
	default:
		top_l = tri_bnds[3];
		break;
	}
	GL::Point in_end3{static_cast<int>(std::round(top_l.x + cos(a) * s * 0.25)),
	                  static_cast<int>(std::round(top_l.y + sin(a) * s * 0.25))};
	tris.push_back(std::make_unique<RTRI::RightTriangle>(top_l, in_end3));
	tris.back()->set_color(GL::Color::dark_yellow);
	tris.back()->set_style({GL::Line_style::solid, 2});
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

bool TRITI::TriangleTiler::pt_inside_bbox(Graph_lib::Point pt) const
{
	float w = pt_dist(bbox.point(0), bbox.point(1));
	float h = pt_dist(bbox.point(0), bbox.point(3));
	float a = w * h;

	float sum_tri_a = tri_area(bbox.point(0), pt, bbox.point(3))
	                  + tri_area(bbox.point(3), pt, bbox.point(2))
	                  + tri_area(bbox.point(2), pt, bbox.point(1))
	                  + tri_area(pt, bbox.point(1), bbox.point(0));
	return sum_tri_a <= a;
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

float TRITI::pt_dist(Graph_lib::Point p0, Graph_lib::Point p1)
{
	float dx = p1.x - p0.x;
	float dy = p1.y - p0.y;
	return sqrt(dx * dx + dy * dy);
}

float TRITI::tri_area(Graph_lib::Point p0,
                      Graph_lib::Point p1,
                      Graph_lib::Point p2)
{
	float a = ((p1.x * p0.y - p0.x * p1.y) + (p2.x * p1.y - p1.x * p2.y)
	           + (p0.x * p2.y - p2.x * p0.y))
	          * 0.5;
	if (a < 0) {
		a *= -1;
	}
	return a;
}
