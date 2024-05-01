#include "triangletiler.h"

TRITI::Bbox::Bbox(Graph_lib::Point origin, int width, int height, float angle)
    : init(false)
    , o(origin)
{
	if (width < 1 || height < 1) {
		throw std::runtime_error("Invalid width or height");
	}

	update(width, height, angle);

	init_w = width;
	init_h = height;
	init_a = a;
	init = true;
}

void TRITI::Bbox::reset_transform()
{
	if (!init) {
		return;
	}
	update(init_w, init_h, init_a);
}
void TRITI::Bbox::update(float angle)
{
	a = angle;
	upd_pts();
}
void TRITI::Bbox::update(int width, int height, float angle)
{
	a = angle;
	upd_width(width);
	upd_height(height);
	if (!init) {
		set_center(o);
	}
	upd_pts();
}

void TRITI::Bbox::upd_width(int w)
{
	half_w_neg = static_cast<int>(w * 0.5);
	half_w_pos = w - half_w_neg;
}

void TRITI::Bbox::upd_height(int h)
{
	half_h_neg = static_cast<int>(h * 0.5);
	half_h_pos = h - half_h_neg;
}

void TRITI::Bbox::set_center(Graph_lib::Point origin)
{
	c = {origin.x + half_w_neg, origin.y + half_h_neg};
}

void TRITI::Bbox::upd_pts()
{
	int x1, x2, x3, x4;
	int y1, y2, y3, y4;
	rot_coords(x1, x2, x3, x4, y1, y2, y3, y4);

	if (!init) {
		add({x1, y1});
		add({x2, y2});
		add({x3, y3});
		add({x4, y4});
	} else {
		set_point(0, {x1, y1});
		set_point(1, {x2, y2});
		set_point(2, {x3, y3});
		set_point(3, {x4, y4});
	}
}

void TRITI::Bbox::rot_coords(
    int& x1, int& x2, int& x3, int& x4, int& y1, int& y2, int& y3, int& y4)
{
	float cos_angle = std::cos(a);
	float sin_angle = std::sin(a);

	x1 = round(half_w_pos * cos_angle - half_h_neg * sin_angle) + c.x;
	y1 = round(half_w_pos * sin_angle + half_h_pos * cos_angle) + c.y;

	x2 = round(-half_w_neg * cos_angle - half_h_neg * sin_angle) + c.x;
	y2 = round(-half_w_neg * sin_angle + half_h_pos * cos_angle) + c.y;

	x3 = round(-half_w_neg * cos_angle + half_h_pos * sin_angle) + c.x;
	y3 = round(-half_w_neg * sin_angle - half_h_neg * cos_angle) + c.y;

	x4 = round(half_w_pos * cos_angle + half_h_pos * sin_angle) + c.x;
	y4 = round(half_w_pos * sin_angle - half_h_neg * cos_angle) + c.y;
}

Coord_sys::Bounds TRITI::Bbox::bounds() const
{
	return Coord_sys::bounds_from_points(
	    {point(0), point(1), point(2), point(3)});
}

void TRITI::Bbox::new_from_bounds()
{
	Coord_sys::Bounds bnds{bounds()};
	int width = bnds.max.x - bnds.min.x;
	int height = bnds.max.y - bnds.min.y;
	update(width, height, 0);
}

TRITI::TriangleTiler::TriangleTiler(
    Graph_lib::Point o, int w, int h, int tri_side, double angle)
    : Graph_lib::Shape()
    , draw_active(true)
    , c{o.x + static_cast<int>((w * 5 + 5) / 10),
        o.y + static_cast<int>((h * 5 + 5) / 10)}
    , bg_bnds{o, {o.x + w, o.y + h}}
    , bg{o, w, h}
    , tiles_cs{c}
    , tiles_bnds{bg_bnds}
    , tiles_bbox{o, w, h}
    , s(tri_side)
    , a(angle)
{
	bg.set_color(Graph_lib::Color::black);
	tiles_bbox.set_color(Graph_lib::Color::yellow);

	// Add first tile
	tris.push_back(
	    std::make_unique<RTRI::RightTriangle>(o,
	                                          TRITI::triangle_end_point(o,
	                                                                    a,
	                                                                    s)));
	tris.back()->set_color(Graph_lib::Color::blue);
}

