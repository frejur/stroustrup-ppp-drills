#include "tiler.h"
#include "../help/inters.h"

Tile_lib::Bbox::Bbox(Graph_lib::Point origin, int width, int height, float angle)
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

void Tile_lib::Bbox::reset_transform()
{
	if (!init) {
		return;
	}
	update(init_w, init_h, init_a);
}
void Tile_lib::Bbox::update(float angle)
{
	a = angle;
	upd_pts();
}
void Tile_lib::Bbox::update(int width, int height, float angle)
{
	a = angle;
	upd_width(width);
	upd_height(height);
	if (!init) {
		set_center(o);
	}
	upd_pts();
}

void Tile_lib::Bbox::upd_width(int w)
{
	half_w_neg = static_cast<int>(w * 0.5);
	half_w_pos = w - half_w_neg;
}

void Tile_lib::Bbox::upd_height(int h)
{
	half_h_neg = static_cast<int>(h * 0.5);
	half_h_pos = h - half_h_neg;
}

void Tile_lib::Bbox::set_center(Graph_lib::Point origin)
{
	c = {origin.x + half_w_neg, origin.y + half_h_neg};
}

void Tile_lib::Bbox::upd_pts()
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

void Tile_lib::Bbox::rot_coords(
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

Coord_sys::Bounds Tile_lib::Bbox::bounds() const
{
	return Coord_sys::bounds_from_points(
	    {point(0), point(1), point(2), point(3)});
}

void Tile_lib::Bbox::new_from_bounds()
{
	Coord_sys::Bounds bnds{bounds()};
	int width = bnds.max.x - bnds.min.x;
	int height = bnds.max.y - bnds.min.y;
	update(width, height, 0);
}

//------------------------------------------------------------------------------

void Tile_lib::Tiler::draw_lines() const
{
	if (!draw_active) {
		return;
	}
	tiles_bbox.draw();
	for (const auto& t : tiles) {
		t->draw();
	}
	bg.draw();
}

int Tile_lib::Tiler::count_tiles_until_oob(Graph_lib::Point point,
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

	// Determine and disregard the inactive axis
	int gr_axis{axis_w_gr_magnitude(rot_offset)};
	if (gr_axis == -1) {
		throw std::runtime_error("Invalid offset vector");
	} else if (gr_axis == 0) {
		rot_bnds.min.y = bounds_lower_limit;
		rot_bnds.max.y = bounds_upper_limit;
	} else {
		rot_bnds.min.x = bounds_lower_limit;
		rot_bnds.max.x = bounds_upper_limit;
	}

	do {
		rot_pt.x += rot_offset.x;
		rot_pt.y += rot_offset.y;
		if (++count == max_count) {
			throw std::runtime_error("Too many triangles in pattern");
		}
	} while (count < max_count && Coord_sys::is_inside(rot_pt, rot_bnds));
	return count;
}

void Tile_lib::Tiler::update_transform(Graph_lib::Point new_pos,
                                            int new_side_len,
                                            float new_angle)
{
	tiles_cs.set_rotation(new_angle);
	s = new_side_len;
	a = new_angle;
	clear_tiles();

	// DEBUG: Draw initial tile
	add_tile(new_pos, new_side_len, new_angle);
	// END DEBUG: Draw initial tile

	new_bbox();
	Offset_pair offs{offset_pair()};

	if (!tile_is_inside(tiles.size() - 1)) {
		return;
	}

	int count_a = count_tiles_until_oob(new_pos, offs.a);
	int inv_count_a = count_tiles_until_oob(new_pos, {-offs.a.x, -offs.a.y});

	int count_b = count_tiles_until_oob(new_pos, offs.b);
	int inv_count_b = count_tiles_until_oob(new_pos, {-offs.b.x, -offs.b.y});

	add_tiles(new_pos,
	          new_side_len,
	          new_angle,
	          {count_a, inv_count_a},
	          {count_b, inv_count_b},
	          offs.a,
	          offs.b);
}

Graph_lib::Point Tile_lib::Tiler::point(int p) const
{
	int count = 0;
	for (const auto& t : tiles) {
		for (int i = 0; i < t->number_of_points(); ++i) {
			if (count == p) {
				return t->point(i);
			}
			++count;
		}
	}
	throw std::runtime_error("No point carries that index");
}

std::vector<Graph_lib::Point> Tile_lib::Tiler::debug_draw_tiles_bbox_grid()
{
	std::vector<Graph_lib::Point> pts;
	int bbw = tiles_bbox.horizontal_distance_to_min()
	          + tiles_bbox.horizontal_distance_to_max();
	int bbh = tiles_bbox.vertical_distance_to_min()
	          + tiles_bbox.vertical_distance_to_max();
	Graph_lib::Point pt = tiles_cs.to_screen({0, 0});
	tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
	tiles.back()->add({pt.x - 1, pt.y - 1});
	tiles.back()->add({pt.x + 1, pt.y - 1});
	tiles.back()->add({pt.x + 1, pt.y + 1});
	tiles.back()->add({pt.x - 1, pt.y + 1});
	tiles.back()->set_color(Graph_lib::Color::red);
	bool done_with_x = false;
	bool done_with_y = false;
	for (int x = 0; !done_with_x && x < bbw + 20 - 1; x += 20) {
		done_with_y = false;
		if (x > bbw) {
			x = bbw;
			done_with_x = true;
		}
		for (int y = 0; !done_with_y && y < bbh + 20 - 1; y += 20) {
			if (y > bbh) {
				y = bbh;
				done_with_y = true;
			}
			pt = tiles_cs.to_screen(
			    {-tiles_bbox.horizontal_distance_to_max() + x,
			     -tiles_bbox.vertical_distance_to_max() + y});
			tiles.push_back(std::make_unique<Graph_lib::Closed_polyline>());
			tiles.back()->add({pt.x - 1, pt.y - 1});
			tiles.back()->add({pt.x + 1, pt.y - 1});
			tiles.back()->add({pt.x + 1, pt.y + 1});
			tiles.back()->add({pt.x - 1, pt.y + 1});
			tiles.back()->set_color(Graph_lib::Color::dark_red);
			pts.push_back(pt);
		}
	}

	return pts;
}

Tile_lib::Tiler::Tiler(Graph_lib::Point o, int w, int h, int side, double angle)
    : Graph_lib::Shape()
    , draw_active(true)
    , c{o.x + static_cast<int>((w * 5 + 5) / 10),
        o.y + static_cast<int>((h * 5 + 5) / 10)}
    , bg_bnds{o, {o.x + w, o.y + h}}
    , bg{o, w, h}
    , tiles_cs{c}
    , tiles_bnds{bg_bnds}
    , tiles_bbox{o, w, h}
    , s(side)
    , a(angle)
{
	bg.set_color(Graph_lib::Color::black);
	tiles_bbox.set_color(Graph_lib::Color::yellow);
}

bool Tile_lib::Tiler::pt_inside_bbox(Graph_lib::Point pt,
                                          const Tile_lib::Bbox& bbox) const
{
	float w = inters::pt_dist(bbox.point(0), bbox.point(1));
	float h = inters::pt_dist(bbox.point(0), bbox.point(3));
	float a = w * h;

	float sum_tri_a = inters::tri_area(bbox.point(0), pt, bbox.point(3))
	                  + inters::tri_area(bbox.point(3), pt, bbox.point(2))
	                  + inters::tri_area(bbox.point(2), pt, bbox.point(1))
	                  + inters::tri_area(pt, bbox.point(1), bbox.point(0));
	return sum_tri_a <= a;
}

void Tile_lib::Tiler::new_bbox()
{
	tiles_bbox.reset_transform();
	tiles_bbox.rotate(a);
	tiles_bbox.new_from_bounds();
	tiles_bbox.rotate(a);
}

//------------------------------------------------------------------------------

void Tile_lib::Bbox::draw_lines() const
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

Coord_sys::Bounds Tile_lib::rotated_bounds(const Bbox& bb,
                                        const Coord_sys::Coordinate_system& cs)
{
	return Coord_sys::bounds_from_points({cs.to_local(bb.point(0)),
	                                      cs.to_local(bb.point(1)),
	                                      cs.to_local(bb.point(2)),
	                                      cs.to_local(bb.point(3))});
}

//------------------------------------------------------------------------------


Coord_sys::Bounds Tile_lib::bounds(const RTRI::RightTriangle& tri)
{
	if (tri.number_of_points() == 0) {
		throw std::runtime_error(
		    "Cannot calculate bounds for a triangle containing no points");
	}
	std::vector<Graph_lib::Point> pts;
	for (int i = 0; i < tri.number_of_points(); ++i) {
		pts.push_back(tri.point(i));
	}
	return Coord_sys::bounds_from_points(pts);
}

bool Tile_lib::tri_is_inside(Graph_lib::Closed_polyline& p,
                             Coord_sys::Bounds bnds)
{
	if (p.number_of_points() != 3) {
		throw std::runtime_error("Not a triangle");
	}
	for (int i = 0; i < p.number_of_points(); ++i) {
		if (Coord_sys::is_inside(p.point(i), bnds)) {
			p.set_fill_color(Graph_lib::Color::red);
			return true;
		}
	}

	if (inters::any_inside_tri(points_v(bnds),
	                           {p.point(0), p.point(1), p.point(2)})) {
		p.set_fill_color(Graph_lib::Color::green);
		return true;
	}

	if (inters::lines_intersect(points_v(p), points_v(bnds))) {
		p.set_fill_color(Graph_lib::Color::magenta);
		return true;
	}
	return false;
}