void TRITI::TriangleTiler::draw_lines() const
{
	bg.draw();
	if (!draw_active) {
		return;
	}
	tiles_bbox.draw();
	for (const auto& t : tris) {
		t->draw();
	}
}

int TRITI::TriangleTiler::count_tris_until_oob(Graph_lib::Point point,
                                               Graph_lib::Point offset,
                                               const int max_count)
{
	int count = 0;
	Graph_lib::Point rot_pt{tiles_cs.to_local(point)};
	Graph_lib::Point rot_offset_pt{
	    tiles_cs.to_local({point.x + offset.x, point.y + offset.y})};
	Graph_lib::Point rot_offset{rot_offset_pt.x - rot_pt.x,
	                            rot_offset_pt.y - rot_pt.y};
	Coord_sys::Bounds rot_bnds{rotated_bounds(tiles_bbox, tiles_cs)};
	while (count < max_count && Coord_sys::is_inside(rot_pt, rot_bnds)) {
		rot_pt.x += rot_offset.x;
		rot_pt.y += rot_offset.y;
		if (++count == max_count) {
			throw std::runtime_error("Too many triangles in pattern");
		}
	}
	return count;
}

void TRITI::TriangleTiler::add_tiles(const Graph_lib::Point point_0,
                                     const Graph_lib::Point point_1,
                                     const int count_a,
                                     const Graph_lib::Point offset_a,
                                     const int count_b,
                                     const Graph_lib::Point offset_b,
                                     const bool inv_tile)
{
	Graph_lib::Point pt_0 = point_0;
	Graph_lib::Point pt_1 = point_1;
	for (int a = 0; a < count_a; ++a) {
		pt_0.x = point_0.x + offset_a.x * a;
		pt_0.y = point_0.y + offset_a.y * a;
		pt_1.x = point_1.x + offset_a.x * a;
		pt_1.y = point_1.y + offset_a.y * a;
		for (int b = 0; b < count_b; ++b) {
			if (b > 0) {
				pt_0.x += offset_b.x;
				pt_0.y += offset_b.y;
				pt_1.x += offset_b.x;
				pt_1.y += offset_b.y;
			}
			tris.push_back(
			    std::make_unique<RTRI::RightTriangle>(pt_0, pt_1, inv_tile));
			tris.push_back(
			    std::make_unique<RTRI::RightTriangle>(pt_0, pt_1, !inv_tile));
		}
	}
}

void TRITI::TriangleTiler::update_transform(Graph_lib::Point new_pos,
                                            int new_side_len,
                                            float new_angle)
{
	tiles_cs.set_rotation(new_angle);
	s = new_side_len;
	a = new_angle;
	tris.clear();
	tris.push_back(
	    std::make_unique<RTRI::RightTriangle>(new_pos,
	                                          TRITI::triangle_end_point(new_pos,
	                                                                    a,
	                                                                    s)));
	new_bbox();

	Graph_lib::Point offs_a{tris.back()->point(1).x - new_pos.x,
	                        tris.back()->point(1).y - new_pos.y};
	Graph_lib::Point offs_b{tris.back()->point(2).x - new_pos.x,
	                        tris.back()->point(2).y - new_pos.y};

	int count_a = count_tris_until_oob(new_pos, offs_a);
	int inv_count_a = count_tris_until_oob(new_pos, {-offs_a.x, -offs_a.y});
	count_a = (count_a > 0) ? count_a - 1 : 0;

	int count_b = count_tris_until_oob(new_pos, offs_b);
	int inv_count_b = count_tris_until_oob(new_pos, {-offs_b.x, -offs_b.y});
	count_b = (count_b > 0) ? count_b - 1 : 0;

	std::vector<Graph_lib::Point>
	    tri_bnds{{new_pos.x + count_a * offs_a.x + count_b * offs_b.x,
	              new_pos.y + count_a * offs_a.y + count_b * offs_b.y},
	             {new_pos.x + count_a * offs_a.x - inv_count_b * offs_b.x,
	              new_pos.y + count_a * offs_a.y - inv_count_b * offs_b.y},
	             {new_pos.x - inv_count_a * offs_a.x + count_b * offs_b.x,
	              new_pos.y - inv_count_a * offs_a.y + count_b * offs_b.y},
	             {new_pos.x - inv_count_a * offs_a.x - inv_count_b * offs_b.x,
	              new_pos.y - inv_count_a * offs_a.y - inv_count_b * offs_b.y}};

	int mid_x = c.x;
	std::vector<Graph_lib::Point> left_pts{};
	for (Graph_lib::Point& p : tri_bnds) {
		if (p.x <= mid_x) {
			left_pts.push_back(p);
		}
	}
	tris.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tris.back()->add(tri_bnds[0]);
	tris.back()->add(tri_bnds[1]);
	tris.back()->add(tri_bnds[2]);
	tris.back()->add(tri_bnds[3]);
	tris.back()->set_color(Graph_lib::Color::dark_yellow);
	tris.back()->set_style({Graph_lib::Line_style::solid, 2});

	Graph_lib::Point top_left{};
	for (int i = 0; i < left_pts.size(); ++i) {
		if (i == 0) {
			top_left = left_pts[i];
			continue;
		}
		if (left_pts[i].y < top_left.y) {
			top_left = left_pts[i];
		}
	}
	tris.push_back(std::make_unique<RTRI::RightTriangle>(
	    top_left, TRITI::triangle_end_point(top_left, a, s)));
	tris.back()->set_color(Graph_lib::Color::cyan);

	Top_left_tile top_l_tri{top_left_tile_attributes(new_angle,
	                                                 new_pos,
	                                                 count_a,
	                                                 inv_count_a,
	                                                 offs_a,
	                                                 count_b,
	                                                 inv_count_b,
	                                                 offs_b)};
	Graph_lib::Point top_l_tri_end_pt{
	    TRITI::triangle_end_point(top_l_tri.pos, a, s)};
	tris.push_back(
	    std::make_unique<RTRI::RightTriangle>(top_l_tri.pos, top_l_tri_end_pt));
	tris.back()->set_color(Graph_lib::Color::dark_yellow);
	tris.back()->set_style({Graph_lib::Line_style::solid, 2});
	if (!top_l_tri.inv_dir) {
		add_tiles(top_l_tri.pos,
		          top_l_tri_end_pt,
		          count_a + inv_count_a + 1,
		          {offs_a.x * top_l_tri.sign_a, offs_a.y * top_l_tri.sign_a},
		          count_b + inv_count_b + 1,
		          {offs_b.x * top_l_tri.sign_b, offs_b.y * top_l_tri.sign_b},
		          top_l_tri.inv_tile);
	} else {
		add_tiles(top_l_tri.pos,
		          top_l_tri_end_pt,
		          count_b + inv_count_b + 1,
		          {offs_b.x * top_l_tri.sign_b, offs_b.y * top_l_tri.sign_b},
		          count_a + inv_count_a + 1,
		          {offs_a.x * top_l_tri.sign_a, offs_a.y * top_l_tri.sign_a},
		          top_l_tri.inv_tile);
	}
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
	throw std::runtime_error("No point carries that index");
}

std::vector<Graph_lib::Point> TRITI::TriangleTiler::debug_draw_tiles_bbox_grid()
{
	std::vector<Graph_lib::Point> pts;
	int bbw = tiles_bbox.horizontal_distance_to_min()
	          + tiles_bbox.horizontal_distance_to_max();
	int bbh = tiles_bbox.vertical_distance_to_min()
	          + tiles_bbox.vertical_distance_to_max();
	Graph_lib::Point pt = tiles_cs.to_screen({0, 0});
	tris.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tris.back()->add(pt);
	tris.back()->add({pt.x + 5, pt.y});
	tris.back()->add({pt.x + 5, pt.y + 5});
	tris.back()->add({pt.x, pt.y + 5});
	tris.back()->set_color(Graph_lib::Color::red);
	for (int x = 0; x < bbw; x += 20)
		for (int y = 0; y < bbh; y += 20) {
			pt = tiles_cs.to_screen(
			    {-tiles_bbox.horizontal_distance_to_max() + x,
			     -tiles_bbox.vertical_distance_to_max() + y});
			tris.push_back(std::make_unique<Graph_lib::Closed_polyline>());
			tris.back()->add(pt);
			tris.back()->add({pt.x + 10, pt.y});
			tris.back()->add({pt.x + 10, pt.y + 10});
			tris.back()->add({pt.x, pt.y + 10});
			tris.back()->set_color(Graph_lib::Color::dark_red);
			pts.push_back(pt);
		}

	return pts;
}

bool TRITI::TriangleTiler::pt_inside_bbox(Graph_lib::Point pt,
                                          const TRITI::Bbox& bbox) const
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
	tiles_bbox.reset_transform();
	tiles_bbox.rotate(a);
	tiles_bbox.new_from_bounds();
	tiles_bbox.rotate(a);
}

//------------------------------------------------------------------------------

TRITI::Bary_coords TRITI::bary(Graph_lib::Point p,
                               Graph_lib::Point a,
                               Graph_lib::Point b,
                               Graph_lib::Point c)
{
	Graph_lib::Point v0 = {b.x - a.x, b.y - a.y};
	Graph_lib::Point v1 = {c.x - a.x, c.y - a.y};
	Graph_lib::Point v2 = {p.x - a.x, p.y - a.y};

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

//------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------

Coord_sys::Bounds TRITI::rotated_bounds(const Bbox& bb,
                                        const Coord_sys::Coordinate_system& cs)
{
	return Coord_sys::bounds_from_points({cs.to_local(bb.point(0)),
	                                      cs.to_local(bb.point(1)),
	                                      cs.to_local(bb.point(2)),
	                                      cs.to_local(bb.point(3))});
}

//------------------------------------------------------------------------------

TRITI::Top_left_tile TRITI::top_left_tile_attributes(float angle,
                                                     Graph_lib::Point init_pt,
                                                     int count_a,
                                                     int inv_count_a,
                                                     Graph_lib::Point offs_a,
                                                     int count_b,
                                                     int inv_count_b,
                                                     Graph_lib::Point offs_b)
{
	if (angle < 0 || angle > M_PI * 2) {
		throw std::runtime_error("Invalid angle");
	}

	int sub_quadrant = static_cast<int>(angle / (M_PI * 0.25));
	switch (sub_quadrant) {
	case 0:
	case 7:
		return {false,
		        false,
		        1,
		        1,
		        {init_pt.x - inv_count_a * offs_a.x - inv_count_b * offs_b.x,
		         init_pt.y - inv_count_a * offs_a.y - inv_count_b * offs_b.y}};
	case 1:
	case 2:
		return {true,
		        true,
		        1,
		        -1,
		        {init_pt.x - inv_count_a * offs_a.x + count_b * offs_b.x,
		         init_pt.y - inv_count_a * offs_a.y + count_b * offs_b.y}};
	case 3:
	case 4:
		return {true,
		        false,
		        -1,
		        -1,
		        {init_pt.x + count_a * offs_a.x + count_b * offs_b.x,
		         init_pt.y + count_a * offs_a.y + count_b * offs_b.y}};
	case 5:
	case 6:
		return {true,
		        false,
		        -1,
		        1,
		        {init_pt.x + count_a * offs_a.x - inv_count_b * offs_b.x,
		         init_pt.y + count_a * offs_a.y - inv_count_b * offs_b.y}};
	default:
		throw std::runtime_error("Invalid angle");
	}
}
